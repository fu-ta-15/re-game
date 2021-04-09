//##################################################################################################################################################################//
//
// ���C������ [main.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
// �C���N���[�h�t�@�C��
//=====================================================================================================================================================================//
#include "main.h"
#include "manager.h"

//=====================================================================================================================================================================//
// �}�N����`
//=====================================================================================================================================================================//
#define ID_TIMER		(121)
#define TIMER_INTERVAL	(1000/60)
#define VERTEX_THREE	(4)

//=====================================================================================================================================================================//
// �O���[�o���錾
//=====================================================================================================================================================================//
//D3DPRESENT_PARAMETERS g_d3dpp;						// ImGui�ɕK�v
//LPD3DXFONT g_pFont = NULL;							// �t�H���g�ւ̃|�C���^
int g_nCountFPS;									// FPS�J�E���^


//=====================================================================================================================================================================//
// �v���g�^�C�v�錾
//=====================================================================================================================================================================//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //���

 //=====================================================================================================================================================================//
 // ���C���֐�
 //=====================================================================================================================================================================//
int WINAPI WinMain
(HINSTANCE hInstance,			// �C���X�^���X�n���h��
	HINSTANCE hPrevInstance,	// ���NULL
	LPSTR lpCmdLine,			// �R�}���h���C������󂯎���������ւ̃|�C���^
	int nCmdShow)				// �����E�B���h�E�̕\�����@�̎w��
{

#ifdef _DEBUG

	// �R���\�[�����쐬����
	AllocConsole();
	// �W�����o�͂Ɋ��蓖�Ă�
	FILE* fp = NULL;
	// ���݂̃R�[�h
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("%s", "�eCPP�̃f�[�^�̓ǂݍ��݂��J�n\n");

#endif

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
		"windows.suzuki", // �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),
	};
	HWND hWnd;				// �E�B���h�E�n���h���i���ʎq�j
	MSG msg;				// Message

							// �����̂͂���
							// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);	// �o�^
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx
	(0,
		"windows.suzuki",		// �����Ȃ��E�E�B���h�E�N���X�̖��O
		"start",				// ������E�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���Y���W
		rect.right - rect.left,	// �E�̍��W
		rect.bottom - rect.top,	// ���̍��W
		NULL,
		NULL,
		hInstance,
		NULL);



	CManager *pManager = NULL;
	pManager = new CManager;

	if (pManager != NULL)
	{
		// ����������
		if (FAILED(pManager->Init(hInstance, hWnd, true)))
		{
			return -1;
		}
	}


	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	// �������s�ŏI����
	DWORD dwFPSLastTime;	// FPS�v���ŏI����
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwFrameCount;		// �t���[���J�E���g

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();	// ���ݎ�����ݒ�
	dwFrameCount = 0;

	// Message�̃��[�v�i�E�B���h�E�Y��p�̏����j
	while (1)
	{// Message�̖|��Ƒ��o
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
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
		{// DirectX�̏���

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

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	if (pManager != NULL)
	{
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}


	// �E�B���h�E�N���X�̓o�^����
	UnregisterClass("windows.suzuki", wcex.hInstance);

	return(int)msg.wParam;	// �Ԃ�l
}

//=====================================================================================================================================================================//
// �E�B���h�E�v���V�[�W��
//=====================================================================================================================================================================//
// Win32 message handler
//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	//	return true;

	int nID;

	switch (uMsg)
	{// ���b�Z�[�W�̂����
	case WM_DESTROY:			// �E�B���h�E��j������
		PostQuitMessage(0);		// WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_CLOSE:				// �~�{�^���������ꂽ�ꍇ
		nID = MessageBox(NULL, "�m�F�ł��B", "�m�F", MB_YESNOCANCEL | MB_ICONHAND);
		if (nID == IDYES)
		{// YES�������ꂽ�ꍇ
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
