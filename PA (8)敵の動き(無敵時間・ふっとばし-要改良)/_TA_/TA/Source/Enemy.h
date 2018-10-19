#ifndef ENEMY_H
#define ENEMY_H

#include <Windows.h>
#include <stdio.h>
#include <math.h>


#include "Global.h"
#include "DX9Mesh.h"

const int E_MAX = 5;


struct E_RESET
{
	D3DXVECTOR3 ResetPos;
	float		ResetYaw;
};


class clsEnemy
{
public:
	clsEnemy()
	{
		for (int i = 0; i < E_MAX; i++)
		{
			E_ATTACKX[i] = false;	//ｘ方向に動くやつ
			E_ATTACKZ[i] = false;	//ｚ方向に動くやつ
		}
	};
	~clsEnemy(){};

	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11,ID3D11DeviceContext* pContext11);

	void LoadModel();
	void Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);

	void E_ACT();


	clsDx9Mesh*		m_aEnemy[E_MAX];
	clsDx9Mesh*		m_aEnemySearch[E_MAX];


	//メインでも使う.
	int E_moveCnt[E_MAX];
	bool SEARCH_EX[E_MAX];
	bool SEARCH_EZ[E_MAX];
	int E_SearchMoveCnt[E_MAX];

	bool E_ATTACKX[E_MAX];
	bool E_ATTACKZ[E_MAX];



private:
	HWND						m_hWnd11;

	ID3D11Device*				m_pDevice11;
	ID3D11DeviceContext*		m_pContext11;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

	D3DXMATRIX					m_mView;	//ビュー(カメラ行列).
	D3DXMATRIX					m_mProj;	//プロジェクション行列.
	D3DXVECTOR3					m_vLight;	//ﾗｲﾄの方向.

	E_RESET			E_Reset[E_MAX];



};

#endif