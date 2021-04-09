//################################################################################//
//
// �����_���[���� [renderer.cpp]
// Author : SUZUKI FUUTA
//
//################################################################################//

//================================================================================//
// �C���N���[�h�t�@�C��
//================================================================================//
#include "renderer.h"

CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

CRenderer::~CRenderer()
{
}

HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// �f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// �Q�[����ʂ̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// ����
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


	// Direct3D�I�u�W�F�N�g�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//1		 /*  1.�J�����O�̐ݒ�i�@�@�@,���ʂ��J�����O�j
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//2		 2.���u�����h�i���l�̍����j�̐ݒ聖�d�v
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//3		 3.�\�[�X�i�`�挳�j�̍������@�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//4		 4.�f�X�e�B�l�[�V�����i�`���j�̍������@�̐ݒ�/�摜�̓����x�����f�@* /
	m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//5		 5.�[�b�g�e�X�g
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					//6		 6.�[�b�g�o�b�t�@�L��

																			// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	CPolygon2d::Create(D3DXVECTOR3(500.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	CPolygon2d::Create(D3DXVECTOR3(700.0f, 500.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	CPolygon2d::Create(D3DXVECTOR3(200.0f, 500.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	CPolygon2d::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	CPolygon2d::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return S_OK;
}

void CRenderer::Uninit(void)
{
	//Direct3D�f�o�C�X�̊J��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̊J��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	CPolygon::ReleceAllList();
}

void CRenderer::Update(void)
{
	//m_pPolygon2d->Update();
}

void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), WhiteColor, 1.0f, 0);


	// �`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CPolygon::DrawAllList();
		// �`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	HRESULT result = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
