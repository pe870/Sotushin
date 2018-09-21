#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <stdio.h>
#include <math.h>


#include "Global.h"
#include "DX9Mesh.h"
#include "CRay.h"



#define PI			 3.14159265358979323846

class clsPlayer
{
public:
	clsPlayer(){};
	~clsPlayer(){};

	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11);


	void LoadModel();
	void Render(D3DXMATRIX &mView, D3DXMATRIX &mProj,D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);

	void P_ACT();


	void Camera(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float yaw);


	//レイの判定関数,
	void RayCollsion(clsDx9Mesh* pTarget);

private:
	HWND						m_hWnd11;

	ID3D11Device*				m_pDevice11;
	ID3D11DeviceContext*		m_pContext11;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

	D3DXMATRIX					m_mView;	//ビュー(カメラ行列).
	D3DXMATRIX					m_mProj;	//プロジェクション行列.
	D3DXVECTOR3					m_vLight;	//ﾗｲﾄの方向.


	//レイとメッシュの判定.
	bool Intersect(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget,
		float* pfDistance, D3DXVECTOR3* pIntersect);

	//交差位置のポリゴンの頂点を見つける.
	HRESULT	FindVerticesOnPoly(
		LPD3DXMESH	pMeshForRay, DWORD	dwPolyIndex,D3DXVECTOR3* pVecVertices);


	clsDx9Mesh*		m_pPlayer;
	
	clsRay*			m_pRayV;	//レイ表示クラス V=Verticle. 垂直.

	D3DXVECTOR3		m_acc;		//加速



};


#endif