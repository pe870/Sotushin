#include "DInput.h"

LPDIRECTINPUT8			g_pDI;	//DxInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8	g_pPad;//�f�o�C�X�I�u�W�F�N�g�i�R���g���[���j	

/*****�u�N���X�֐��ł͂Ȃ��v�֐�*****/
//�W���C�X�e�B�b�N�񋓊֐�
BOOL CALLBACK EnumJoysticksCallBack(const DIDEVICEINSTANCE *pDiDInstance, VOID *pContext)
{
	HRESULT hRlt;	//�֐��̕��A�l

	//�f�o�C�X�̍쐬
	hRlt = g_pDI->CreateDevice(
		pDiDInstance->guidInstance,	//�f�o�C�X�̔ԍ�
		&g_pPad,					//(out)�쐬���ꂽ�f�o�C�X�I�u�W�F�N�g
		NULL);
	//�G���[�`�F�b�N
	if (hRlt != DI_OK){
		return DIENUM_CONTINUE;	//���̃f�o�C�X��v��
	}

	return DIENUM_STOP;	//�񋓒�~
}

//�I�u�W�F�N�g�񋓊֐�
BOOL CALLBACK EnumObjectsCallBack(const DIDEVICEOBJECTINSTANCE *pDiDObjectInstance, VOID *pContext){
	//��(Axis�A�A�i���O�X�e�B�b�N)�������Ă��邩�H
	if (pDiDObjectInstance->dwType & DIDFT_AXIS){
		//���͏��͈̔͂�ݒ肷��
		DIPROPRANGE diprg;	//�͈͐ݒ�\����

		diprg.diph.dwSize = sizeof(DIPROPRANGE);		//�\���̂̃T�C�Y
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);	//�w�b�_�[���̃T�C�Y
		diprg.diph.dwObj = pDiDObjectInstance->dwType;	//�I�u�W�F�N�g�^�C�v��ݒ肷��iAxis�^�C�v)
		diprg.diph.dwHow = DIPH_BYID;					//dwObj�ɐݒ肳�ꂽ���̂��I�u�W�F�N�g�̎�ނ��H�C���X�^���X�ԍ����H

		diprg.lMax = +1000;	//���̍ő�l
		diprg.lMin = -1000;	//���̍ŏ��l

		//�͈͂̐ݒ�
		if (FAILED(g_pPad->SetProperty(DIPROP_RANGE, &diprg.diph))){
			return DIENUM_STOP;
		}
	}

	return DIENUM_CONTINUE;
}

/**********/

DInput::DInput()
{
	m_pDI = NULL;
	m_pPad = NULL;
}

DInput::~DInput()
{
}

//DirectInput�̏������ݒ�
bool DInput::initDI(HWND hWnd)
{
	HRESULT hRlt;	//�֐��̕��A�l

	/*****DxInput�I�u�W�F�N�g���쐬*****/
	hRlt = DirectInput8Create(
		GetModuleHandle(NULL),	//DxInput ���쐬����A�v���̃n���h��
		DIRECTINPUT_VERSION,	//�Œ�FDxInput�̃o�[�W����
		IID_IDirectInput8,		//�Œ�FUnicode��Ansi�̋�ʗp
		(VOID**)&m_pDI,			//(out)DxInput�I�u�W�F�N�g
		NULL);
	//�G���[�`�F�b�N
	if (hRlt != DI_OK){
		MessageBox(NULL, "DxInput�̍쐬�Ɏ��s", "�G���[", MB_OK);
		return false;
	}
	g_pDI = m_pDI;
	/**********/

	/*****�g�p�\�ȃR���g���[����T���i�񋓂���)*****/
	hRlt = (*m_pDI).EnumDevices(
		DI8DEVCLASS_GAMECTRL,	//�S�ẴQ�[���R���g���[��
		EnumJoysticksCallBack,	//�R���g���[���̗񋓊֐�
		NULL,					//�R�[���o�b�N�֐�����̒l
		DIEDFL_ATTACHEDONLY);	//�q�����Ă�����̂̂�
	//�G���[�`�F�b�N
	if (hRlt != DI_OK){
		MessageBox(NULL, "�R���g���[���̊m�F�Ɏ��s  �l�Ԃ͋���", "�G���[", MB_OK);
		return false;
	}
	m_pPad = g_pPad;
	/**********/

	/*****�R���g���[���̐ڑ��m�F*****/
	//�ڑ�����Ȃ��ꍇ
	if (g_pPad == NULL){
		MessageBox(NULL, "�R���g���[���[���ڑ�����Ă��܂���", "�x��", MB_OK);
	}
	//�ڑ�����̏ꍇ
	else{
		//�R���g���[���\���̂̃f�[�^�t�H�[�}�b�g���쐬
		hRlt = g_pPad->SetDataFormat(&c_dfDIJoystick2);	//�Œ�
		if (hRlt != DI_OK){
			MessageBox(NULL, "�f�[�^�t�H�[�}�b�g�̍쐬���s", "�G���[", MB_OK);
		}

		//���̃f�o�C�X�Ƃ̋������x����ݒ�
		hRlt = g_pPad->SetCooperativeLevel(hWnd,
			DISCL_EXCLUSIVE |	//�r���A�N�Z�X
			DISCL_FOREGROUND);	//�t�H�A�O���E���h�A�N�Z�X��
		if (hRlt != DI_OK){
			MessageBox(NULL, "�������x���̐ݒ莸�s", "�G���[", MB_OK);
		}

		//�g�p�\�ȃI�u�W�F�N�g�i�{�^���Ȃǁj�̗񋓂��쐬
		hRlt = g_pPad->EnumObjects(
			EnumObjectsCallBack,	//�I�u�W�F�N�g�񋓊֐�
			(VOID*)hWnd,			//�R�[���o�b�N�֐��ɑ�����
			DIDFT_ALL);				//�S�ẴI�u�W�F�N�g
		if (hRlt != DI_OK){
			MessageBox(NULL, "�I�u�W�F�N�g�̗񋓂Ɏ��s", "�G���[", MB_OK);
		}

	}


	return true;
	/**********/

}

