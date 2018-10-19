#include "Player.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";

int radian;

bool j_flg = true;			//�W�����v����������
float j_cnt = 0.0f;			//��Ԏ���

float wide = 90.0f;			//�e���L����p�x.
float center_direct = 0.0f;	//���S�̕���.
float direct = 0;			//���@�̌���


//������
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


	//���C�̏�����.
	m_pRayV->m_Ray.vPoint[0] = D3DXVECTOR3(0.0f,-0.1f, 0.0f);
	m_pRayV->m_Ray.vPoint[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_pRayV->Init(m_pDevice11, m_pContext11);

}

void clsPlayer::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{

	m_pPlayer->Render(mView, mProj, vLight,vEye);	//�u���@�v�̕\��.

	//Ray�̃����_�����O�i�����j.
	m_pRayV->m_Ray.vPos = m_pPlayer->m_vPos;	//�ʒu�����@�ɍ��킹��.
	//��]�������@�ɍ��킹��.
	m_pRayV->m_Ray.Yaw = m_pPlayer->m_Yaw;
	m_pRayV->Render(m_mView, m_mProj);


}

void clsPlayer::P_ACT()
{


	if (GetAsyncKeyState('J') & 0x8000)
	{
		m_pPlayer->m_vPos.y += 0.1f;

	}
	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_pPlayer->m_vPos.y -= 0.1f;

	}

	//�R���g���[�����͏��X�V
	m_tclsDInput->UpdateInputState();



	//���@�ړ� Dx9Mesh�ɗL.
	if (m_acc.y > 0.1f)
	{
		m_acc.y -= 0.011f;
	}
	else
	{
		m_acc.y = 0.00f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_R))
	{
		m_acc.x += 0.011f;
		if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_U))
		{
			if (direct > 135) direct += 3;
			if (direct <  45) direct += 3;
			else if (direct > 45) direct -= 3;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_D))
		{
			if (direct > 315) direct += 3;
			if (direct <  135) direct += 3;
			else if (direct > 135) direct -= 3;
		}
		if (direct < 90)	direct += 3;
		if (direct > 270)	direct += 3;
		else if (direct >= 90)	direct -= 3;

	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_L))
	{
		m_acc.x -= 0.011f;
		if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_U))
		{
			if (direct < 135) direct -= 3;
			if (direct <  315) direct += 3;
			else if (direct > 315) direct -= 3;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_D))
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
	if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_U))
	{
		m_acc.z += 0.011f;
		if (direct > 180)	direct += 3;
		else if (direct > 0)	direct -= 3;
		if (direct >= 360)	direct = 0;
		if (direct <= 0)	direct = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_D))
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
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 || m_tclsDInput->IsPressKey(enPKey_00))
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


	//�����x����
	if (m_acc.x >  0.05f) m_acc.x = 0.05f;
	if (m_acc.x < -0.05f) m_acc.x = -0.05f;
	if (m_acc.y >  1.00f) m_acc.y = 1.00f;
	if (m_acc.y < -0.10f) m_acc.y = -0.10f;
	if (m_acc.z >  0.05f) m_acc.z = 0.05f;
	if (m_acc.z < -0.05f) m_acc.z = -0.05f;

	//m_pPlayer->m_vPos.y -= 0.05f;

	//���̏�
	FloorCollision(m_pPlayer, -7.9f, -2.0f, -6.0f, -4.0f, -8.75f, 1.95f);

	//�����z�u�̏�
	FloorCollision(m_pPlayer, -3.0f, 8.25f, -1.0f, 0.0f, -11.5f, 0.0f);
	//RayCollsion(m_pGround);
	//�����z�u����̏o������
	FloorCollision(m_pPlayer, 0.25f, 5.35f, -1.0f, 0.0f, -12.0f, 5.5f);

	//��̑���
	FloorCollision(m_pPlayer, -0.25f, 5.75f, 1.5, 4.5f, 11.5f, 22.4f);

	//�㉜�̑���
	FloorCollision(m_pPlayer, -0.25f, 5.75f, 1.5f, 4.5f, 27.0f, 38.0f);

	//��ŉ��̑���
	FloorCollision(m_pPlayer, -0.25f, 5.75f, 1.5f, 4.5f, 41.2f, 52.0f);





	m_pPlayer->m_vPos.x += m_acc.x;
	m_pPlayer->m_vPos.y += m_acc.y;
	m_pPlayer->m_vPos.z += m_acc.z;



}


