//##################################################################################################################################################################//
//
// メイン処理 [main.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "main.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "keyinput.h"
#include "Dinput.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "game.h"



//=====================================================================================================================================================================//
// マクロ定義
//=====================================================================================================================================================================//
#define ID_TIMER		(121)
#define TIMER_INTERVAL	(1000/60)
#define VERTEX_THREE	(4)

//=====================================================================================================================================================================//
// グローバル宣言
//=====================================================================================================================================================================//
LPDIRECT3D9 g_pD3D = NULL;							// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				// Direct3Dデバイスへのポインタ
D3DPRESENT_PARAMETERS g_d3dpp;						// ImGuiに必要
LPD3DXFONT g_pFont = NULL;							// フォントへのポインタ
int g_nCountFPS;									// FPSカウンタ
MODE g_mode = MODE_TITLE;							// 最初のモード

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

	//freopen_s(&fp, "CONIN$", "r", stdin);
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


	// 初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
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
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

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

	// ウィンドウクラスの登録解除
	UnregisterClass("windows.suzuki", wcex.hInstance);

	return(int)msg.wParam;	// 返り値
}

//=====================================================================================================================================================================//
// ウィンドウプロシージャ
//=====================================================================================================================================================================//
// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

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

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// ゲーム画面の幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// 高さ
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


	// Direct3Dオブジェクトの生成
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

	// フォントオブジェクトの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//1		 /*  1.カリングの設定（　　　,裏面をカリング）
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//2		 2.αブレンド（α値の合成）の設定＊重要
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//3		 3.ソース（描画元）の合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//4		 4.デスティネーション（描画先）の合成方法の設定/画像の透明度が反映　* /
	
	// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値　繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V値　繰り返し

	// テクスチャステージステートの設定
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

	// 入力の初期化処理
	InitKeyboard(hInstance, hWnd);
	InitKeypad(hInstance, hWnd);

	//モードの設定
	SetMode(g_mode);

	// フェードモード
	InitFade(g_mode);

	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void Uninit(void)
{
	// 入力の終了処理
	UninitKeyboard();
	UninitKeypad();
	//フェードの終了処理
	UninitFade();

	//各モードの終了処理
	switch (g_mode)
	{
		// タイトル
	case MODE_TITLE:
		UninitTitle();
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		UninitTutorial();
		break;

		// ゲーム
	case MODE_GAME:
		UninitGame();
		break;

		// リザルト
	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}



	//Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//フォントの開放
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
// 更新処理
//=====================================================================================================================================================================//
void Update(void)
{
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
#endif

	//各モードの更新処理
	switch (g_mode)
	{
		// タイトル
	case MODE_TITLE:
		UpdateTitle();
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

		// ゲーム
	case MODE_GAME:
		UpdateGame();
		break;

		// リザルト
	case MODE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}

	//フェードの更新処理
	UpdateFade();


	// 入力の更新処理
	UpdateKeyboard();
	UpdateKeypad();


#ifdef _DEBUG	// デバッグのみ
	// フレームの生成
	ImGui::NewFrame();
	ImGui::Begin("Debug");
	// フレーム内の内容
	if (ImGui::TreeNode("FPS"))
	{// FPS
		ImGui::Text("FPS:%d\n", g_nCountFPS);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("PLAYER"))
	{// プレイヤーの情報
		DrawPlayerInfo();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("MODE"))
	{// 現在のモード
		DrawMode();
		ImGui::TreePop();
	}
	// フレームの生成完了
	ImGui::End();
	ImGui::EndFrame();
#endif
}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void Draw(void)
{

	// バックバッファ＆Zバッファのクリア（画面のクリア）
 	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	// 描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//各モードの描画処理
		switch (g_mode)
		{
			// タイトル
		case MODE_TITLE:
			DrawTitle();
			break;

			// チュートリアル
		case MODE_TUTORIAL:
			DrawTutorial();
			break;

			// ゲーム
		case MODE_GAME:
			DrawGame();
			break;

			// リザルト
		case MODE_RESULT:
			DrawResult();
			break;

		default:
			break;
		}


		//フェードの描画処理
		DrawFade();


#ifdef _DEBUG


		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

#endif //_DEBUG


		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
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
// プレイヤー情報の表示処理
//=====================================================================================================================================================================//
void DrawPlayerInfo(void)
{
	// 座標
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	// 文字列
	char aStr[763];
	// 構造体の情報
	Camera *pCamera = GetCamera();
	Player *pPlayer = GetPlayer();

	// 表示する情報
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
	ImGui::Text("Counetr %d \n",pPlayer->nCounterMotion);

	// テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


//=====================================================================================================================================================================//
// モードの表示処理
//=====================================================================================================================================================================//
void DrawMode(void)
{
	switch (g_mode)
	{
		// タイトル
	case MODE_TITLE:
		ImGui::Text("TITLE_MODE");
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		ImGui::Text("TUTORIAL_MODE");
		break;

		// ゲーム
	case MODE_GAME:
		ImGui::Text("GAME_MODE");
		break;

		// リザルト
	case MODE_RESULT:
		ImGui::Text("RESULT_MODE");
		break;

	default:
		break;
	}
}

//=====================================================================================================================================================================//
// モードの確定
//=====================================================================================================================================================================//
void SetMode(MODE mode)
{
	switch (g_mode)
	{
		// タイトル
	case MODE_TITLE:
		UninitTitle();
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		UninitTutorial();
		break;

		// ゲーム
	case MODE_GAME:
		UninitGame();
		break;

		// リザルト
	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}


	switch (mode)
	{
		// タイトル
	case MODE_TITLE:
		InitTitle();
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		InitTutorial();
		break;

		// ゲーム
	case MODE_GAME:
		InitGame();
		break;

		// リザルト
	case MODE_RESULT:
		InitResult();
		break;

	default:
		break;
	}

	g_mode = mode;

}


//=====================================================================================================================================================================//
// デバイスの取得
//=====================================================================================================================================================================//
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=====================================================================================================================================================================//
// モードの取得
//=====================================================================================================================================================================//
MODE GetMode(void)
{
	return g_mode;
}
