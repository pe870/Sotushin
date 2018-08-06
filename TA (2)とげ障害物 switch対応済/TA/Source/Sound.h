#ifndef __SOUND__
#define __SOUND__

#include <Windows.h>

#pragma comment (lib, "winmm.lib")	//�����֌W

//������o�b�t�@�̃T�C�Y
#define STR_BUFF_MAX	256


class clsSound
{
public:
	clsSound();
	~clsSound();

	//�����t�@�C�����J��
	bool Open(LPCTSTR sFileName, char *sAlias, HWND hWnd);
	//�����t�@�C�������
	bool Close();
	//�����t�@�C�����Đ�
	bool Play( bool bNotify = false);
	//�����t�@�C�����~
	bool Stop();

	//�����̃X�e�[�^�X
	bool GetStatus(char *sStatus, char *sAlias, HWND hWnd);
	//�����͒�~���Ă��邱�Ƃ��m�F
	bool IsStopped();
	//�����͍Đ����Ă��邱�Ƃ��m�F
	bool IsPlaying();
	//�����̍Đ��ʒu��
	bool SeekToStart();

	//���ʂ̒���
	bool SetVolume(int iVolume);
private:
	HWND	m_hWnd;		//�E�B���h�E�n���h��
	char	m_sAlias[STR_BUFF_MAX];	//�G�C���A�X
};

#endif //__SOUND__
