//##################################################################################################################################################################//
//
// �����_���[���� [renderer.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//


//=====================================================================================================================================================================//
//�@�C���N���[�h�t�@�C��
//=====================================================================================================================================================================//
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "keyinput.h"
#include "Dinput.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "game.h"

//=====================================================================================================================================================================//
// �O���[�o���錾
//=====================================================================================================================================================================//
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				// Direct3D�f�o�C�X�ւ̃|�C���^
LPDIRECT3D9 g_pD3D = NULL;							// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;							// �t�H���g�ւ̃|�C���^
D3DPRESENT_PARAMETERS g_d3dpp;						// ImGui�ɕK�v
MODE g_mode = MODE_TITLE;							// �ŏ��̃��[�h
D3DFILLMODE m_fillMode = D3DFILL_SOLID;				// ���C���[�t���[��

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// �f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
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
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//1		 /*  1.�J�����O�̐ݒ�i�@�@�@,���ʂ��J�����O�j
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//2		 2.���u�����h�i���l�̍����j�̐ݒ聖�d�v
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//3		 3.�\�[�X�i�`�挳�j�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//4		 4.�f�X�e�B�l�[�V�����i�`���j�̍������@�̐ݒ�/�摜�̓����x�����f�@* /
	g_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//5		 5.�[�b�g�e�X�g
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					//6		 6.�[�b�g�o�b�t�@�L��

																			// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	g_d3dpp = d3dpp;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(g_pD3DDevice);
