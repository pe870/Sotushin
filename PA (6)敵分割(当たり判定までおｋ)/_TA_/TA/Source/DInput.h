#ifndef __DIINPUT__
#define __DIINPUT__

#include <dinput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")	//コントローラ操作で使用

//定数
#define N_OFFSET	500	//スティックのニュートラルゾーン

//キー情報の列挙体
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

	enPKey_Max	//入力の最大数

};


class DInput
{
public:
	DInput();
	~DInput();

	//DirectInput 初期化設定
	bool initDI(HWND hWnd);
	//入力情報更新関数
	HRESULT UpdateInputState();
	//入力チェック関数
	bool IsPressKey(enPKey key);

private:
	LPDIRECTINPUT8			m_pDI;	//DxInputオブジェクト
	LPDIRECTINPUTDEVICE8	m_pPad;	//デバイスオブジェクト（コントローラ）

	unsigned int m_uInputState;		//入力情報を保管用

	//入力情報の追加
	void AddInputState(enPKey Key);
	//入力情報の初期化
	void InitInputState();

};

#endif //__DIINPUT__