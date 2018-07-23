#include "Main.h"
#include "Global.h"
#include "Position.h"
#include "MyMacro.h"
#include <stdio.h>

//��۰��ٕϐ�.
clsMain* g_pClsMain = NULL;

// Ҳ݊֐�.
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevinstance,PSTR IpCmdLine,INT nCmdShow)
{
	g_pClsMain = new clsMain;

	if (g_pClsMain != NULL)
	{
		//����޳�쐬����.
		if (SUCCEEDED(g_pClsMain->InitWindow(hInstance,0, 0,WND_W, WND_H,WND_TITLE)))
		{
			//DirectX11�p�̏�����.
			if (SUCCEEDED(g_pClsMain->Init3D()))
			{
				//ү����ٰ��.
				g_pClsMain->Loop();
			}
		}
		//�I��.
		g_pClsMain->DestroyD3D();
		delete g_pClsMain;//�׽�̔j��.
		g_pClsMain = NULL;
	}

	return 0;
}

// ����޳��ۼ��ެ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	//��ۼ��ެ�.
	return g_pClsMain->MsgProc(hWnd, uMsg, wParam, lParam);
}

//�ݽ�׸�.
clsMain::clsMain()
{
	ZeroMemory(this, sizeof(clsMain));

	m_hWnd = NULL;

	m_pDevice = NULL;
	m_pContext = NULL;
	m_pSwapChain = NULL;

	m_pBackBuffer_TexRTV = NULL;
	m_pBackBuffer_DSTex = NULL;
	m_pBackBuffer_DSTexDSV = NULL;

	m_pSampleLinear = NULL;
	m_pTexture = NULL;

	m_Camera.vEye = D3DXVECTOR3(0.0f, 3.7f, -10.0f);

	m_Camera.vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vLight = D3DXVECTOR3(0.0f, 0.5f, -1.0f);
}

//�޽�׸�.
clsMain::~clsMain()
{
}

//����޳�������֐�.
HRESULT clsMain::InitWindow(HINSTANCE hInstance,INT iX, INT iY,INT iWidth, INT iHeight,LPSTR WindowName)
{
	//����޳��`.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = APP_NAME;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//����޳�׽��Windows�ɓo�^.
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL,
			"����޳�׽�̓o�^�Ɏ��s", "�G���[", MB_OK);
		return E_FAIL;
	}

	//����޳�̍쐬.
	m_hWnd = CreateWindow(APP_NAME,WindowName,WS_OVERLAPPEDWINDOW,0, 0,iWidth, iHeight,NULL,NULL,hInstance,NULL);
	if (!m_hWnd)
	{
		MessageBox(NULL,"����޳�쐬�Ɏ��s", "�G���[", MB_OK);
		return E_FAIL;
	}

	//����޳�̕\��.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

