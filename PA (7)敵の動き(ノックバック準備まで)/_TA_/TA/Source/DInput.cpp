#include "DInput.h"

LPDIRECTINPUT8			g_pDI;	//DxInputオブジェクト
LPDIRECTINPUTDEVICE8	g_pPad;//デバイスオブジェクト（コントローラ）	

/*****「クラス関数ではない」関数*****/
//ジョイスティック列挙関数
BOOL CALLBACK EnumJoysticksCallBack(const DIDEVICEINSTANCE *pDiDInstance, VOID *pContext)
{
	HRESULT hRlt;	//関数の復帰値

	//デバイスの作成
	hRlt = g_pDI->CreateDevice(
		pDiDInstance->guidInstance,	//デバイスの番号
		&g_pPad,					//(out)作成されたデバイスオブジェクト
		NULL);
	//エラーチェック
	if (hRlt != DI_OK){
		return DIENUM_CONTINUE;	//次のデバイスを要求
	}

	return DIENUM_STOP;	//列挙停止
}

//オブジェクト列挙関数
BOOL CALLBACK EnumObjectsCallBack(const DIDEVICEOBJECTINSTANCE *pDiDObjectInstance, VOID *pContext){
	//軸(Axis、アナログスティック)を持っているか？
	if (pDiDObjectInstance->dwType & DIDFT_AXIS){
		//入力情報の範囲を設定する
		DIPROPRANGE diprg;	//範囲設定構造体

		diprg.diph.dwSize = sizeof(DIPROPRANGE);		//構造体のサイズ
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);	//ヘッダー情報のサイズ
		diprg.diph.dwObj = pDiDObjectInstance->dwType;	//オブジェクトタイプを設定する（Axisタイプ)
		diprg.diph.dwHow = DIPH_BYID;					//dwObjに設定されたものがオブジェクトの種類か？インスタンス番号か？

		diprg.lMax = +1000;	//軸の最大値
		diprg.lMin = -1000;	//軸の最小値

		//範囲の設定
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

//DirectInputの初期化設定
bool DInput::initDI(HWND hWnd)
{
	HRESULT hRlt;	//関数の復帰値

	/*****DxInputオブジェクトを作成*****/
	hRlt = DirectInput8Create(
		GetModuleHandle(NULL),	//DxInput を作成するアプリのハンドル
		DIRECTINPUT_VERSION,	//固定：DxInputのバージョン
		IID_IDirectInput8,		//固定：UnicodeとAnsiの区別用
		(VOID**)&m_pDI,			//(out)DxInputオブジェクト
		NULL);
	//エラーチェック
	if (hRlt != DI_OK){
		MessageBox(NULL, "DxInputの作成に失敗", "エラー", MB_OK);
		return false;
	}
	g_pDI = m_pDI;
	/**********/

	/*****使用可能なコントローラを探す（列挙する)*****/
	hRlt = (*m_pDI).EnumDevices(
		DI8DEVCLASS_GAMECTRL,	//全てのゲームコントローラ
		EnumJoysticksCallBack,	//コントローラの列挙関数
		NULL,					//コールバック関数からの値
		DIEDFL_ATTACHEDONLY);	//繋がっているもののみ
	//エラーチェック
	if (hRlt != DI_OK){
		MessageBox(NULL, "コントローラの確認に失敗  人間は愚か", "エラー", MB_OK);
		return false;
	}
	m_pPad = g_pPad;
	/**********/

	/*****コントローラの接続確認*****/
	//接続されない場合
	if (g_pPad == NULL){
		MessageBox(NULL, "コントローラーが接続されていません", "警告", MB_OK);
	}
	//接続ありの場合
	else{
		//コントローラ構造体のデータフォーマットを作成
		hRlt = g_pPad->SetDataFormat(&c_dfDIJoystick2);	//固定
		if (hRlt != DI_OK){
			MessageBox(NULL, "データフォーマットの作成失敗", "エラー", MB_OK);
		}

		//他のデバイスとの協調レベルを設定
		hRlt = g_pPad->SetCooperativeLevel(hWnd,
			DISCL_EXCLUSIVE |	//排他アクセス
			DISCL_FOREGROUND);	//フォアグラウンドアクセス権
		if (hRlt != DI_OK){
			MessageBox(NULL, "協調レベルの設定失敗", "エラー", MB_OK);
		}

		//使用可能なオブジェクト（ボタンなど）の列挙を作成
		hRlt = g_pPad->EnumObjects(
			EnumObjectsCallBack,	//オブジェクト列挙関数
			(VOID*)hWnd,			//コールバック関数に送る情報
			DIDFT_ALL);				//全てのオブジェクト
		if (hRlt != DI_OK){
			MessageBox(NULL, "オブジェクトの列挙に失敗", "エラー", MB_OK);
		}

	}


	return true;
	/**********/

}

//入力情報更新
HRESULT DInput::UpdateInputState(){
	HRESULT hRlt;	//関数復帰値
	DIJOYSTATE2 js;	//ジョイスティック情報構造体

	//入力情報の初期化
	InitInputState();

	//ジョイスティックの接続確認
	if (m_pPad == NULL)	return S_OK;


	//ジョイスティックが変更されているかを確認
	hRlt = m_pPad->Poll();
	if (hRlt != DI_OK && hRlt != DI_NOEFFECT){ //DI_NOEFFECT：確認不要なデバイス
		//コントローラのアクセス権を取得する
		hRlt = m_pPad->Acquire();
		while (hRlt == DIERR_INPUTLOST)
		{
			hRlt = m_pPad->Acquire();
		}
		return S_OK;
	}

	//コントローラから直接データを取得する
	hRlt = m_pPad->GetDeviceState(
		sizeof(DIJOYSTATE2),	//取得するサイズ
		&js);					//(out)取得したデータの結果
	if (hRlt != DI_OK) return hRlt;


	/*****入力結果*****/
	//軸（Axis）
	if (js.lX > N_OFFSET)
		AddInputState(enPKey_R);
	else if (js.lX < -N_OFFSET)
		AddInputState(enPKey_L);
	if (js.lY > N_OFFSET)
		AddInputState(enPKey_D);
	else if (js.lY < -N_OFFSET)
		AddInputState(enPKey_U);

	//ボタン（RGB Buttons）
	//　ループ開始位置をチェック対象のボタンに変更する
	for (int i = enPKey_00; i < enPKey_Max; i++){
		//コントローラのボタンの配列開始番号が0からなので開始位置を戻す
		if (js.rgbButtons[i - enPKey_00] & 0x80)
			//列挙体にキャストしてループ変数を入力値として格納
			AddInputState((enPKey)i);
	}

	/****************/


	return S_OK;
}

//入力情報を追加
void DInput::AddInputState(enPKey key){
	// シフト演算子: << または >>
	m_uInputState |= 1 << key;
}

//入力情報の初期化
void DInput::InitInputState(){
	m_uInputState = 0;
}

//入力チェック
bool DInput::IsPressKey(enPKey key){

	if ((m_uInputState >> key) & 1){
		return true;
	}
	return false;
}