//��������
void clsPlayer::FloorCollision(clsDx9Mesh* m_pPlayer,
	float lx, float hx, float ly, float hy, float lz, float hz)
{
	if (m_pPlayer->m_vPos.y >= ly)
	{
		if (m_pPlayer->m_vPos.y <= hy)
		{
			if (m_pPlayer->m_vPos.x >= lx)
			{
				if (m_pPlayer->m_vPos.x < hx)
				{
					if (m_pPlayer->m_vPos.z >= lz)
					{
						if (m_pPlayer->m_vPos.z < hz)
						{
							m_pPlayer->m_vPos.y = hy;
							j_flg = true;
						}
					}
				}
			}
		}
	}
	if (m_pPlayer->m_vPos.y >= ly)
	{
		if (m_pPlayer->m_vPos.y < hy)
		{
			if (m_pPlayer->m_vPos.x >= lx - 0.1f)
			{
				if (m_pPlayer->m_vPos.x < lx)
				{
					if (m_pPlayer->m_vPos.z >= lz)
					{
						if (m_pPlayer->m_vPos.z < hz)
						{
							m_pPlayer->m_vPos.x = lx - 0.1f;
						}
					}
				}
			}
		}
	}
	if (m_pPlayer->m_vPos.y >= ly)
	{
		if (m_pPlayer->m_vPos.y <= hy)
		{
			if (m_pPlayer->m_vPos.x >= hx)
			{
				if (m_pPlayer->m_vPos.x < hx + 0.1f)
				{
					if (m_pPlayer->m_vPos.z >= lz + 0.1f)
					{
						if (m_pPlayer->m_vPos.z < hz)
						{
							m_pPlayer->m_vPos.x = hx + 0.1f;
						}
					}
				}
			}
		}
	}
	if (m_pPlayer->m_vPos.y >= ly)
	{
		if (m_pPlayer->m_vPos.y < hy)
		{
			if (m_pPlayer->m_vPos.x >= lx)
			{
				if (m_pPlayer->m_vPos.x < hx)
				{
					if (m_pPlayer->m_vPos.z >= lz - 0.1f)
					{
						if (m_pPlayer->m_vPos.z < lz)
						{
							m_pPlayer->m_vPos.z = lz - 0.1f;
						}
					}
				}
			}
		}
	}
	if (m_pPlayer->m_vPos.y >= ly)
	{
		if (m_pPlayer->m_vPos.y < hy)
		{
			if (m_pPlayer->m_vPos.x >= lx)
			{
				if (m_pPlayer->m_vPos.x < hx)
				{
					if (m_pPlayer->m_vPos.z >= hz)
					{
						if (m_pPlayer->m_vPos.z < hz + 0.1f)
						{
							m_pPlayer->m_vPos.z = hz + 0.1f;
						}
					}
				}
			}
		}
	}
}



void clsPlayer::Camera(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float yaw)
{
	vLook = vEye =m_pPlayer->m_vPos;
	yaw = m_pPlayer->m_Yaw;
}

bool clsPlayer::RayCollsion(clsDx9Mesh* pTarget)
{
	FLOAT	fDistance;	//����.
	D3DXVECTOR3	vIntersect;	//�������W.

	//���݈ʒu�̃R�s�[.
	m_pPlayer->m_vRay = m_pPlayer->m_vPos;
	//���C�̍��������@�̈ʒu����ɂ���.
	m_pPlayer->m_vRay.y = m_pPlayer->m_vPos.y + 2.0f;
	//���x�N�g���͐����ŉ�����.
	m_pPlayer->m_vAxis = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	bool bHit = false;
	bHit = Intersect(m_pPlayer, pTarget, &fDistance, &vIntersect);


	if (bHit == true)
	{
		return true;
	}
	return false;

	//��_�̍��W����y���W�Ƃ��ăZ�b�g.
	m_pPlayer->m_vPos.y = vIntersect.y +1.0f;

}



bool clsPlayer::Intersect(
	clsDx9Mesh* pAttacker,		//��̕���.
	clsDx9Mesh* pTarget,		//�Ώۂ̕���.
	float* pfDistance,			//(out)����.
	D3DXVECTOR3* pIntersect)	//(out)�������W.