//����޳�֐�(ү���ޖ��̏���)
LRESULT clsMain::MsgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch ((char)wParam){
		case VK_ESCAPE://ESC��.
			if (MessageBox(NULL,"����H","�x��", MB_YESNO) == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//ү����ٰ�߂Ʊ��ع���ݏ����̓����.
void clsMain::Loop()
{
	m_pDebugText = new clsDebugText;
	D3DXVECTOR4 vColor(1.0f, 0.0f, 0.0f, 1.0f);
	if (FAILED(m_pDebugText->Init(m_pContext, WND_W, WND_H, 50.0f, vColor)))
	{
		return;
	}

	LoadModel();

	//--------------�ڰ�ڰĒ�������.------------------------------
	
	float Rate = 0.0f;	//ڰ�.
	float FPS = 60.0f;	//FPS�l.
	DWORD sync_old = timeGetTime();	//�ߋ�����.
	DWORD sync_now;					//���ݎ���.
	//���ԏ����ׁ̈A�ŏ��P�ʂ�1�ؕb�ɕύX.
	timeBeginPeriod(1);

	//------------------------------------------------------------

	//ү����ٰ��.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		sync_now = timeGetTime();//���ݎ��Ԃ��擾.

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Rate = 1000.0f / FPS;	//���z���Ԃ��Z�o.
		if(sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;//���ݎ��Ԃɒu������.
			AppMain();
		}
	}
	//���ع���݂̏I��.
	timeEndPeriod(1);
}

//���ع���ݏ���.���؂�Ҳݏ���.
void clsMain::AppMain()
{
	//�x�^�\��m�F�p.
	if (GetAsyncKeyState('L') & 0x8000)
	{
		m_pSprite2D->m_Alpha += 0.01f;
		if (m_pSprite2D->m_Alpha > 1.0f)
		{
			m_pSprite2D->m_Alpha = 0.0f;
		}

	}

	ScaffSqu();


	//���@�ړ�. Dx9Mesh�ɗL.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pPlayer->m_eDir = enDirectioin_Left;
		//m_pPlayer->m_vPos.x -= 0.04f;
		//m_vCamera.x -= 0.04f;
		//m_vLook.x -= 0.04f;

	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pPlayer->m_eDir = enDirectioin_Right;
		//m_pPlayer->m_vPos.x += 0.04f;
		//m_vCamera.x += 0.04f;
		//m_vLook.x += 0.04f;

	}	
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pPlayer->m_eDir = enDirectioin_Forward;
		//m_pPlayer->m_vPos.z += 0.05f;
		//m_vCamera.z += 0.05f;
		//m_vLook.z += 0.05f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	
	{
		m_pPlayer->m_eDir = enDirectioin_Backward;
		//m_pPlayer->m_vPos.z -= 0.05f;
		//m_vCamera.z -= 0.05f;
		//m_vLook.z -= 0.05f;

	}	



	//�����ݸ�(�`��).
	Render();
}

//���(���)����ʂ������ݸ�(�`��).
void clsMain::Render()
{
	//��ʸر.
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//�ر�F(RGBA�̏�).
	//�װ�ޯ��ޯ̧.
	m_pContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);
	//���߽��ݼ��ޯ��ޯ̧.
	m_pContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f, 0);

	Camera();
	Proj();

	//ү���׽���������ݸ�.
	//m_pClsDx9Mesh->Render(mView, mProj, m_vLight, m_vCamera);

	//�u�n�ʁv�̕\��.
	m_pGround->Render(m_mView, m_mProj, m_vLight, m_Camera.vEye);
	//�u���@�v�̕\��.
	m_pPlayer->Render(m_mView, m_mProj, m_vLight, m_Camera.vEye);


	m_aScafSqu->Render(m_mView, m_mProj, m_vLight, m_Camera.vEye);
	m_aScafSquM->Render(m_mView, m_mProj, m_vLight, m_Camera.vEye);

	/*
	//���@�̨̽��̕\��.
	m_pSphere->m_vPos = m_pPlayer->m_vPos;	//���@�̈ʒu���߰.
	m_pSphere->m_Scale = m_pPlayer->m_Sphere.Radius * 2.0f;
	m_pSphere->Render(mView, mProj, m_vLight, m_vCamera);
	*/

	//�f�o�b�O�e�L�X�g.
	char strDebugText[256];
	sprintf_s(strDebugText,"Cnt[%d] X[%f] Y[%f] Z[%f]",
		scaffoldCntSpu, m_aScafSqu->m_vPos.x,
		m_aScafSqu->m_vPos.y, m_aScafSqu->m_vPos.z);
	//�e�L�X�g�`��.
	m_pDebugText->Render(strDebugText, 0.0f, 5.0f);


	//�X�v���C�g2D.
	m_pSprite2D->Render();


	//�����ݸނ��ꂽ�Ұ�ނ�\��.
	m_pSwapChain->Present(0, 0);
}

