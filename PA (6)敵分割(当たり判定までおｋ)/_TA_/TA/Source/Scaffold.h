#ifndef SCAFFOLD_H
#define SCAFFOLD_H

#include <Windows.h>
#include <stdio.h>
#include "DebugText.h"

#include "Global.h"
#include "DX9Mesh.h"

//四角　足場1.
enum SQUARE
{
	FIRST, SECOND, THIRD, FOURS
};

//上下　足場2.
enum DOWNUPLEFT
{
	UPLEFT, DOWNLEFT
};
enum DOWNUPRIGHT
{
	 DOWNRIGHT,UPRIGHT

};
//ちくわ　足場3.
enum FISHBLOCK
{
	MOVE, RETURN
};

class clsScaff
{
public:
	clsScaff(){};
	~clsScaff(){};

	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	void LoadModel();
	void Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);


	void ScaffSqu();
	void UpDown();
	void SlowDown();

private:
	HWND						m_hWnd11;

	ID3D11Device*				m_pDevice11;
	ID3D11DeviceContext*		m_pContext11;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

	D3DXMATRIX					m_mView;
	D3DXMATRIX					m_mProj;
	D3DXVECTOR3					m_vLight;

	clsDebugText*	m_pDebugText;


	clsDx9Mesh*		m_aScafSqu;
	clsDx9Mesh*		m_aScafSquM;
	clsDx9Mesh*		m_aScafUp;
	clsDx9Mesh*		m_aScafDown;
	clsDx9Mesh*		m_aScaf_Paste;
	clsDx9Mesh*		m_aScaf_PasteOn;


};

#endif