{
	D3DXMATRIXA16	matRot;		//��]�s��.

	//��]�s����v�Z.
	D3DXMatrixRotationY(&matRot, pAttacker->m_Yaw);

	//���x�N�g���̗p��.
	D3DXVECTOR3	vecAxisZ;

	//Z�x�N�g�����̂��̂����݂̉�]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord
		(&vecAxisZ, &pAttacker->m_vAxis, &matRot);

	D3DXVECTOR3	vecStart, vecEnd, vecDistance;
	vecStart = vecEnd = pAttacker->m_vRay;	//���C�̈ʒu��ݒ�.

	vecEnd += vecAxisZ*1.0f;

	//��L�����̍��W�ɉ�]���W����������.
	//�t�����p����ΐ��������C��������.
	D3DXMATRIX matWorld;
	D3DXMATRIX matP;
	D3DXMatrixTranslation(&matP,
		pTarget->m_vPos.x, pTarget->m_vPos.y, pTarget->m_vPos.z);
	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS,
		pTarget->m_Scale, pTarget->m_Scale, pTarget->m_Scale);

	matWorld = matS*matP;

	//�t�s������߂�.
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	D3DXVec3TransformCoord(&vecStart, &vecStart, &matWorld);
	D3DXVec3TransformCoord(&vecEnd, &vecEnd, &matWorld);

	//���������߂�.
	vecDistance = vecEnd - vecStart;

	BOOL	bHit = false;//�����t���O.

	DWORD	dwIndex = 0;	//�C���f�b�N�X�ԍ�.
	D3DXVECTOR3 vVertex[3];	//���_���W.
	FLOAT U = 0, V = 0;		//(out)�d�S�q�b�g���W.

	//���C�ƃ��b�V���̌����𒲂ׂ�.
	D3DXIntersect(pTarget->m_pMeshForRay,	//�Ώۂ̃��b�V��.
		&vecStart,							//���C�̊J�n�ʒu.
		&vecDistance,						//���C�̋���.
		&bHit,								//(out)���茋��
		&dwIndex,							//(out)bHit��true���A
		//���C�̎��_�ɍł��߂��̖ʂ̲��ޯ���l�ւ̃|�C���^.
		&U, &V,								//(out)�d�S�q�b�g���W.
		pfDistance,							//�^�[�Q�b�g�Ƃ̋���.
		NULL, NULL);

	if (bHit == true)
	{
		//������.
		FindVerticesOnPoly
			(pTarget->m_pMeshForRay, dwIndex, vVertex);
		//�d�S���W�����_���Z�o����.
		//���[�J����_��v0 + U*(v1-v0)+v*(v2-v0)�ŋ��߂���/
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

//�����ʒu�̃|���S���̒��_��������.
//(���_���W�̓��[�J�����W)
HRESULT	clsPlayer::FindVerticesOnPoly(LPD3DXMESH	pMeshForRay, DWORD	dwPolyIndex,D3DXVECTOR3* pVecVertices)
{
	//���_���̃o�C�g�����擾.
	DWORD dwStride = pMeshForRay->GetNumBytesPerVertex();
	//���_�����擾����.
	DWORD dwVertexAmt = pMeshForRay->GetNumBytesPerVertex();
	//�ʐ��擾.
	DWORD dwPolyAmt = pMeshForRay->GetNumFaces();

	WORD* pwPoly = NULL;

	//�C���f�b�N�X�o�b�t�@�����b�N(�Ǎ����[�h)
	pMeshForRay->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = NULL;
	FLOAT* pfVertices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMeshForRay->GetVertexBuffer(&VB);

	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		//�|���S���̒��_�̂ЂƂڂ��擾.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//�|���S���̒��_�̂ӂ��ڂ��擾.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//�|���S���̒��_�݂̂��ڂ��擾.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pVecVertices[2].x = pfVertices[0];
		pVecVertices[2].y = pfVertices[1];
		pVecVertices[2].z = pfVertices[2];

		//���b�N����.
		pMeshForRay->UnlockIndexBuffer();
		VB->Unlock();

	}

	VB->Release();

	return S_OK;

}