/****************�Ǎ��֐��R�[�i�[******************/
void clsMain::LoadModel()
{
	//ү���Ǎ�.
	//�u�n�ʁv.
	m_pGround = new clsDx9Mesh;
	m_pGround->Init(m_hWnd, m_pDevice, m_pContext,"Data\\Model\\Ground\\Testground.x");
	m_pGround->m_vPos = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//�u���@�v.
	m_pPlayer = new clsDx9Mesh;
	m_pPlayer->Init(m_hWnd, m_pDevice, m_pContext,"Data\\Model\\Player\\player.x");
	m_pPlayer->m_vPos = D3DXVECTOR3(0.0f, 1.0f, -6.0f);


	m_aScafSqu = new clsDx9Mesh;
	m_aScafSqu->Init(m_hWnd, m_pDevice, m_pContext, "Data\\Model\\Scaffold\\square.x");
	m_aScafSqu->m_vPos = D3DXVECTOR3(scaffoldSquX, scaffoldSquY, scaffoldSquZ);

	m_aScafSquM = new clsDx9Mesh;
	m_aScafSquM->Init(m_hWnd, m_pDevice, m_pContext, "Data\\Model\\Scaffold\\square.x");
	m_aScafSquM->m_vPos = D3DXVECTOR3(scaffoldSqumX, scaffoldSqumY, scaffoldSqumZ);


	//�m�F�p�ɽ̨��������ݸނ���.
	//(�����蔻��Ƃ��Ă͎g�p���Ă��Ȃ�).
	m_pSphere = new clsDx9Mesh;
	m_pSphere->Init(m_hWnd, m_pDevice, m_pContext, "Data\\Model\\Sphere\\Sphere.x");

	//ү�������޳��ިݸ޽̨��̍쐬.
	//InitSphere(m_pPlayer);

	InitSphere(m_pSphere);

	//�\���p�̨��̒��S�Ɣ��a�����@�ƓG�@�ɔ��f.
	//m_pPlayer->m_Sphere = m_pSphere->m_Sphere;

	//�X�v���C�g����ݒ肷��(�x�^�\��).
	SPRITE_STATE	ss;
	ss.Width = 256.0f;
	ss.Height = 256.0f;
	ss.U = 1.0f;
	ss.V = 1.0f;

	//�X�v���C�g2D�̏�����.
	m_pSprite2D = new clsSprite2D;
	m_pSprite2D->Init(m_pDevice, m_pContext, "Data\\Texture\\UI\\particle.png", ss);
	m_pSprite2D->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


}

void clsMain::LoadSound()
{
	//m_sTitle.Open
}

/**************************************************/


//�J�����֐�.
void clsMain::Camera()
{
	//�J�����ʒu(���@�̔w�ʂ���v)�̐ݒ�.
	m_Camera.vEye = m_Camera.vLook = m_pPlayer->m_vPos;	//���@�̌��ݒn���߰.
	m_Camera.Yaw = m_pPlayer->m_Yaw;					//��]�n���߰.
	//Y����]�s��.
	D3DXMatrixRotationY(&m_Camera.mRotation, m_Camera.Yaw);

	//���x�N�g����p�ӂ���.
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);
	//Z���x�N�g�����̂��̂���]��Ԃɂ��ϊ�����.
	//D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Camera.mRotation);
	//�J�����ʒu�E�����ʒu�𒲐�.
	m_Camera.vEye -= vecAxisZ*4.0f;		//���@�̔w��.
	m_Camera.vLook += vecAxisZ*2.0f;	//���@�̑O��.
	//���ꂼ��̍�������.
	m_Camera.vEye.y += 2.0f;		//���@�̔w��.
	m_Camera.vLook.y += 0.2f;			//���@�̑O��.

	//�ޭ�(���)�ϊ�.
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//����ʒu.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�ޭ��v�Z����.
		&m_Camera.vEye, &m_Camera.vLook, &vUpVec);

}

//��ۼު���݊֐�.
void clsMain::Proj()
{
	//��ۼު����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,						//(out)��ۼު���݌v�Z����.
		D3DX_PI / 4.0,				//y�����̎���(׼ޱݎw��)���l��傫�������王�삪�����Ȃ�.
		(FLOAT)WND_W / (FLOAT)WND_H,//���߸Ĕ�(��������).
		0.1f,						//�߂��ޭ����ʂ�z�l.
		100.0f);					//�����ޭ����ʂ�z�l.

}

/*****************�e�L��������****************/

void clsMain::P_ACT()
{

}

void clsMain::B_ACT()
{

}

void clsMain::E_ACT()
{

}

