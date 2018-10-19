#include "Obstacle.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";

//‚Ü‚í‚é‚â‚Â.
int SawControllCnt = 0;
int SAW = LEFT;
float SawSpeed = 0;
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
	m_aSaw->m_Scale = 0.8f;

	m_aSawCover->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\cover.x");
	m_aSawCover->m_vPos = D3DXVECTOR3(-1.3f, 3.45f, 14.1);
	
	m_aNeedle->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\needle.x");
	m_aNeedle->m_vPos = D3DXVECTOR3(2.72f, 5.4f, 33.0f);


	m_aWallMove->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Obstacle\\Wall.x");
	m_aWallMove->m_vPos = D3DXVECTOR3(7.5f, 4.5f, 46.5f);

}

void clsObst::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	m_aSaw->Render(mView, mProj, vLight, vEye);
	m_aSawCover->Render(mView, mProj, vLight, vEye);

	m_aNeedle->Render(mView, mProj, vLight, vEye);

	m_aWallMove->Render(mView, mProj, vLight, vEye);



}



/*áŠQ•¨*/
void clsObst::SawControll()
{
	m_aSaw->m_Roll += 0.5f;
	SawControllCnt++;

	switch (SAW)
	{
	case LEFT:
		SawSpeed += 0.02;

		m_aSaw->m_vPos.x += 0.02f * SawSpeed;
		if (SawSpeed >= 3.6)
		{
			SawSpeed = 3.6;
			m_aSaw->m_vPos.x = 5.815996;
			SAW = RIGHT;

		}


		break;
	case RIGHT:
		SawSpeed -= 0.02;
		m_aSaw->m_vPos.x -= 0.02f*SawSpeed;
		if (SawSpeed <= 0.0)
		{
			SawSpeed = 0;
			m_aSaw->m_vPos.x = -0.628009;
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
			m_aNeedle->m_vPos.y = 5.4f;

			Needle = NOUT;
		}

		break;
	case NOUT:
		if (NeedleControllCnt > 110)
		{
			m_aNeedle->m_vPos.y -= 0.01f;
			if (m_aNeedle->m_vPos.y < 4.45f)
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

			if (m_aWallMove->m_vPos.x < 0.0f)
			{
				WallCnt = SLOWRETURN;
			}
		}



		break;
	case SLOWRETURN:
		m_aWallMove->m_vPos.x += 0.02;
		if (m_aWallMove->m_vPos.x > 6.0)
		{
			PushCnt = 0;
			PushSpeed = 0.00f;
			WallCnt = PUSH;
		}


		break;
	}


}
