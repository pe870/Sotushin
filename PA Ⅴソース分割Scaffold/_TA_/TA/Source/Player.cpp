#include "Player.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";

int radian;

bool j_flg = true;			//ジャンプを押したか
float j_cnt = 0.0f;			//飛ぶ時間

float wide = 90.0f;			//弾が広がる角度.
float center_direct = 0.0f;	//中心の方向.
float direct = 0;			//自機の向き


//初期化
HRESULT clsPlayer::Init(
	HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd11 = hWnd;
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;
	m_pPlayer = new clsDx9Mesh;
	m_pRayV = new clsRay;

	return S_OK;
}


void clsPlayer::LoadModel()
{
	m_pPlayer->Init(m_hWnd11, m_pDevice11, m_pContext11, "Data\\Model\\Player\\player2.x");
	m_pPlayer->m_vPos = D3DXVECTOR3(2.7f, 0.0f, -6.0f);


	//レイの初期化.
	m_pRayV->m_Ray.vPoint[0] = D3DXVECTOR3(0.0f, -1.4f, 0.0f);
	m_pRayV->m_Ray.vPoint[1] = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_pRayV->Init(m_pDevice11, m_pContext11);

}

void clsPlayer::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{

	m_pPlayer->Render(mView, mProj, vLight,vEye);	//「自機」の表示.


	//Rayのレンダリング（垂直）.
	m_pRayV->m_Ray.vPos = m_pPlayer->m_vPos;	//位置を自機に合わせる.

	//回転軸を自機に合わせる.
	m_pRayV->m_Ray.Yaw = m_pPlayer->m_Yaw;
	m_pRayV->Render(m_mView, m_mProj);


}

void clsPlayer::P_ACT()
{
#ifndef DEBUG_
	if (GetAsyncKeyState('J') & 0x8000)
	{
		m_pPlayer->m_vPos.y += 0.1f;

	}
	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_pPlayer->m_vPos.y -= 0.1f;

	}