/**********************************************/



void clsMain::ScaffSqu()
{
	scaffoldCntSpu++;

	if (0 <= scaffoldCntSpu&&!moveOne&&!moveTwo)
	{
		m_aScafSqu->m_vPos.x += 0.01f;
		m_aScafSquM->m_vPos.x -= 0.01f;

		if (m_aScafSqu->m_vPos.x >= 1.7f && m_aScafSquM->m_vPos.x <= -1.7f)
		{
			m_aScafSqu->m_vPos.x = 1.7f;
			m_aScafSquM->m_vPos.x = -1.7f;

			moveOne = true;
		}
	}

	if (340 <= scaffoldCntSpu&&moveOne&&!moveTwo)
	{
		m_aScafSqu->m_vPos.z += 0.01f;
		m_aScafSqu->m_vPos.y += 0.01f;

		m_aScafSquM->m_vPos.z -= 0.01f;
		m_aScafSquM->m_vPos.y -= 0.01f;

		if (m_aScafSqu->m_vPos.z >= 11.0f && m_aScafSqu->m_vPos.y >= 4.2f
			&&m_aScafSquM->m_vPos.z <= 7.0f && m_aScafSquM->m_vPos.y <= 0.1f)
		{
			m_aScafSqu->m_vPos.y = 4.2f;
			m_aScafSqu->m_vPos.z = 11.0f;
			m_aScafSquM->m_vPos.y = 0.1f;
			m_aScafSquM->m_vPos.z = 7.0f;

			moveOne = false;
			moveTwo = true;

		}
	}

	if (739 <= scaffoldCntSpu&&!moveOne&&moveTwo)
	{
		m_aScafSqu->m_vPos.x -= 0.01f;
		m_aScafSquM->m_vPos.x += 0.01f;

		if (m_aScafSqu->m_vPos.x <= -1.7f && m_aScafSquM->m_vPos.x >= 1.7f)
		{
			m_aScafSqu->m_vPos.x = -1.7f;
			m_aScafSquM->m_vPos.x = 1.7f;
			moveOne = true;
			moveTwo = true;

		}

	}
	
	if (1079 <= scaffoldCntSpu&&moveOne&&moveTwo)
	{
		m_aScafSqu->m_vPos.z -= 0.01f;
		m_aScafSqu->m_vPos.y -= 0.01f;
		m_aScafSquM->m_vPos.z += 0.01f;
		m_aScafSquM->m_vPos.y += 0.01f;

		if (m_aScafSqu->m_vPos.z <= 7.0f && m_aScafSqu->m_vPos.y <= 0.1f
		&&m_aScafSquM->m_vPos.z >= 11.0f && m_aScafSquM->m_vPos.y >= 4.2f)
		{
			m_aScafSqu->m_vPos.x = -1.7f;
			m_aScafSqu->m_vPos.y = 0.1f;
			m_aScafSqu->m_vPos.z = 7.0f;
			m_aScafSquM->m_vPos.x = 1.7f;
			m_aScafSquM->m_vPos.y = 4.2f;
			m_aScafSquM->m_vPos.z = 11.0f;

			scaffoldCntSpu = 0;
			moveOne = false;
			moveTwo = false;
		}


	}


}














