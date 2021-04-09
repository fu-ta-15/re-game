//##################################################################################################################################################################//
//
// メイン処理 [main.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
// インクルードファイル
//=====================================================================================================================================================================//
#include "main.h"
#include "manager.h"

//=====================================================================================================================================================================//
// マクロ定義
//=====================================================================================================================================================================//
#define ID_TIMER		(121)
#define TIMER_INTERVAL	(1000/60)
#define VERTEX_THREE	(4)

//=====================================================================================================================================================================//
// グローバル宣言
//=====================================================================================================================================================================//
//D3DPRESENT_PARAMETERS g_d3dpp;						// ImGuiに必要
//LPD3DXFONT g_pFont = NULL;							// フォントへのポインタ
int g_nCountFPS;									// FPSカウンタ


//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //情報

 //=====================================================================================================================================================================//
 // メイン関数
 //=====================================================================================================================================================================//
int WINAPI WinMain
(HINSTANCE hInstance,			// インスタンスハンドル
	HINSTANCE hPrevInstance,	// 常にNULL
	LPSTR lpCmdLine,			// コマンドラインから受け取った引数へのポインタ
	int nCmdShow)				// 初期ウィンドウの表示方法の指定
{

#ifdef _DEBUG

	// コンソールを作成する
	AllocConsole();
	// 標準入出力に割り当てる
	FILE* fp = NULL;
	// 現在のコード
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("%s", "各CPPのデータの読み込みを開始\n");

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
		"windows.suzuki", // ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),
	};
	HWND hWnd;				// ウィンドウハンドル（識別子）
	MSG msg;				// Message

							// 処理のはじめ
							// ウィンドウクラスの登録
	RegisterClassEx(&wcex);	// 登録
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindowEx
	(0,
		"windows.suzuki",		// 見えない・ウィンドウクラスの名前
		"start",				// 見える・ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
		CW_USEDEFAULT,			// ウィンドウの左上X座標
		CW_USEDEFAULT,			// ウィンドウの左上Y座標
		rect.right - rect.left,	// 右の座標
		rect.bottom - rect.top,	// 下の座標
		NULL,
		NULL,
		hInstance,
		NULL);



	CManager *pManager = NULL;
	pManager = new CManager;

	if (pManager != NULL)
	{
		// 初期化処理
		if (FAILED(pManager->Init(hInstance, hWnd, true)))
		{
			return -1;
		}
	}


	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	// 処理実行最終時刻
	DWORD dwFPSLastTime;	// FPS計測最終時刻
	DWORD dwCurrentTime;	// 現在時刻
	DWORD dwFrameCount;		// フレームカウント

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();	// 現在時刻を設定
	dwFrameCount = 0;

	// Messageのループ（ウィンドウズ専用の処理）
	while (1)
	{// Messageの翻訳と送出
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
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
		{// DirectXの処理

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

				// 更新処理
				pManager->Update();

				// 描画処理
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	if (pManager != NULL)
	{
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}


	// ウィンドウクラスの登録解除
	UnregisterClass("windows.suzuki", wcex.hInstance);

	return(int)msg.wParam;	// 返り値
}

//=====================================================================================================================================================================//
// ウィンドウプロシージャ
//=====================================================================================================================================================================//
// Win32 message handler
//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	//	return true;

	int nID;

	switch (uMsg)
	{// メッセージのやり取り
	case WM_DESTROY:			// ウィンドウを破棄する
		PostQuitMessage(0);		// WM_QUITメッセージを返す
		break;

	case WM_CLOSE:				// ×ボタンが押された場合
		nID = MessageBox(NULL, "確認です。", "確認", MB_YESNOCANCEL | MB_ICONHAND);
		if (nID == IDYES)
		{// YESが押された場合
			DestroyWindow(hWnd);//メッセージを送る
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
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//返り値
}
