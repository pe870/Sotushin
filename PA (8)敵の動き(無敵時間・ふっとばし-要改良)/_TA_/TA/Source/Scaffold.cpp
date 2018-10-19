#include "Scaffold.h"

int Square = FIRST;
int scaffoldCntSqu = 0;
int UPDown = UPLEFT;
int UpDownCnt = 0;
int DOWNUp = DOWNRIGHT;
int FishBlock = RETURN;
int SlowDownCnt = 0;
bool ColorChange = false;


float UpSpeed = 3.0f;
float DownSpeed = 0.0f;
float TikuwaSpeed = 0.0f;
//初期化
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


	m_pDebugText = new clsDebugText;

	D3DXVECTOR4 vColor(1.0f, 0.0f, 0.0f, 1.0f);

	if (FAILED(m_pDebugText->Init(m_pContext11, WND_W, WND_H, 50.0f, vColor)))
	{
		//return;
	}





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
	m_aScafUp->m_vPos = D3DXVECTOR3(1.1f, -1.0, 24.2f);

	m_aScafDown->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Scaffold\\updown.x");
	m_aScafDown->m_vPos = D3DXVECTOR3(4.5f, 3.2f, 24.2f);

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


	//デバッグテキスト.
	char strDebugText[256];
	sprintf_s(strDebugText, " UpY : %f DownY : %f "
		, m_aScafUp->m_vPos.y, m_aScafDown->m_vPos.y);
	//テキスト描画.
	m_pDebugText->Render(strDebugText, 0.0f, 5.0f);

}
//当たり判定まだ.
void clsScaff::ScaffSqu()
{
		scaffoldCntSqu++;


		switch (Square)
		{
		case FIRST:	//ok
			if (0 <= scaffoldCntSqu && 340 > scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x += 0.01f;
				m_aScafSquM->m_vPos.x -= 0.01f;

			}
			if (340 <= scaffoldCntSqu )
			{
				m_aScafSqu->m_vPos.x = 4.4f;
				m_aScafSquM->m_vPos.x = 1.0f;
			}
			if (380 < scaffoldCntSqu )
				Square = SECOND;

			break;
		case SECOND:	//ok
			if (380 <= scaffoldCntSqu && 789 >= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.z += 0.01f;
				m_aScafSqu->m_vPos.y += 0.01f;

			}

			m_aScafSquM->m_vPos.z -= 0.01f;
			m_aScafSquM->m_vPos.y -= 0.01f;
			if (789 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.y = 4.2f;
				m_aScafSqu->m_vPos.z = 11.0f;
				m_aScafSquM->m_vPos.y = 0.1f;
				m_aScafSquM->m_vPos.z = 7.0f;

			}
			if (820 < scaffoldCntSqu)
				Square = THIRD;

			break;
		case THIRD:
			if (820 <= scaffoldCntSqu && 1159 >= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x -= 0.01f;
				m_aScafSquM->m_vPos.x += 0.01f;

			}

			if (1159 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x = 1.0f;
				m_aScafSquM->m_vPos.x = 4.4f;

			}
			if (1199 < scaffoldCntSqu)
			Square = FOURS;

			break;
		case FOURS:
			if (1199 <= scaffoldCntSqu && 1608 >= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.z -= 0.01f;
				m_aScafSqu->m_vPos.y -= 0.01f;
				m_aScafSquM->m_vPos.z += 0.01f;
				m_aScafSquM->m_vPos.y += 0.01f;

			}

			if (1608 <= scaffoldCntSqu)
			{
				m_aScafSqu->m_vPos.x = 1.0f;
				m_aScafSqu->m_vPos.y = 0.1f;
				m_aScafSqu->m_vPos.z = 7.0f;
				m_aScafSquM->m_vPos.x = 4.4f;
				m_aScafSquM->m_vPos.y = 4.2f;
				m_aScafSquM->m_vPos.z = 11.0f;

			}
			if (1649 <= scaffoldCntSqu)
			{
				Square = FIRST;
				scaffoldCntSqu = 0;

			}

			break;

		}







	}

//当たり判定まだ.
void clsScaff::UpDown()
{
	
	switch (UPDown)
	{
	case UPLEFT:
		UpSpeed -= 0.03;
		m_aScafUp->m_vPos.y += 0.03f*UpSpeed;

		
		if (UpSpeed<0.0)
		{
			UpSpeed = 0.0;

			m_aScafUp->m_vPos = D3DXVECTOR3(1.1f, 3.22f, 24.2f);



			UPDown = DOWNLEFT;

		}


		break;
	case DOWNLEFT:
		UpSpeed += 0.03;
		m_aScafUp->m_vPos.y -= 0.03f*UpSpeed;


		if (UpSpeed >= 3.0)
		{
			m_aScafUp->m_vPos = D3DXVECTOR3(1.1f, -1.2, 24.2f);
			UpSpeed = 3.0f;

			UPDown = UPLEFT;

		}

		break;
	}

	switch (DOWNUp)
	{
	case DOWNRIGHT:
		DownSpeed += 0.03f;
		m_aScafDown->m_vPos.y -= 0.03f*DownSpeed;
		if (DownSpeed >= 3.0)
		{
			m_aScafDown->m_vPos = D3DXVECTOR3(4.5f, -1.34f, 24.2f);

			DownSpeed = 3.0f;


			DOWNUp = UPRIGHT;

		}


		break;

	case UPRIGHT:
		DownSpeed -= 0.03f;
		m_aScafDown->m_vPos.y += 0.03f*DownSpeed;
		if (DownSpeed < 0.0)
		{
			DownSpeed = 0.0f;


			m_aScafDown->m_vPos = D3DXVECTOR3(4.5f, 3.11f, 24.2f);



			DOWNUp = DOWNRIGHT;

		}


		break;
	}

}

//当たり判定まだ.
void clsScaff::SlowDown()
{

	if (GetAsyncKeyState('V') & 0x0001)
	{
		ColorChange = true;
	}
	if (GetAsyncKeyState('B') & 0x0001)
	{
		ColorChange = false;
	}

	if (ColorChange)
		FishBlock = MOVE;
	if (!ColorChange)
		FishBlock = RETURN;


	switch (FishBlock)
	{
	case MOVE:

		SlowDownCnt++;

		if (SlowDownCnt > 250)
		{
			TikuwaSpeed += 0.03f;
			m_aScaf_PasteOn->m_vPos.y -= 0.03*TikuwaSpeed;
			if (SlowDownCnt>400)
			{
				m_aScaf_PasteOn->m_vPos.y = 4.0f;
				ColorChange = false;
				TikuwaSpeed = 0.0f;
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