//Direct3D������.
HRESULT clsMain::Init3D()
{
	//-----------------------------------------------
	//	���޲��ƽܯ�����݊֌W.
	//-----------------------------------------------

	//�ܯ�����ݍ\����.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount	= 1;//�ޯ��ޯ̧�̐�.
	sd.BufferDesc.Width = WND_W;//�ޯ��ޯ̧�̕�.
	sd.BufferDesc.Height = WND_H;//�ޯ��ޯ̧�̍���.
	//̫�ϯ�(32�ޯĶװ)
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//��گ��ڰ�(����) ��FPS:60
	sd.BufferDesc.RefreshRate.Numerator = 60;
	//��گ��ڰ�(���q)
	sd.BufferDesc.RefreshRate.Denominator = 1;
	//�g����(�\����)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;//����޳�����.
	sd.SampleDesc.Count = 1;//�������ِ�.
	sd.SampleDesc.Quality = 0;//�������ق̸��è
	sd.Windowed = TRUE;//����޳Ӱ��(�ٽ�ذݎ���FALSE)

	//�쐬�����݂�@�\���ق̗D����w��.
	//	(GPU����߰Ă���@�\��Ă̒�`)
	//	D3D_FEATURE_LEVEL�񋓌^�̔z��.
	//	D3D_FEATURE_LEVEL_10_1�FDirect3D 10.1��GPU����.
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;//�z��̗v�f��.

	//���޲��ƽܯ�����݂̍쐬.
	//ʰ�޳��(GPU)���޲��ō쐬.
	if (FAILED(	D3D11CreateDeviceAndSwapChain(
		NULL,	//���޵�������ւ��߲��.
		D3D_DRIVER_TYPE_HARDWARE,//�쐬�������޲��̎��.
		NULL,	//��ĳ�� ׽�ײ�ް����������DLL�������.
		0,	//�L���ɂ��������ڲ԰.
		&pFeatureLevels,//�쐬�����݂�@�\���ق̏������w�肷��z��ւ��߲��.
		1,	//���̗v�f��.
		D3D11_SDK_VERSION,//SKD���ް�ޮ�.
		&sd,	//�ܯ�����݂̏��������Ұ����߲��.
		&m_pSwapChain,//(out)�����ݸނɎg�p����ܯ������.
		&m_pDevice,	//(out)�쐬���ꂽ���޲�.
		pFeatureLevel,//�@�\���ق̔z��ɂ���ŏ��̗v�f��\���߲��.
		&m_pContext)))//(out)���޲���÷��.
	{
		//WARP���޲��̍쐬.(Windows Advanced Rasterization Platform)
		// D3D_FEATURE_LEVEL_9_1�`D3D_FEATURE_LEVEL_10_1
		if (FAILED(
			D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_WARP,//�쐬�������޲��̎��.
			NULL, 0, &pFeatureLevels, 1, D3D11_SDK_VERSION,
			&sd, &m_pSwapChain, &m_pDevice, pFeatureLevel, &m_pContext)))
		{
			//�̧�ݽ���޲��̍쐬.
			// DirectX SKD���ݽİق���ĂȂ��Ǝg���Ȃ�.
			if (FAILED(
				D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_REFERENCE,//�쐬�������޲��̎��.
				NULL, 0, &pFeatureLevels, 1, D3D11_SDK_VERSION,
				&sd, &m_pSwapChain, &m_pDevice, pFeatureLevel, &m_pContext)))
			{
				MessageBox(NULL,
					"���޲��ƽܯ�����݂̍쐬�Ɏ��s",
					"error(main.cpp)", MB_OK);
				return E_FAIL;
			}
		}
	}

	//�e��ø����ƁA����ɕt�т���e���ޭ����쐬.

	//-----------------------------------------------
	//	�ޯ��ޯ̧�����F�װ�ޯ̧�ݒ�.
	//-----------------------------------------------

	//�ޯ��ޯ̧ø������擾(���ɂ���̂ō쐬�ł͂Ȃ�)
	ID3D11Texture2D* pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D),//__uuidof�F���Ɋ֘A�t�����ꂽGUID���擾.
								  //Texture2D�̗B��̕��Ƃ��Ĉ���.
		(LPVOID*)&pBackBuffer_Tex);//(out)�ޯ��ޯ̧ø���.

	//����ø����ɑ΂����ް���ޯ��ޭ�(RTV)���쐬.
	m_pDevice->CreateRenderTargetView(
		pBackBuffer_Tex,
		NULL,
		&m_pBackBuffer_TexRTV);//(out)RTV.
	//�ޯ��ޯ̧ø������J��.
	SAFE_RELEASE(pBackBuffer_Tex);


	//-----------------------------------------------
	//	�ޯ��ޯ̧����:���߽(�[�x)��ݼي֌W.
	//-----------------------------------------------
	//���߽(�[��or�[�x)��ݼ��ޭ��p��ø������쐬.
	D3D11_TEXTURE2D_DESC descDepth;

	descDepth.Width = WND_W;//��.
	descDepth.Height = WND_H;//����.
	descDepth.MipLevels = 1;//Я��ϯ������:1.
	descDepth.ArraySize = 1;//�z��:1.
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;//32�ޯ�̫�ϯ�.
	descDepth.SampleDesc.Count = 1;//�������ق̐�.
	descDepth.SampleDesc.Quality = 0;//�������ق̸��è.
	descDepth.Usage = D3D11_USAGE_DEFAULT;//�g�p���@:��̫��.
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;//�[�x(��ݼقƂ��Ďg�p).
	descDepth.CPUAccessFlags = 0;//CPU����ͱ������Ȃ�.
	descDepth.MiscFlags = 0;//���̑�:�ݒ�Ȃ�.

	if (FAILED(
		m_pDevice->CreateTexture2D(
		&descDepth,
		NULL,
		&m_pBackBuffer_DSTex)))//(out)���߽��ݼٗpø���.
	{
		MessageBox(NULL,
			"���߽��ݼٗpø����쐬���s", "error", MB_OK);
		return E_FAIL;
	}
	//����ø����ɑ΂����߽��ݼ��ޭ�(DSV)���쐬.
	if (FAILED(
		m_pDevice->CreateDepthStencilView(
		m_pBackBuffer_DSTex,
		NULL,
		&m_pBackBuffer_DSTexDSV)))//(out)���߽��ݼ��ޭ�(DSV).
	{
		MessageBox(NULL,
			"���߽��ݼ��ޭ��쐬���s", "error", MB_OK);
		return E_FAIL;
	}

	//���ް���ޯ��ޭ������߽��ݼ��ޭ����߲��ײ݂ɾ��.
	m_pContext->OMSetRenderTargets(
		1,
		&m_pBackBuffer_TexRTV,
		m_pBackBuffer_DSTexDSV);

	//�ޭ��߰Ă̐ݒ�.
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)WND_W;	//��.
	vp.Height = (FLOAT)WND_H;	//����.
	vp.TopLeftX = 0.0f;	//����ʒux.
	vp.TopLeftY = 0.0f;	//����ʒuy.
	vp.MinDepth = 0.0f;	//�ŏ��[�x(��O).
	vp.MaxDepth = 1.0f;	//�ő�[�x(��).
	m_pContext->RSSetViewports(1, &vp);

	//׽�ײ��(�ʂ̓h��ׂ���)�ݒ�.
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.FillMode = D3D11_FILL_SOLID;//�h��ׂ�(�د��).
									//D3D11_FILL_WIREFRAME:ܲ԰�ڰ�.
	rdc.CullMode = D3D11_CULL_NONE;	//D3D11_CULL_NONE:��ݸނ�؂�
									//(���ʔw�ʂ�`�悷��)
									//D3D11_CULL_FRONT:���ʂ�`�悵�Ȃ�.
									//D3D11_CULL_BACK :�w�ʂ�`�悵�Ȃ�.
	rdc.FrontCounterClockwise = FALSE;//��غ�݂̗��\�����肷���׸�.
									  //TRUE:�����Ȃ�O����.�E���Ȃ������.
									  //FALSE:�t�ɂȂ�.
	rdc.DepthClipEnable = TRUE;	//�����ɂ��Ă̸د��ݸޗL��.
	
	//׽�ײ�ލ쐬.
	ID3D11RasterizerState* pIr = NULL;
	m_pDevice->CreateRasterizerState(&rdc, &pIr);
	m_pContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);


	//ү��̧�ٓǍ�.
	//m_pClsDx9Mesh = new clsDx9Mesh;
	//m_pClsDx9Mesh->Init(m_hWnd, m_pDevice, m_pContext,"Data\\model_pnt.x");

	return S_OK;
}