#endif

	// ���͂̏���������
	InitKeyboard(hInstance, hWnd);
	InitKeypad(hInstance, hWnd);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	// �t�F�[�h���[�h
	InitFade(g_mode);

	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void Uninit(void)
{
	// ���͂̏I������
	UninitKeyboard();
	UninitKeypad();
	//�t�F�[�h�̏I������
	UninitFade();

	//�e���[�h�̏I������
	switch (g_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		UninitTitle();
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		UninitTutorial();
		break;

		// �Q�[��
	case MODE_GAME:
		UninitGame();
		break;

		// ���U���g
	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}


	if (g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//�t�H���g�̊J��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void Update(void)
{
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
#endif

	//�e���[�h�̍X�V����
	switch (g_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		UpdateTitle();
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

		// �Q�[��
	case MODE_GAME:
		UpdateGame();
		break;

		// ���U���g
	case MODE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();


	// ���͂̍X�V����
	UpdateKeyboard();
	UpdateKeypad();


#ifdef _DEBUG	// �f�o�b�O�̂�
	int nFPS = GetFPS();
	// �t���[���̐���
	ImGui::NewFrame();
	ImGui::Begin("Debug");
	// �t���[�����̓��e
	if (ImGui::TreeNode("FPS"))
	{// FPS
		ImGui::Text("FPS:%d\n", nFPS);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("PLAYER"))
	{// �v���C���[�̏��
		DrawPlayerInfo();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("MODE"))
	{// ���݂̃��[�h
		DrawMode();
		ImGui::TreePop();
	}
	// �t���[���̐�������
	ImGui::End();
	ImGui::EndFrame();


	if (GetKeyboardTrigger(DIK_M) == true)
	{
		switch (m_fillMode)
		{
		case D3DFILL_SOLID:
			m_fillMode = D3DFILL_WIREFRAME;
			break;
		case D3DFILL_WIREFRAME:
			m_fillMode = D3DFILL_SOLID;
			break;
		}

		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
	}
#endif
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void Draw(void)
{
	// �o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), CLEAR_ZBFF, 0);


	// �`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//�e���[�h�̕`�揈��
		switch (g_mode)
		{
			// �^�C�g��
		case MODE_TITLE:
			DrawTitle();
			break;

			// �`���[�g���A��
		case MODE_TUTORIAL:
			DrawTutorial();
			break;

			// �Q�[��
		case MODE_GAME:
			DrawGame();
			break;

			// ���U���g
		case MODE_RESULT:
			DrawResult();
			break;

		default:
			break;
		}


		//�t�F�[�h�̕`�揈��
		DrawFade();


#ifdef _DEBUG


		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

#endif 


		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	HRESULT result = g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

#ifdef _DEBUG
	if (result == D3DERR_DEVICELOST && g_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		HRESULT hr = g_pD3DDevice->Reset(&g_d3dpp);
		if (hr == D3DERR_INVALIDCALL)
			IM_ASSERT(0);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
#endif

}

//=====================================================================================================================================================================//
// �v���C���[���̕\������
//=====================================================================================================================================================================//
void DrawPlayerInfo(void)
{
	// ���W
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	// ������
	char aStr[763];
	// �\���̂̏��
	Camera *pCamera = GetCamera();
	Player *pPlayer = GetPlayer();

	// �\��������
	ImGui::Text("==========CAMERA========== \n");
	ImGui::Text("CAMERA_V : (%.2f : %.2f : %.2f) \n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	ImGui::Text("CAMERA_R : (%.2f : %.2f : %.2f) \n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	ImGui::Text("CAMERA_ROT : (%.2f) \n", pCamera->rot.y);
	ImGui::Text("============================== \n");
	ImGui::Text("==========PLAYER========== \n");
	ImGui::Text("MODEL_POS : (%.2f : %.2f : %.2f) \n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	ImGui::Text("MODEL_ROT : (%.2f) \n", pPlayer->rot.y);
	ImGui::Text("MODEL_ROTDEST : (%.2f) \n", pPlayer->rotDest.y);
	ImGui::Text("============================== \n");
	ImGui::Text("==========MODEL========== \n");
	ImGui::Text("MODEL_MIN : (X:%.2f Y:%.2f Z:%.2f) \n", pPlayer->aModel[0].g_VtxMinModel.x, pPlayer->aModel[0].g_VtxMinModel.y, pPlayer->aModel[0].g_VtxMinModel.z);
	ImGui::Text("MODEL_MAX : (X:%.2f Y:%.2f Z:%.2f) \n", pPlayer->aModel[0].g_VtxMaxModel.x, pPlayer->aModel[0].g_VtxMaxModel.y, pPlayer->aModel[0].g_VtxMaxModel.z);
	ImGui::Text("============================== \n");
	ImGui::Text("============Motion========== \n");
	ImGui::Text("Counetr %d \n", pPlayer->nCounterMotion);

	// �e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


//=====================================================================================================================================================================//
// ���[�h�̕\������
//=====================================================================================================================================================================//
void DrawMode(void)
{
	switch (g_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		ImGui::Text("TITLE_MODE");
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		ImGui::Text("TUTORIAL_MODE");
		break;

		// �Q�[��
	case MODE_GAME:
		ImGui::Text("GAME_MODE");
		break;

		// ���U���g
	case MODE_RESULT:
		ImGui::Text("RESULT_MODE");
		break;

	default:
		break;
	}
}

//=====================================================================================================================================================================//
// ���[�h�̊m��
//=====================================================================================================================================================================//
void SetMode(MODE mode)
{
	switch (g_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		UninitTitle();
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		UninitTutorial();
		break;

		// �Q�[��
	case MODE_GAME:
		UninitGame();
		break;

		// ���U���g
	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}


	switch (mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		InitTitle();
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		InitTutorial();
		break;

		// �Q�[��
	case MODE_GAME:
		InitGame();
		break;

		// ���U���g
	case MODE_RESULT:
		InitResult();
		break;

	default:
		break;
	}

	// ���[�h�̎擾
	g_mode = mode;

}

//=====================================================================================================================================================================//
// ���[�h�̎擾
//=====================================================================================================================================================================//
MODE GetMode(void)
{
	return g_mode;
}

//=====================================================================================================================================================================//
// �f�o�C�X�̎擾
//=====================================================================================================================================================================//
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
