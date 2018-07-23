//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���. 4005:�Ē�`.
#pragma warning(disable:4005)

#include <Windows.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>

#include "DX9Mesh.h"	//Dx9���g�p����׽.
#include "Sprite.h"		//����غ��(���ײ�)�׽.
#include "DebugText.h"	//���ޯ��÷�ĸ׽.
#include "Sound.h"		//����޸׽.
#include "Sprite2D.h"
//ײ����.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.


//�萔.
#define WND_TITLE	"���߂Ă�3D�V���[�e�B���O"
#define APP_NAME	"3DSTG"

//�\����.
//�J�������.

struct CAMERA
{
	D3DXVECTOR3	vEye;		//�J�����ʒu.
	D3DXVECTOR3 vLook;		//�J���������ʒu.
	float		Yaw;		//Y��]��.
	D3DXMATRIX	mRotation;	//��]�s��.

};


/*************************************************
*	Ҳݸ׽.
**/
class clsMain
{
public://public �O�����籸���\.
	clsMain();	//�ݽ�׸�.
	~clsMain();	//�޽�׸�.

	//����޳�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT iX, INT iY, INT iWidth, INT iHeight,
		LPSTR WindowName);

	//����޳�֐�(ү���ޖ��̏���)
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

	//ү����ٰ��.
	void Loop();
	//���ع����Ҳݏ���.
	void AppMain();

private://private �O�����籸���s�\.
	HWND	m_hWnd;//����޳�����.


//�ȍ~��DirectX�֌W.
public:
	//DirectX������.
	HRESULT Init3D();
	//Direct3D�I������.
	void DestroyD3D();


	//�`��(�����ݸ�).
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

	void ScaffSqu();

	/***********************�Ǎ��n****************************/

	void LoadModel();	//���ٓǍ��֐�.
	void LoadSound();	//�����Ǎ��֐�.
	/**********************************************************/

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
	// �����؂Ɉ����.
	ID3D11Device*	m_pDevice;//���޲���޼ު��.
	ID3D11DeviceContext* m_pContext;//���޲���÷��.
	IDXGISwapChain*		 m_pSwapChain;//�ܯ������.
	//���ް���ޯ��ޭ�.
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;
	//�ޯ��ޯ̧.
	ID3D11Texture2D*	m_pBackBuffer_DSTex;
	//���߽��ݼ��ޭ�.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;




	ID3D11SamplerState*	m_pSampleLinear;	//ø����̻���� ø����Ɋe��̨����������.
	ID3D11ShaderResourceView* m_pTexture;	//ø���.
	CAMERA			m_Camera;	//�J�������.
	D3DXMATRIX		m_mView;	//�r���[(�J�����s��).
	D3DXMATRIX		m_mProj;	//�v���W�F�N�V�����s��.
	D3DXVECTOR3		m_vLight;	//ײĂ̕���.
	clsDx9Mesh*		m_pClsDx9Mesh;//Dx9ү���׽.

	//���ޯ��÷�ĸ׽.
	clsDebugText*	m_pDebugText;

	//����ؗp(�A�j���L).
	clsSprite*		m_pExplosion;	//�����p.
	
	//�X�v���C�g2D�׽.
	clsSprite2D*	m_pSprite2D;

	//�޳��ިݸ޽̨��p.
	clsDx9Mesh*		m_pSphere;	//�̨���޼ު��.

	/****************���f���錾*****************/
	clsDx9Mesh*		m_pGround;
	clsDx9Mesh*		m_pPlayer;

	clsDx9Mesh*		m_aScafSqu;
	clsDx9Mesh*		m_aScafSquM;

	/********************************************/


	/*****************�����錾*******************/
	clsSound		m_sTitle;

	/********************************************/

};