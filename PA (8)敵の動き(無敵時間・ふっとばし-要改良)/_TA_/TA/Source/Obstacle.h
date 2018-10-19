#ifndef OBSTACLE_H
#define OBSTACLE_H


#include <Windows.h>
#include <stdio.h>

#include "Global.h"
#include "DX9Mesh.h"


enum SAWMOVE
{
	LEFT, RIGHT
};

enum NEEDLEMOVE
{
	NIN, NOUT
};


enum WALLMOVE
{
	PUSH, SLOWRETURN
};


class clsObst
{
public:
	clsObst(){};
	~clsObst(){};


	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11,ID3D11DeviceContext* pContext11);


	void LoadModel();
	void Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);

	void ResetObstacle();

	void SawControll();
	void NeedleControll();
	void WallControll();

	clsDx9Mesh*		m_aSaw;
	clsDx9Mesh*		m_aSawCover;
	clsDx9Mesh*		m_aNeedle;
	clsDx9Mesh*		m_aNeedleSta;
	clsDx9Mesh*		m_aWallMove;


private:
	HWND						m_hWnd11;

	ID3D11Device*				m_pDevice11;
	ID3D11DeviceContext*		m_pContext11;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;
	
	D3DXMATRIX					m_mView;	
	D3DXMATRIX					m_mProj;
	D3DXVECTOR3					m_vLight;





};

#endif