//##################################################################################################################################################################//
//
// ���C������ [main.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "player.h"
#include "stage.h"
#include "brock.h"
#include "padinput.h"
#include "action.h"
#include "rankingbg.h"

//=====================================================================================================================================================================//
//�}�N����`
//=====================================================================================================================================================================//
#define ID_TIMER		(121)
#define TIMER_INTERVAL	(1000/60)
#define VERTEX_THREE	(4)

//=====================================================================================================================================================================//
//�O���[�o���錾
//=====================================================================================================================================================================//
LPDIRECT3D9 g_pD3D = NULL;							//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;							//�t�H���g�ւ̃|�C���^
int g_nCountFPS;									//FPS�J�E���^
MODE g_mode = MODE_TITLE;							//���[�h�̎��

													//=====================================================================================================================================================================//
													//�v���g�^�C�v�錾
													//=====================================================================================================================================================================//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //���
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=====================================================================================================================================================================//
//���C���֐�
//=====================================================================================================================================================================//
int WINAPI WinMain
(HINSTANCE hInstance,		//�C���X�^���X�n���h��
	HINSTANCE hPrevInstance,	//���NULL
	LPSTR lpCmdLine,			//�R�}���h���C������󂯎���������ւ̃|�C���^
	int nCmdShow)				//�����E�B���h�E�̕\�����@�̎w��
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"windows.suzuki", //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),
	};
	HWND hWnd;				//�E�B���h�E�n���h���i���ʎq�j
	MSG msg;				//Message

							//�����̂͂���
							//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);	//�o�^
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx
	(0,
		"windows.suzuki",		//�����Ȃ��E�E�B���h�E�N���X�̖��O
		"start",				//������E�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,			//�E�B���h�E�̍���Y���W
		rect.right - rect.left,				//�E�̍��W
		rect.bottom - rect.top,			//���̍��W
		NULL,
		NULL,
		hInstance,
		NULL);

	//����������
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	//�������s�ŏI����
	DWORD dwFPSLastTime;	//FPS�v���ŏI����
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwFrameCount;		//�t���[���J�E���g

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();	//���ݎ�����ݒ�
	dwFrameCount = 0;

	//Message�̃��[�v�i�E�B���h�E�Y��p�̏����j
	while (1)
	{//Message�̖|��Ƒ��o
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass("windows.suzuki", wcex.hInstance);

	return(int)msg.wParam;	//�Ԃ�l
}

//=====================================================================================================================================================================//
//�E�B���h�E�v���V�[�W��
//=====================================================================================================================================================================//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{//���b�Z�[�W�̂����
	case WM_DESTROY:			//�E�B���h�E��j������
		PostQuitMessage(0);		//WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_CLOSE:				//�~�{�^���������ꂽ�ꍇ
		nID = MessageBox(NULL, "�m�F�ł��B", "�m�F", MB_YESNOCANCEL | MB_ICONHAND);
		if (nID == IDYES)
		{//YES�������ꂽ�ꍇ
			DestroyWindow(hWnd);//���b�Z�[�W�𑗂�
		}
		else
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//�Ԃ�l
}

//=====================================================================================================================================================================//
//����������
//=====================================================================================================================================================================//
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//�Q�[����ʂ̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//����
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�I�u�W�F�N�g�̐���
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

	//�t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//1
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//2
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//3
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//4
																			/*  1.�J�����O�̐ݒ�i�@�@�@,���ʂ��J�����O�j
																			2.���u�����h�i���l�̍����j�̐ݒ聖�d�v
																			3.�\�[�X�i�`�挳�j�̍������@�̐ݒ�
																			4.�f�X�e�B�l�[�V�����i�`���j�̍������@�̐ݒ�
																			�@�@�@							�摜�̓����x�����f�@*/
																										// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	InitKeyboard(hInstance, hWnd);
	InitKeypad(hInstance, hWnd);

	//�T�E���h�̏���������
	InitSound(hWnd);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	// �t�F�[�h���[�h
	InitFade(g_mode);

	return S_OK;
}

//=====================================================================================================================================================================//
//�I������
//=====================================================================================================================================================================//
void Uninit(void)
{

	//�L�[�{�[�h�̏I������
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

		// �����L���O
	case MODE_RANKING:
		UninitBgRan();
		UninitRanking();
		break;

	default:
		break;
	}


	//�T�E���h�̏I������
	UninitSound();

	//Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
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
}

//=====================================================================================================================================================================//
//�X�V����
//=====================================================================================================================================================================//
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	UpdateKeypad();

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

		// �����L���O
	case MODE_RANKING:
		UpdateBgRan();
		UpdateRanking();
		break;

	default:
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();

}

//=====================================================================================================================================================================//
//�`�揈��
//=====================================================================================================================================================================//
void Draw(void)
{
	//�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��̊J�n
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

			// �����L���O
		case MODE_RANKING:
			DrawBgRan();
			DrawRanking();
			break;

		default:
			break;
		}


		//�t�F�[�h�̕`�揈��
		DrawFade();



#ifdef _DEBUG

		//FPS�̕`�揈��
		//DrawFPS();

#endif // _DEBUG

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=====================================================================================================================================================================//
//FPS�̕`�揈��
//=====================================================================================================================================================================//
void DrawFPS(void)
{
	// ���W
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	// ������
	char aStr[512];
	// �\���̂̏��
	PLAYER *pPlayer = GetPlayer();
	BROCK *pBrock = GetBrock();
	GAMEPOS *pGamePos = GetGamePos();
	ACTIONPLAYER *pAction = GetAction();
	// �\��������
	int nNum = sprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	nNum += sprintf(&aStr[nNum], "�u���b�N�̓����蔻��: %d \n", pAction->Hit);
	nNum += sprintf(&aStr[nNum], "move.y: %f \n", pPlayer->move.y);
	nNum += sprintf(&aStr[nNum], "�u���b�N��X���W: %f \n", pBrock->pos.x);
	nNum += sprintf(&aStr[nNum], "�u���b�N�̈ړ���: %f \n", pBrock->move.x);
	nNum += sprintf(&aStr[nNum], "�Q�[�����W�u�]�v: %f \n", pGamePos->GamePos.x);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

// ���[�h�̊m��
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

		// �����L���O
	case MODE_RANKING:
		UninitBgRan();
		UninitRanking();
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

		// �����L���O
	case MODE_RANKING:
		InitBgRan();
		InitRanking();
		break;

	default:
		break;
	}

	g_mode = mode;

}


//=====================================================================================================================================================================//
// �f�o�C�X�̎擾
//=====================================================================================================================================================================//
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=====================================================================================================================================================================//
// ���[�h�̎擾
//=====================================================================================================================================================================//
MODE GetMode(void)
{
	return g_mode;
}
