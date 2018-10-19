#include "Enemy.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";




HRESULT clsEnemy::Init(
	HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd11 = hWnd;
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;
	for (int i = 0; i < E_MAX; i++)	{
		m_aEnemy[i] = new clsDx9Mesh;

		m_aEnemySearch[i] = new clsDx9Mesh;

	}

	return S_OK;
}

void clsEnemy::LoadModel()
{
	E_Reset[0].ResetPos = D3DXVECTOR3(2.7f, 0.0f, -6.0f + 1.0);
	E_Reset[1].ResetPos = D3DXVECTOR3(2.7f, 0.0f, -6.0f + 2.0);
	E_Reset[2].ResetPos = D3DXVECTOR3(2.7f, 0.0f, -6.0f + 3.0);
	E_Reset[3].ResetPos = D3DXVECTOR3(2.7f, 0.0f, -6.0f + 4.0);
	E_Reset[4].ResetPos = D3DXVECTOR3(2.7f, 0.0f, -6.0f + 5.0);

	for (int i = 0; i < E_MAX; i++)
	{
		m_aEnemy[i]->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Enemy\\enemy.x");
		m_aEnemy[i]->m_vPos = E_Reset[i].ResetPos;

	}
	for (int i = 0; i < E_MAX; i++)
	{
		m_aEnemySearch[i]->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Enemy\\enemysearth.x");
		m_aEnemySearch[i]->m_vPos.x = m_aEnemy[i]->m_vPos.x;
		m_aEnemySearch[i]->m_vPos.z = m_aEnemy[i]->m_vPos.z;
		m_aEnemySearch[i]->m_vPos.y = m_aEnemy[i]->m_vPos.y - 0.0368f;

	}

}

void clsEnemy::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_aEnemy[i]->Render(mView, mProj, vLight, vEye);
		m_aEnemySearch[i]->Render(mView, mProj, vLight, vEye);

	}

}

void clsEnemy::E_ACT()
{


	E_moveCnt++;


	//間隔往復、発見したら自機によってくる
	for (int i = 0; i < E_MAX; i++)
	{
		if (!SEARCH_EX[i])
		{
			if (i % 2 == 0)
			{

				if (E_moveCnt < 100)
				{
					m_aEnemy[i]->m_vPos.x += 0.03f;
					m_aEnemySearch[i]->m_vPos.x += 0.03f;
				}
				if (101 < E_moveCnt && E_moveCnt < 170)
				{
					m_aEnemy[i]->m_vPos.x += 0.0f;
					m_aEnemy[i]->m_Yaw += 0.045f;
					m_aEnemySearch[i]->m_vPos.x += 0.0f;

				}

				if (171 <= E_moveCnt && E_moveCnt < 270)
				{
					m_aEnemy[i]->m_vPos.x -= 0.03f;
					m_aEnemySearch[i]->m_vPos.x -= 0.03f;

				}

				if (271 < E_moveCnt && E_moveCnt < 320)
				{
					m_aEnemy[i]->m_vPos.x -= 0.0f;
					m_aEnemySearch[i]->m_vPos.x += 0.0f;
					m_aEnemy[i]->m_Yaw -= 0.045f;

				}

			}

		}

		if (!SEARCH_EZ[i])
		{
			if (i % 2 == 1)
			{

				if (E_moveCnt < 100)
				{
					m_aEnemy[i]->m_vPos.z += 0.03f;
					m_aEnemySearch[i]->m_vPos.z += 0.03f;
				}
				if (101 < E_moveCnt && E_moveCnt < 170)
				{
					m_aEnemy[i]->m_vPos.z += 0.0f;
					m_aEnemySearch[i]->m_vPos.z += 0.0f;

				}

				if (171 <= E_moveCnt && E_moveCnt < 270)
				{
					m_aEnemy[i]->m_vPos.z -= 0.03f;
					m_aEnemySearch[i]->m_vPos.z -= 0.03f;

				}

				if (271 < E_moveCnt && E_moveCnt < 320)
				{
					m_aEnemy[i]->m_vPos.z -= 0.0f;
					m_aEnemySearch[i]->m_vPos.z += 0.0f;

				}

			}





		}


	}




			//2つのパターンの⑴行動後の初期化処理
			if (321 < E_moveCnt)
			{
					E_moveCnt = 0;

			}

	


}