//Direct3D�I������.
void clsMain::DestroyD3D()
{

	//���ق̉��.
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);

	//Direct3D��޼ު�Ẳ��.
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);

}


//�̨��쐬.
HRESULT clsMain::InitSphere(clsDx9Mesh* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;//���_�ޯ̧.
	void*		pVertices = NULL;//���_.
	D3DXVECTOR3	vCenter;	//���S.
	float		Radius;		//���a.

	//���_�ޯ̧���擾.
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	//ү���̒��_�ޯ̧��ۯ�����.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//ү���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)pVertices,
		pMesh->m_pMesh->GetNumVertices(),	//���_��.
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()),//���_���.
		&vCenter,	//(out)���S���W.
		&Radius);	//(out)���a.

	//��ۯ�.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//���S�Ɣ��a���\���̂ɐݒ�.
	pMesh->m_Sphere.vCenter = vCenter;
	pMesh->m_Sphere.Radius = Radius;

	return S_OK;
}

//�Փ˔���.
bool clsMain::Collision(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�.
	D3DXVECTOR3 vLength
		= pTarget->m_vPos - pAttacker->m_vPos;
	//�����ɕϊ�����.
	float Length = D3DXVec3Length(&vLength);

	//�Q�̕��̂̋������A�Q�̕��̂̔��a�����������̂�菬�����Ƃ������Ƃ�.
	//�̨����m���d�Ȃ��Ă���(�Փ˂��Ă���)�Ƃ�������.
	if (Length <= pAttacker->m_Sphere.Radius + pTarget->m_Sphere.Radius)
	{
		return true;//�Փ�.
	}
	return false;//�Փ˂��Ă��Ȃ�.
}

