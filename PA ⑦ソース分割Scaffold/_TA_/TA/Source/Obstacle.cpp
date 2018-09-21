#include "Obstacle.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";

//‚Ü‚í‚é‚â‚Â.
int SawControllCnt = 0;
int SAW = LEFT;

//ž™.
int NeedleControllCnt = 0;
int Needle = NIN;

//•Ç.
int PushCnt = 0;
float PushSpeed = 0.00f;
bool PushStanby = false;
int WallCnt = 0;


HRESULT clsObst::Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd11 = hWnd;
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	m_aSaw = new clsDx9Mesh;
	m_aSawCover = new clsDx9Mesh;
	m_aNeedle = new clsDx9Mesh;
	m_aNeedleSta = new clsDx9Mesh;
	m_aWallMove = new clsDx9Mesh;


	return S_OK;
}


void clsObst::LoadModel()
{
	m_aSaw->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\saw.x");
	m_aSaw->m_vPos = D3DXVECTOR3(-0.7f, 4.3f, 15.55f);
	m_aSaw->m_Pitch = 80.1f;
	m_aSaw->m_Scale = 0.6f;

	m_aSawCover->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\cover.x");
	m_aSawCover->m_vPos = D3DXVECTOR3(-0.8f, 3.45f, 14.1);

	m_aNeedle->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\needle.x");
	m_aNeedle->m_vPos = D3DXVECTOR3(2.55f, 2.4f, 33.0f);

	m_aNeedleSta->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\stature.x");
	m_aNeedleSta->m_vPos = D3DXVECTOR3(2.55f, 3.4f, 33.0f);

	m_aWallMove->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Ground\\ground.x");
	m_aWallMove->m_vPos = D3DXVECTOR3(7.5f, 5.0f, 45.0f);
	m_aWallMove->m_Scale = 0.6f;

}

void clsObst::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	m_aSaw->Render(mView, mProj, vLight, vEye);
	m_aSawCover->Render(mView, mProj, vLight, vEye);

	m_aNeedle->Render(mView, mProj, vLight, vEye);
	m_aNeedleSta->Render(mView, mProj, vLight, vEye);

	m_aWallMove->Render(mView, mProj, vLight, vEye);

}

void clsObstResetObstacle()
{

}


/*áŠQ•¨*/
void clsObst::SawControll()
{
	m_aSaw->m_Roll += 0.5f;
	SawControllCnt++;

	switch (SAW)
	{
	case LEFT:

		m_aSaw->m_vPos.x += 0.023f;
		if (280 < SawControllCnt)
		{
			m_aSaw->m_vPos.x = 5.7f;//3.6
			SAW = RIGHT;
		}


		break;
	case RIGHT:
		m_aSaw->m_vPos.x -= 0.023f;
		if (560 < SawControllCnt)
		{
			m_aSaw->m_vPos.x = -0.7f;
			SawControllCnt = 0;
			SAW = LEFT;
		}
		break;
	}

}

void clsObst::NeedleControll()
{

	NeedleControllCnt++;
	switch (Needle)
	{
	case NIN:
		if (NeedleControllCnt > 70)
		{
			m_aNeedle->m_vPos.y = 3.1f;

			Needle = NOUT;
		}

		break;
	case NOUT:
		if (NeedleControllCnt > 110)
		{
			m_aNeedle->m_vPos.y -= 0.01f;
			if (m_aNeedle->m_vPos.y < 2.4f)
			{
				NeedleControllCnt = 0;
				Needle = NIN;
			}
		}

		break;
	}

}

void clsObst::WallControll()
{


	switch (WallCnt)
	{
	case PUSH:
		PushCnt++;
		PushSpeed += 0.02;
		if (PushCnt > 100)
		{
			m_aWallMove->m_vPos.x -= 0.1*PushSpeed;

			if (m_aWallMove->m_vPos.x < 2.0f)
			{
				WallCnt = SLOWRETURN;
			}
		}



		break;
	case SLOWRETURN:
		m_aWallMove->m_vPos.x += 0.02;
		if (m_aWallMove->m_vPos.x > 8.0)
		{
			PushCnt = 0;
			PushSpeed = 0.00f;
			WallCnt = PUSH;
		}


		break;
	}


}
