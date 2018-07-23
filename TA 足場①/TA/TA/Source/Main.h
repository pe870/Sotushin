//警告についてのｺｰﾄﾞ分析を無効にする. 4005:再定義.
#pragma warning(disable:4005)

#include <Windows.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//「D3DX～」の定義使用時に必要.
#include <D3D10.h>

#include "DX9Mesh.h"	//Dx9を使用するｸﾗｽ.
#include "Sprite.h"		//板ﾎﾟﾘｺﾞﾝ(ｽﾌﾟﾗｲﾄ)ｸﾗｽ.
#include "DebugText.h"	//ﾃﾞﾊﾞｯｸﾞﾃｷｽﾄｸﾗｽ.
#include "Sound.h"		//ｻｳﾝﾄﾞｸﾗｽ.
#include "Sprite2D.h"
//ﾗｲﾌﾞﾗﾘ.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )//「D3DX～」の定義使用時に必要.


//定数.
#define WND_TITLE	"初めての3Dシューティング"
#define APP_NAME	"3DSTG"

//構造体.
//カメラ情報.

struct CAMERA
{
	D3DXVECTOR3	vEye;		//カメラ位置.
	D3DXVECTOR3 vLook;		//カメラ注視位置.
	float		Yaw;		//Y回転軸.
	D3DXMATRIX	mRotation;	//回転行列.

};


/*************************************************
*	ﾒｲﾝｸﾗｽ.
**/
class clsMain
{
public://public 外部からｱｸｾｽ可能.
	clsMain();	//ｺﾝｽﾄﾗｸﾀ.
	~clsMain();	//ﾃﾞｽﾄﾗｸﾀ.

	//ｳｨﾝﾄﾞｳ初期化関数.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT iX, INT iY, INT iWidth, INT iHeight,
		LPSTR WindowName);

	//ｳｨﾝﾄﾞｳ関数(ﾒｯｾｰｼﾞ毎の処理)
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

	//ﾒｯｾｰｼﾞﾙｰﾌﾟ.
	void Loop();
	//ｱﾌﾟﾘｹｰｼｮﾝﾒｲﾝ処理.
	void AppMain();

private://private 外部からｱｸｾｽ不可能.
	HWND	m_hWnd;//ｳｨﾝﾄﾞｳﾊﾝﾄﾞﾙ.


//以降はDirectX関係.
public:
	//DirectX初期化.
	HRESULT Init3D();
	//Direct3D終了処理.
	void DestroyD3D();


	//描画(ﾚﾝﾀﾞﾘﾝｸﾞ).
	void Render();

	/************シーン毎の処理*************/
	void Title();		//タイトリ処理.
	void Main();		//メイン処理.
	void Clear();		//クリア処理.
	void Over();		//オーバー処理.

	void P_ACT();		//プレイヤー処理.
	void E_ACT();		//雑魚処理.
	void B_ACT();		//ボス処理.

	/***************************************/

	void ScaffSqu();

	/***********************読込系****************************/

	void LoadModel();	//ﾓﾃﾞﾙ読込関数.
	void LoadSound();	//音源読込関数.
	/**********************************************************/

	//カメラ関数.
	void Camera();
	//ﾌﾟﾛｼﾞｪｸｼｮﾝ関数.
	void Proj();


	/*******************当たり判定関連*************************/
	//ｽﾌｨｱ作成.
	HRESULT InitSphere(clsDx9Mesh* pMesh);
	//●衝突判定.
	bool Collision(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget);
	//ﾊﾞｳﾝﾃﾞｨﾝｸﾞﾎﾞｯｸｽ作成.
	HRESULT	InitBBox(clsDx9Mesh* pMesh);
	//■衝突判定.
	bool BBoxCollision(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget);

	/**********************************************************/

	


private:
	// ↓ｱﾌﾟﾘに一つだけ.
	ID3D11Device*	m_pDevice;//ﾃﾞﾊﾞｲｽｵﾌﾞｼﾞｪｸﾄ.
	ID3D11DeviceContext* m_pContext;//ﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ.
	IDXGISwapChain*		 m_pSwapChain;//ｽﾜｯﾌﾟﾁｪｰﾝ.
	//ﾚﾝﾀﾞｰﾀｰｹﾞｯﾄﾋﾞｭｰ.
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;
	//ﾊﾞｯｸﾊﾞｯﾌｧ.
	ID3D11Texture2D*	m_pBackBuffer_DSTex;
	//ﾃﾞﾌﾟｽｽﾃﾝｼﾙﾋﾞｭｰ.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;




	ID3D11SamplerState*	m_pSampleLinear;	//ﾃｸｽﾁｬのｻﾝﾌﾟﾗ ﾃｸｽﾁｬに各種ﾌｨﾙﾀをかける.
	ID3D11ShaderResourceView* m_pTexture;	//ﾃｸｽﾁｬ.
	CAMERA			m_Camera;	//カメラ情報.
	D3DXMATRIX		m_mView;	//ビュー(カメラ行列).
	D3DXMATRIX		m_mProj;	//プロジェクション行列.
	D3DXVECTOR3		m_vLight;	//ﾗｲﾄの方向.
	clsDx9Mesh*		m_pClsDx9Mesh;//Dx9ﾒｯｼｭｸﾗｽ.

	//ﾃﾞﾊﾞｯｸﾞﾃｷｽﾄｸﾗｽ.
	clsDebugText*	m_pDebugText;

	//板ﾎﾟﾘ用(アニメ有).
	clsSprite*		m_pExplosion;	//爆発用.
	
	//スプライト2Dｸﾗｽ.
	clsSprite2D*	m_pSprite2D;

	//ﾊﾞｳﾝﾃﾞｨﾝｸﾞｽﾌｨｱ用.
	clsDx9Mesh*		m_pSphere;	//ｽﾌｨｱｵﾌﾞｼﾞｪｸﾄ.

	/****************モデル宣言*****************/
	clsDx9Mesh*		m_pGround;
	clsDx9Mesh*		m_pPlayer;

	clsDx9Mesh*		m_aScafSqu;
	clsDx9Mesh*		m_aScafSquM;

	/********************************************/


	/*****************音源宣言*******************/
	clsSound		m_sTitle;

	/********************************************/

};