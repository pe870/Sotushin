#ifndef __DIINPUT__
#define __DIINPUT__

#include <dinput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")	//�R���g���[������Ŏg�p

//�萔
#define N_OFFSET	500	//�X�e�B�b�N�̃j���[�g�����]�[��

//�L�[���̗񋓑�
enum enPKey{
	enPKey_U,	//Up
	enPKey_D,	//Down
	enPKey_L,	//Left
	enPKey_R,	//Right
	enPKey_00,
	enPKey_01,
	enPKey_02,
	enPKey_03,
	enPKey_04,
	enPKey_05,
	enPKey_06,
	enPKey_07,
	enPKey_08,
	enPKey_09,
	enPKey_10,
	enPKey_11,

	enPKey_Max	//���͂̍ő吔

};


class DInput
{
public:
	DInput();
	~DInput();

	//DirectInput �������ݒ�
	bool initDI(HWND hWnd);
	//���͏��X�V�֐�
	HRESULT UpdateInputState();
	//���̓`�F�b�N�֐�
	bool IsPressKey(enPKey key);

private:
	LPDIRECTINPUT8			m_pDI;	//DxInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	m_pPad;	//�f�o�C�X�I�u�W�F�N�g�i�R���g���[���j

	unsigned int m_uInputState;		//���͏���ۊǗp

	//���͏��̒ǉ�
	void AddInputState(enPKey Key);
	//���͏��̏�����
	void InitInputState();

};

#endif //__DIINPUT__