//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���. 4005:�Ē�`.
#pragma warning(disable:4005)

#include <Windows.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3D10.h>

#include "DX9Mesh.h"
#include "Sprite.h"
#include "Sprite2D.h"
#include "DebugText.h"

#include "Sound.h"

#include "costant.h"	//�萔�܂Ƃߐ�.

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.

//�萔.
#define WND_TITLE	"���߂Ă�3D�V���[�e�B���O"
#define APP_NAME	"3DSTG"
#define PI			 3.14159265358979323846

//�\����.
//�J�������.
struct CAMERA
{
	D3DXVECTOR3	vEye;		//�J�����ʒu.
	D3DXVECTOR3 vLook;		//�J���������ʒu.
	float		Yaw;		//Y��]��.
	D3DXMATRIX	mRotation;	//��]�s��.

};
//�����蔻��ꏊ���.
struct COLLSIONBOX
{
	D3DXVECTOR3	MinPos;
	float	m_MinX;
	float	m_MinY;
	float	m_MinZ;

	D3DXVECTOR3	MaxPos;
	float	m_MaxX;
	float	m_MaxY;
	float	m_MaxZ;

};

enum SQUARE
{
	L3,CV33,CV35,CV38
};

enum UPDOWN
{
	S35,ARL44
};

enum SAWMOVE
{
	MARK1,MARK2
};

enum NEEDLEMOVE
{
	M4SHA,M4A1SHA
};

enum SLOWDOWN
{
	MOVE,RETURN
};

enum WALLMOVE
{
	PUSH,SLOWRETURN
};
/*************************************************
*	Ҳݸ׽.
**/
class clsMain
{
public:
	clsMain();
	~clsMain();

	//����޳�������֐�.
	HRESULT InitWindow(HINSTANCE hInstance,INT iX, INT iY, INT iWidth, INT iHeight,LPSTR WindowName);

	LRESULT MsgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam);

	void Loop();
	void AppMain();

private:
	HWND	m_hWnd;


//�ȍ~��DirectX�֌W.
public:
	HRESULT Init3D();
	void DestroyD3D();
	void Render();

	/************�V�[�����̏���*************/

	void Title();		//�^�C�g������.
	void Main();		//���C������.
	void Clear();		//�N���A����.
	void Over();		//�I�[�o�[����.

	void P_ACT();		//�v���C���[����.
	void E_ACT();		//�G������.
	void B_ACT();		//�{�X����.

	/***************************************/
	
	/***********************�Ǎ��n****************************/

	void LoadModel();		//���ٓǍ��֐�.
	void LoadSound();		//�����Ǎ��֐�.
	void LoadPosition();	//������W�Ǎ��֐�.

	/**********************************************************/

	/*****************����n*******************/
	
	void ScaffSqu();
	void UpDown();
	void SlowDown();

	/******************************************/

	/*****************��Q���n*******************/

	void SawControll();
	void NeedleControll();
	void WallControll();

	/********************************************/





	//�J�����֐�.
	void Camera();
	//��ۼު���݊֐�.
	void Proj();
	/*******************�����蔻��֘A*************************/
	//�̨��쐬.
	HRESULT InitSphere(clsDx9Mesh* pMesh);
	//���Փ˔���.
	bool Collision(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget);
	//�޳��ިݸ��ޯ���쐬.
	HRESULT	InitBBox(clsDx9Mesh* pMesh);
	//���Փ˔���.
	bool BBoxCollision(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget);

	/**********************************************************/

	


private:
	ID3D11Device*	m_pDevice;
	ID3D11DeviceContext* m_pContext;
	IDXGISwapChain*		 m_pSwapChain;
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;
	ID3D11Texture2D*	m_pBackBuffer_DSTex;
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;




	ID3D11SamplerState*	m_pSampleLinear;	//ø����̻���� ø����Ɋe��̨����������.
	ID3D11ShaderResourceView* m_pTexture;	//ø���.
	CAMERA			m_Camera;	//�J�������.
	D3DXMATRIX		m_mView;	//�r���[(�J�����s��).
	D3DXMATRIX		m_mProj;	//�v���W�F�N�V�����s��.
	D3DXVECTOR3		m_vLight;	//ײĂ̕���.
	D3DXVECTOR3		m_acc;		//����
	clsDx9Mesh*		m_pClsDx9Mesh;//Dx9ү���׽.
	
	COLLSIONBOX		CollB;

	clsDebugText*	m_pDebugText;
	clsSprite2D*	m_pSprite2D;
	clsDx9Mesh*		m_pSphere;	//�̨���޼ު��.

	/****************���f���錾*****************/
	clsDx9Mesh*		m_pGround;
	clsDx9Mesh*		m_aGround[G_MAX];
	clsDx9Mesh*		m_pPlayer;

	clsDx9Mesh*		m_aStandard;

	clsDx9Mesh*		m_aScafSqu;
	clsDx9Mesh*		m_aScafSquM;
	clsDx9Mesh*		m_aScafUp;
	clsDx9Mesh*		m_aScafDown;
	clsDx9Mesh*		m_aScaf_Paste;
	clsDx9Mesh*		m_aScaf_PasteOn;

	clsDx9Mesh*		m_aSaw;
	clsDx9Mesh*		m_aSawCover;
	clsDx9Mesh*		m_aNeedle;
	clsDx9Mesh*		m_aNeedleSta;
	clsDx9Mesh*		m_aWallMove;
	/********************************************/


	/*****************�����錾*******************/
	clsSound		m_sTitle;

	/********************************************/

};