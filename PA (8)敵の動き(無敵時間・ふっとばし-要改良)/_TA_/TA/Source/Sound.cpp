#include "Sound.h"


clsSound::clsSound()
{
	ZeroMemory(this, sizeof(clsSound));
}

clsSound::~clsSound()
{
}

//�����t�@�C�����J��
bool clsSound::Open(LPCTSTR sFileName, char *sAlias, HWND hWnd){
	m_hWnd = hWnd;	//�����o�[�E�B���h�E�n���h���̐ݒ�
	strcpy_s(m_sAlias, sizeof(m_sAlias), sAlias); //�����o�[�G�C���A�X�̐ݒ�


	//�R�}���h
	char command[STR_BUFF_MAX] = "open ";

	//������̌���
	strcat_s(command, sizeof(command), sFileName);
	strcat_s(command, sizeof(command), " alias ");
	strcat_s(command, sizeof(command), m_sAlias);
	
	//�R�}���h�F"open [sFileName] alias [sAlias]"
	if(mciSendString(command, NULL, 0, m_hWnd) == 0){
		return true;
	}

	return false;
}

//�����t�@�C�������
bool clsSound::Close(){
	//�R�}���h
	char command[STR_BUFF_MAX] = "close ";

	//������̌���
	strcat_s(command, sizeof(command), m_sAlias);
	
	//�R�}���h�F"close [sAlias]"
	if(mciSendString(command, NULL, 0, m_hWnd) == 0){
		return true;
	}

	return false;
}

//�����t�@�C�����Đ�
bool clsSound::Play(bool bNotify){
	//�R�}���h
	char command[256] = "play ";

	//������̌���
	strcat_s(command, sizeof(command), m_sAlias);
	if(bNotify)
		//notify : �����I�������Ƃ���hWnd��MM_MCINOTIFY���b�Z�[�W���|�X�g����
		strcat_s(command, sizeof(command), " notify");
	
	//�R�}���h�F"play [sAlias]" �܂��� "play [sAlias] notify"
	if(mciSendString(command, NULL, 0, m_hWnd) == 0){
		return true;
	}

	return false;
}

//�����t�@�C�����~
bool clsSound::Stop(){
	//�R�}���h
	char command[256] = "stop ";

	//������̌���
	strcat_s(command, sizeof(command), m_sAlias);
	
	//�R�}���h�F"stop [sAlias]"
	if(mciSendString(command, NULL, 0, m_hWnd) == 0){
		return true;
	}

	return false;
}


//�����̃X�e�[�^�X
//�@sStatus�̔z�񐔂�256�ȉ��ɂ��邱��
//�@�������A��Ԃ̎擾����ꍇ�́A�Đ����Ɂunotify�v��ݒ肵�A
//�@�E�B���h�E�n���h���Ƀ��b�Z�[�W�𑗂��Ă����K�v������
bool clsSound::GetStatus(char *sStatus, char *sAlias, HWND hWnd){
	//�R�}���h
	char command[256] = "status ";

	//������̌���
	strcat_s(command, sizeof(command), sAlias);
	strcat_s(command, sizeof(command), " mode");

	//�R�}���h�F"status [sAlias] mode"
	if(mciSendString(command, sStatus, 256, hWnd) == 0){
		return true;
	}

	return false;
}

//�����͒�~���Ă��邱�Ƃ��m�F
bool clsSound::IsStopped(){

	char sStatus[STR_BUFF_MAX] = "";

	if(GetStatus(sStatus, m_sAlias, m_hWnd)){ //��Ԃ̎擾
		if(strcmp(sStatus, "stopped") == 0) //��Ԃ̕�������r
			return true;
	}
	return false;

}

//�����͍Đ����Ă��邱�Ƃ��m�F
bool clsSound::IsPlaying(){
	char sStatus[STR_BUFF_MAX] = "";

	if(GetStatus(sStatus, m_sAlias, m_hWnd)){ //��Ԃ̎擾
		if(strcmp(sStatus, "playing") == 0) //��Ԃ̕�������r
			return true;
	}
	return false;
}

//�����̍Đ��ʒu������������
bool clsSound::SeekToStart(){
	//�R�}���h
	char command[STR_BUFF_MAX] = "seek ";

	//������̌���
	strcat_s(command, sizeof(command), m_sAlias);
	strcat_s(command, sizeof(command), " to start");
	
	//�R�}���h�F"seek [sAlias] to start"
	if(mciSendString(command, NULL, 0, m_hWnd) == 0){
		return true;
	}

	return false;
}


bool clsSound::SetVolume(int iVolume)
{
	
	//���ʂ͈̔�:0�`1k
	if(iVolume<0)	iVolume=0;
	if(iVolume>=1000)	iVolume=1000;

	//���ʂ𕶎���ɕϊ�
	char sVolume[8] = "";
	wsprintf(sVolume,"%d",iVolume);

	//�R�}���h
	char command[STR_BUFF_MAX] = "setaudio ";

	//������̌���
	strcat_s(command, sizeof(command), m_sAlias);
	strcat_s(command, sizeof(command), " volume to ");
	strcat_s(command, sizeof(command), sVolume);


	//�R�}���h:"setaudio [Alias] volume to [Volume]"
	if(mciSendString(command,NULL,0,m_hWnd)==0)
	{
		return true;
	}
	return false;

};