#endif

	//自機移動 Dx9Meshに有.
	if (m_acc.y > 0.1f)
	{
		m_acc.y -= 0.011f;
	}
	else
	{
		m_acc.y = 0.00f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_acc.x += 0.011f;
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (direct > 135) direct += 3;
			if (direct <  45) direct += 3;
			else if (direct > 45) direct -= 3;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (direct > 315) direct += 3;
			if (direct <  135) direct += 3;
			else if (direct > 135) direct -= 3;
		}
		if (direct < 90)	direct += 3;
		if (direct > 270)	direct += 3;
		else if (direct >= 90)	direct -= 3;

	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_acc.x -= 0.011f;
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (direct < 135) direct -= 3;
			if (direct <  315) direct += 3;
			else if (direct > 315) direct -= 3;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (direct > 45) direct += 3;
			if (direct > 225) direct -= 6;
			else if (direct <  225) direct += 3;
		}
		if (direct == 0)	direct = 359;
		if (direct < 270)	direct += 3;
		if (direct < 90)	direct -= 3;
		else if (direct >= 270)	direct -= 3;

	}
	else if (m_acc.x > 0) {
		m_acc.x -= m_acc.x * 0.06;
		if (m_acc.x < 0) m_acc.x = 0;
	}
	else if (m_acc.x < 0) {
		m_acc.x -= m_acc.x * 0.06;
		if (m_acc.x > 0) m_acc.x = 0;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_acc.z += 0.011f;
		if (direct > 180)	direct += 3;
		else if (direct > 0)	direct -= 3;
		if (direct >= 360)	direct = 0;
		if (direct <= 0)	direct = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_acc.z -= 0.011f;
		if (direct < 180)	direct += 3;
		else if (direct >= 180)	direct -= 3;
	}
	else if (m_acc.z > 0) {
		m_acc.z -= m_acc.z * 0.06;
		if (m_acc.z < 0) m_acc.z = 0;
	}
	else if (m_acc.z < 0) {
		m_acc.z -= m_acc.z * 0.06;
		if (m_acc.z > 0) m_acc.z = 0;
	}
	m_pPlayer->m_Yaw = direct / 180 * PI;
	if (direct > 360)	direct = 1;
	if (direct < 0)		direct = 359;

	if (j_flg == true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_acc.y += 5.00f;
			j_flg = false;
		}
	}
	else {
		if (m_acc.y > 0.00f)
		{
			m_acc.y -= m_acc.y * 0.5;
		}
		else if (m_acc.y < 0.00f)
		{
			m_acc.y += m_acc.y * 0.5;
		}
	}


	//加速度処理
	if (m_acc.x >  0.05f) m_acc.x = 0.05f;
	if (m_acc.x < -0.05f) m_acc.x = -0.05f;
	if (m_acc.y >  1.00f) m_acc.y = 1.00f;
	if (m_acc.y < -0.10f) m_acc.y = -0.10f;
	if (m_acc.z >  0.05f) m_acc.z = 0.05f;
	if (m_acc.z < -0.05f) m_acc.z = -0.05f;

	m_pPlayer->m_vPos.y -= 0.05f;

	//下の床
	if (m_pPlayer->m_vPos.x > -8.0f)
	{
		if (m_pPlayer->m_vPos.x < -1.9f)
		{
			if (m_pPlayer->m_vPos.z > -8.75f)
			{
				if (m_pPlayer->m_vPos.z < 2.0f)
				{
					if (m_pPlayer->m_vPos.y <= -4.0f)
					{
						if (m_pPlayer->m_vPos.y >= -6.0f)
						{
							m_pPlayer->m_vPos.y = -4.0f;
						}

					}
				}
			}
		}
	}

	//初期配置の床
	if (m_pPlayer->m_vPos.x > -3.0f)
	{
		if (m_pPlayer->m_vPos.x < 8.25f)
		{
			if (m_pPlayer->m_vPos.z > -11.5f)
			{
				if (m_pPlayer->m_vPos.z < 0.0f)
				{
					if (m_pPlayer->m_vPos.y <= 0.0f)
					{
						if (m_pPlayer->m_vPos.y >= -1.0f)
						{
							m_pPlayer->m_vPos.y = 0.0f;
							j_flg = true;
						}
					}
				}
			}
		}
	}

	//初期配置からの出っ張り
	if (m_pPlayer->m_vPos.x > 0.25f)
	{
		if (m_pPlayer->m_vPos.x < 5.35f)
		{
			if (m_pPlayer->m_vPos.z > -12.0f)
			{
				if (m_pPlayer->m_vPos.z < 5.5f)
				{
					if (m_pPlayer->m_vPos.y <= 0.0f)
					{
						if (m_pPlayer->m_vPos.y >= -1.0f)
						{
							m_pPlayer->m_vPos.y = 0.0f;
							j_flg = true;
						}
					}
				}
			}
		}
	}

	//上の足場
	if (m_pPlayer->m_vPos.x > -0.25f)
	{
		if (m_pPlayer->m_vPos.x < 5.75f)
		{
			if (m_pPlayer->m_vPos.z > 11.5f)
			{
				if (m_pPlayer->m_vPos.z < 22.4f)
				{
					if (m_pPlayer->m_vPos.y <= 4.5f)
					{
						if (m_pPlayer->m_vPos.y >= 1.5f)
						{
							m_pPlayer->m_vPos.y = 4.5f;
							j_flg = true;
						}
					}
				}
			}
		}
	}


	//上奥の足場
	if (m_pPlayer->m_vPos.x > -0.25f)
	{
		if (m_pPlayer->m_vPos.x < 5.75f)
		{
			if (m_pPlayer->m_vPos.z > 27.0f)
			{
				if (m_pPlayer->m_vPos.z < 38.0f)
				{
					if (m_pPlayer->m_vPos.y <= 4.5f)
					{
						if (m_pPlayer->m_vPos.y >= 1.5f)
						{
							m_pPlayer->m_vPos.y = 4.5f;
							j_flg = true;
						}
					}
				}
			}
		}
	}

	//上最奥の足場
	if (m_pPlayer->m_vPos.x > -0.25f)
	{
		if (m_pPlayer->m_vPos.x < 5.75f)
		{
			if (m_pPlayer->m_vPos.z > 41.2f)
			{
				if (m_pPlayer->m_vPos.z < 52.0f)
				{
					if (m_pPlayer->m_vPos.y <= 4.5f)
					{
						if (m_pPlayer->m_vPos.y >= 1.5f)
						{
							m_pPlayer->m_vPos.y = 4.5f;
							j_flg = true;
						}
					}
				}
			}
		}
	}



	m_pPlayer->m_vPos.x += m_acc.x;
	m_pPlayer->m_vPos.y += m_acc.y;
	m_pPlayer->m_vPos.z += m_acc.z;



}


void clsPlayer::Camera(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float yaw)
{
	vLook = vEye =m_pPlayer->m_vPos;
	yaw = m_pPlayer->m_Yaw;
}

void clsPlayer::RayCollsion(clsDx9Mesh* pTarget)
{
	FLOAT	fDistance;	//距離.
	D3DXVECTOR3	vIntersect;	//交差座標.

	//現在位置のコピー.
	m_pPlayer->m_vRay = m_pPlayer->m_vPos;
	//レイの高さを自機の位置より上にする.
	m_pPlayer->m_vRay.y = m_pPlayer->m_vPos.y + 2.0f;
	//軸ベクトルは垂直で下向き.
	m_pPlayer->m_vAxis = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	bool bHit = false;
	bHit = Intersect(m_pPlayer, pTarget, &fDistance, &vIntersect);


	if (bHit == true)
	{
		SetWindowText(m_hWnd11, "on the 足場");
	}
	else
	{
		SetWindowText(m_hWnd11, "");

	}

	//交点の座標からy座標としてセット.
	//m_pPlayer->m_vPos.y = vIntersect.y +1.0f;

}



