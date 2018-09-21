#include "Scaffold.h"

int Square = FIRST;
int scaffoldCntSqu = 0;
int UPDown = UP;
int UpDownCnt = 0;
int FishBlock = RETURN;
int SlowDownCnt = 0;
bool ColorChange = false;
//‰Šú‰»
HRESULT clsScaff::Init(
	HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd11 = hWnd;
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	m_aScafSqu = new clsDx9Mesh;
	m_aScafSquM = new clsDx9Mesh;
	m_aScafUp = new clsDx9Mesh;
	m_aScafDown = new clsDx9Mesh;
	m_aScaf_Paste = new clsDx9Mesh;
	m_aScaf_PasteOn = new clsDx9Mesh;

	return S_OK;
}

void clsScaff::LoadModel()
{
	m_aScafSqu->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\square.x");
	m_aScafSqu->m_vPos = D3DXVECTOR3(1.0f, 0.1f, 7.0f);
	m_aScafSqu->m_Scale = 0.6f;

	m_aScafSquM->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\square.x");
	m_aScafSquM->m_vPos = D3DXVECTOR3(4.4f, 4.2f, 11.0f);
	m_aScafSquM->m_Scale = 0.6f;

	m_aScafUp->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\updown.x");
	m_aScafUp->m_vPos = D3DXVECTOR3(0.9f, -0.9f, 24.2f);

	m_aScafDown->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\updown.x");
	m_aScafDown->m_vPos = D3DXVECTOR3(4.5f, -4.8, 24.2f);

	m_aScaf_Paste->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\slowdown1.x");
	m_aScaf_Paste->m_vPos = D3DXVECTOR3(4.5f, 4.0f, 40.0f);
	m_aScaf_Paste->m_Scale = 1.2f;

	m_aScaf_PasteOn->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\slowdown2.x");
	m_aScaf_PasteOn->m_vPos = D3DXVECTOR3(4.5f, 4.0f, 40.0f);
	m_aScaf_PasteOn->m_Scale = 1.2f;

}

void clsScaff::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	m_aScafSqu->Render(mView, mProj, vLight,vEye);
	m_aScafSquM->Render(mView, mProj, vLight,vEye);

	m_aScafUp->Render(mView, mProj, vLight,vEye);
	m_aScafDown->Render(mView, mProj, vLight,vEye);

	switch (FishBlock)
	{
	case MOVE:
		m_aScaf_PasteOn->Render(mView, mProj, vLight,vEye);

		break;
	case RETURN:
		m_aScaf_Paste->Render(mView, mProj, vLight,vEye);

		break;


	}
}

void clsScaff::ScaffSqu()
{
		scaffoldCntSqu++;


		switch (Square)
		{
		case FIRST:
			m_aScafSqu->m_vPos.x += 0.01f;
			m_aScafSquM->m_vPos.x -= 0.01f;
			if (340 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x = 4.4f;
				m_aScafSquM->m_vPos.x = 1.0f;
				Square = SECOND;
			}
			break;
		case SECOND:
			m_aScafSqu->m_vPos.z += 0.01f;
			m_aScafSqu->m_vPos.y += 0.01f;

			m_aScafSquM->m_vPos.z -= 0.01f;
			m_aScafSquM->m_vPos.y -= 0.01f;
			if (739 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.y = 4.2f;
				m_aScafSqu->m_vPos.z = 11.0f;
				m_aScafSquM->m_vPos.y = 0.1f;
				m_aScafSquM->m_vPos.z = 7.0f;

				Square = THIRD;
			}
			break;
		case THIRD:
			m_aScafSqu->m_vPos.x -= 0.01f;
			m_aScafSquM->m_vPos.x += 0.01f;

			if (1079 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x = 1.0f;
				m_aScafSquM->m_vPos.x = 4.4f;

				Square = FOURS;
			}
			break;
		case FOURS:
			m_aScafSqu->m_vPos.z -= 0.01f;
			m_aScafSqu->m_vPos.y -= 0.01f;
			m_aScafSquM->m_vPos.z += 0.01f;
			m_aScafSquM->m_vPos.y += 0.01f;

			if (1490 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x = 1.0f;
				m_aScafSqu->m_vPos.y = 0.1f;
				m_aScafSqu->m_vPos.z = 7.0f;
				m_aScafSquM->m_vPos.x = 4.4f;
				m_aScafSquM->m_vPos.y = 4.2f;
				m_aScafSquM->m_vPos.z = 11.0f;
				scaffoldCntSqu = 0;

				Square = FIRST;
			}
			break;

		}







	}

void clsScaff::UpDown()
{
	UpDownCnt++;
	switch (UPDown)
	{
	case UP:
		m_aScafUp->m_vPos.y -= 0.03f;
		m_aScafDown->m_vPos.y += 0.03f;
		if (UpDownCnt>130)
		{
			m_aScafUp->m_vPos.y -= 0.00f;
			m_aScafDown->m_vPos.y += 0.000f;

			m_aScafUp->m_vPos.y = -4.8f;
			m_aScafDown->m_vPos.y = -0.89f;
			if (UpDownCnt > 150)
			{
				UPDown = DOWN;

			}
		}

		break;
	case DOWN:

		m_aScafUp->m_vPos.y += 0.03f;
		m_aScafDown->m_vPos.y -= 0.03f;
		if (UpDownCnt>280)
		{
			m_aScafUp->m_vPos.y -= 0.00f;
			m_aScafDown->m_vPos.y += 0.000f;

			m_aScafUp->m_vPos.y = -0.89f;
			m_aScafDown->m_vPos.y = -4.8f;
			if (UpDownCnt > 300)
			{
				UpDownCnt = 0;
				UPDown = UP;

			}
		}


		break;
	}

}

void clsScaff::SlowDown()
{

	if (ColorChange)			FishBlock = MOVE;
	if (!ColorChange)			FishBlock = RETURN;


	switch (FishBlock)
	{
	case MOVE:

		SlowDownCnt++;
		if (SlowDownCnt > 250)
		{
			m_aScaf_PasteOn->m_vPos.y -= 0.07;
			if (SlowDownCnt>300)
			{
				m_aScaf_PasteOn->m_vPos.y = 4.0f;
				FishBlock = RETURN;
			}
		}


		break;
	case RETURN:

		SlowDownCnt = 0;
		m_aScaf_PasteOn->m_vPos.y = 4.0f;
		FishBlock = MOVE;


		break;
	}

}