//���͏��X�V
HRESULT DInput::UpdateInputState(){
	HRESULT hRlt;	//�֐����A�l
	DIJOYSTATE2 js;	//�W���C�X�e�B�b�N���\����

	//���͏��̏�����
	InitInputState();

	//�W���C�X�e�B�b�N�̐ڑ��m�F
	if (m_pPad == NULL)	return S_OK;


	//�W���C�X�e�B�b�N���ύX����Ă��邩���m�F
	hRlt = m_pPad->Poll();
	if (hRlt != DI_OK && hRlt != DI_NOEFFECT){ //DI_NOEFFECT�F�m�F�s�v�ȃf�o�C�X
		//�R���g���[���̃A�N�Z�X�����擾����
		hRlt = m_pPad->Acquire();
		while (hRlt == DIERR_INPUTLOST)
		{
			hRlt = m_pPad->Acquire();
		}
		return S_OK;
	}

	//�R���g���[�����璼�ڃf�[�^���擾����
	hRlt = m_pPad->GetDeviceState(
		sizeof(DIJOYSTATE2),	//�擾����T�C�Y
		&js);					//(out)�擾�����f�[�^�̌���
	if (hRlt != DI_OK) return hRlt;


	/*****���͌���*****/
	//���iAxis�j
	if (js.lX > N_OFFSET)
		AddInputState(enPKey_R);
	else if (js.lX < -N_OFFSET)
		AddInputState(enPKey_L);
	if (js.lY > N_OFFSET)
		AddInputState(enPKey_D);
	else if (js.lY < -N_OFFSET)
		AddInputState(enPKey_U);

	//�{�^���iRGB Buttons�j
	//�@���[�v�J�n�ʒu���`�F�b�N�Ώۂ̃{�^���ɕύX����
	for (int i = enPKey_00; i < enPKey_Max; i++){
		//�R���g���[���̃{�^���̔z��J�n�ԍ���0����Ȃ̂ŊJ�n�ʒu��߂�
		if (js.rgbButtons[i - enPKey_00] & 0x80)
			//�񋓑̂ɃL���X�g���ă��[�v�ϐ�����͒l�Ƃ��Ċi�[
			AddInputState((enPKey)i);
	}

	/****************/


	return S_OK;
}

//���͏���ǉ�
void DInput::AddInputState(enPKey key){
	// �V�t�g���Z�q: << �܂��� >>
	m_uInputState |= 1 << key;
}

//���͏��̏�����
void DInput::InitInputState(){
	m_uInputState = 0;
}

//���̓`�F�b�N
bool DInput::IsPressKey(enPKey key){

	if ((m_uInputState >> key) & 1){
		return true;
	}
	return false;
}