//�o�E���f�B���O�{�b�N�X�쐬.
HRESULT	clsMain::InitBBox(clsDx9Mesh* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 Max, Min;

	//ү���̒��_�o�b�t�@�����b�N����.
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB)))
	{
		MessageBox(NULL, "���_�o�b�t�@�擾���s", "error", MB_OK);
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		MessageBox(NULL, "���_�o�b�t�@���b�N���s", "error", MB_OK);
		return E_FAIL;

	}
	//���b�V�����̒��_�ʒu�̍ő�ƍŏ�����������
	D3DXComputeBoundingBox((D3DXVECTOR3*)pVertices,
		pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()),
		&Min, &Max);//�o�́F�ŏ��A�ő咸�_.

	pVB->Unlock();//�A�����b�N.
	SAFE_RELEASE(pVB);

	pMesh->m_BBox.vPosMax = Max;
	pMesh->m_BBox.vPosMin = Min;

	//���x�N�g���E���̒���(���̏ꍇ�A�{�b�N�X�̊e���a)������������.
	pMesh->m_BBox.LengthX = (Max.x - Min.x) / 2.0f;
	pMesh->m_BBox.LengthY = (Max.y - Min.y) / 2.0f;
	pMesh->m_BBox.LengthZ = (Max.z - Min.z) / 2.0f;

	return S_OK;
}

//���Փ˔���.
bool clsMain::BBoxCollision(clsDx9Mesh* pAttacker, clsDx9Mesh* pTarget)
{
	//�U���p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecAtkMax, vecAtkMin;	//�ő�A�ŏ����_.
	vecAtkMax = pAttacker->m_BBox.vPosMax + pAttacker->m_vPos;
	vecAtkMin = pAttacker->m_BBox.vPosMin + pAttacker->m_vPos;

	//�ڕW�p�p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecTrgMax, vecTrgMin;	//�ő�A�ŏ����_.
	vecTrgMax = pTarget->m_BBox.vPosMax + pTarget->m_vPos;
	vecTrgMin = pTarget->m_BBox.vPosMin + pTarget->m_vPos;


	//2�̃��b�V�����ꂼ��̍ő�A�ŏ��ʒu���g��.
	//4�̏�񂪂���΁A�Փ˂����o�ł���.
	if (vecAtkMin.x<vecTrgMax.x &&vecAtkMax.x>vecTrgMin.x
		&&vecAtkMin.y<vecTrgMax.y &&vecAtkMax.y>vecTrgMin.y
		&&vecAtkMin.z<vecTrgMax.z &&vecAtkMax.z>vecTrgMin.z)
	{
		return true;	//�Փ˂��Ă���.
	}
	return false;		//�Փ˂��Ă��Ȃ�.
}