bool clsPlayer::Intersect(
	clsDx9Mesh* pAttacker,		//基準の物体.
	clsDx9Mesh* pTarget,		//対象の物体.
	float* pfDistance,			//(out)距離.
	D3DXVECTOR3* pIntersect)	//(out)交差座標.

{
	D3DXMATRIXA16	matRot;		//回転行列.

	//回転行列を計算.
	D3DXMatrixRotationY(&matRot, pAttacker->m_Yaw);

	//軸ベクトルの用意.
	D3DXVECTOR3	vecAxisZ;

	//Zベクトルそのものを現在の回転状態により変換する.
	D3DXVec3TransformCoord
		(&vecAxisZ, &pAttacker->m_vAxis, &matRot);

	D3DXVECTOR3	vecStart, vecEnd, vecDistance;
	vecStart = vecEnd = pAttacker->m_vRay;	//レイの位置を設定.

	vecEnd += vecAxisZ*1.0f;

	//基準キャラの座標に回転座標を合成する.
	//逆光列を用いれば正しくレイが当たる.
	D3DXMATRIX matWorld;
	D3DXMATRIX matP;
	D3DXMatrixTranslation(&matP,
		pTarget->m_vPos.x, pTarget->m_vPos.y, pTarget->m_vPos.z);
	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS,
		pTarget->m_Scale, pTarget->m_Scale, pTarget->m_Scale);

	matWorld = matS*matP;

	//逆行列を求める.
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	D3DXVec3TransformCoord(&vecStart, &vecStart, &matWorld);
	D3DXVec3TransformCoord(&vecEnd, &vecEnd, &matWorld);

	//距離を求める.
	vecDistance = vecEnd - vecStart;

	BOOL	bHit = false;//命中フラグ.

	DWORD	dwIndex = 0;	//インデックス番号.
	D3DXVECTOR3 vVertex[3];	//頂点座標.
	FLOAT U = 0, V = 0;		//(out)重心ヒット座標.

	//レイとメッシュの交差を調べる.
	D3DXIntersect(pTarget->m_pMeshForRay,	//対象のメッシュ.
		&vecStart,							//レイの開始位置.
		&vecDistance,						//レイの距離.
		&bHit,								//(out)判定結果
		&dwIndex,							//(out)bHitがtrue時、
		//レイの視点に最も近くの面のｲﾝﾃﾞｯｸｽ値へのポインタ.
		&U, &V,								//(out)重心ヒット座標.
		pfDistance,							//ターゲットとの距離.
		NULL, NULL);

	if (bHit == true)
	{
		//命中時.
		FindVerticesOnPoly
			(pTarget->m_pMeshForRay, dwIndex, vVertex);
		//重心座標から交点を算出する.
		//ローカル交点はv0 + U*(v1-v0)+v*(v2-v0)で求められる/
		*pIntersect = vVertex[0]
			+ U * (vVertex[1] - vVertex[0])
			+ V * (vVertex[2] - vVertex[0]);

		//D3DXMatrixTranslation(&matP,
		//	pIntersect->x, pIntersect->y, pIntersect->z);
		//D3DXMatrixTranslation(&matS,
		//	pTarget->m_Scale, pTarget->m_Scale, pTarget->m_Scale);

		//matWorld = matS*matP;

		//pIntersect->x = matWorld._41;
		//pIntersect->y = matWorld._42;
		//pIntersect->z = matWorld._43;


		return true;
	}
	return false;


}

//交差位置のポリゴンの頂点を見つける.
//(頂点座標はローカル座標)
HRESULT	clsPlayer::FindVerticesOnPoly(LPD3DXMESH	pMeshForRay, DWORD	dwPolyIndex,D3DXVECTOR3* pVecVertices)
{
	//頂点毎のバイト数を取得.
	DWORD dwStride = pMeshForRay->GetNumBytesPerVertex();
	//頂点数を取得する.
	DWORD dwVertexAmt = pMeshForRay->GetNumBytesPerVertex();
	//面数取得.
	DWORD dwPolyAmt = pMeshForRay->GetNumFaces();

	WORD* pwPoly = NULL;

	//インデックスバッファをロック(読込モード)
	pMeshForRay->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = NULL;
	FLOAT* pfVertices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMeshForRay->GetVertexBuffer(&VB);

	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		//ポリゴンの頂点のひとつ目を取得.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//ポリゴンの頂点のふたつ目を取得.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//ポリゴンの頂点のみっつ目を取得.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pVecVertices[2].x = pfVertices[0];
		pVecVertices[2].y = pfVertices[1];
		pVecVertices[2].z = pfVertices[2];

		//ロック解除.
		pMeshForRay->UnlockIndexBuffer();
		VB->Unlock();

	}

	VB->Release();

	return S_OK;

}

