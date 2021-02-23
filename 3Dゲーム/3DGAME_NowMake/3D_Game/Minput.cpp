//##################################################################################################################################################################//
//
// マウス入力処理 [mouseinput.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#include "Minput.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define DEADZONE        2500            // 各軸の25%を無効ゾーンとする
#define RANGE_MAX       10000           // 有効範囲の最大値
#define RANGE_MIN       -10000          // 有効範囲の最小値

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	LPDIRECTINPUTDEVICE8 g_lpMIDevice = NULL;	// ジョイパッドのデバイス情報
	DIMOUSESTATE State;						// プレス
	DIMOUSESTATE Trigger;					// トリガー
	DIMOUSESTATE Release;					// リリース
}MOUSE;								// コントローラーの情報


//-------------------------------------------------------------------
// グローバル変数
//-------------------------------------------------------------------
LPDIRECTINPUT8 g_lpMI = NULL;				// Dinputのポインタ
MOUSE g_Mouse;					// コントローラー情報のポインタ
bool g_bMPress[JPPRESS_MAX];					// プレス情報
bool g_bMTrigger[JPTRIGGER_MAX];				// スティックを倒したか


//=====================================================================================================================================================================//
//初期化処理
//=====================================================================================================================================================================//
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{

	// 初期化
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bMPress[nCuntPress] = false;
	}

	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_lpMI, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(g_lpMI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumMouseCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	// コントローラー情報の初期化
	if (!g_Mouse.g_lpMIDevice)
	{
		return E_FAIL;
	}

	// ボタンの初期化
	for (int nCntButton = 0; nCntButton < 4; nCntButton++)
	{
		g_Mouse.State.rgbButtons[nCntButton] = '\0';
		g_Mouse.Trigger.rgbButtons[nCntButton] = '\0';
		g_Mouse.Release.rgbButtons[nCntButton] = '\0';
	}


	//データフォーマットの設定
	if (FAILED(g_Mouse.g_lpMIDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(g_Mouse.g_lpMIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}


	//アクセス権の取得
	g_Mouse.g_lpMIDevice->Acquire();

	return S_OK;
}

//=====================================================================================================================================================================//
//終了処理
//=====================================================================================================================================================================//
void UninitMouse(void)
{
	//データフォーマットの開放
	if (g_Mouse.g_lpMIDevice != NULL)
	{
		//アクセス権の破棄
		g_Mouse.g_lpMIDevice->Unacquire();
		g_Mouse.g_lpMIDevice->Release();
		g_Mouse.g_lpMIDevice = NULL;
	}

	//DirectInputオブジェクトの開放
	if (g_lpMI != NULL)
	{
		g_lpMI->Release();
		g_lpMI = NULL;
	}
}

//=====================================================================================================================================================================//
//更新処理
//=====================================================================================================================================================================//
void UpdateMouse(void)
{
	// 変数宣言
	DIMOUSESTATE MouseState;	// コントローラーのボタン情報
	HRESULT hr;						// 成功したか判別
	int nCntButton;					// ボタンの個数

	if (g_Mouse.g_lpMIDevice != NULL)
	{// ジョイパッドが接続されていたらポーリング開始
		hr = g_Mouse.g_lpMIDevice->Poll();

		// デバイスからデータを取得
		if (SUCCEEDED(hr = g_Mouse.g_lpMIDevice->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
		{// スティックに情報を代入
			MousePressInfo(MouseState);			// プレス
			MouseTriggerInfo(MouseState);			// トリガー

														// 左スティックの情報
			g_Mouse.State.lY = MouseState.lY;			// lYのプレス
			g_Mouse.State.lX = MouseState.lX;			// lXのプレス
			g_Mouse.State.lZ = MouseState.lZ;

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{// プレス情報の保存
				g_Mouse.State.rgbButtons[nCnt] = MouseState.rgbButtons[nCnt];
			}

			for (nCntButton = 0; nCntButton < 13; nCntButton++)
			{// トリガー情報の保存
				g_Mouse.Trigger.rgbButtons[nCntButton] =
					(g_Mouse.State.rgbButtons[nCntButton] ^ MouseState.rgbButtons[nCntButton]) & MouseState.rgbButtons[nCntButton];

				// リリース情報の保存
				g_Mouse.Release.rgbButtons[nCntButton] =
					(MouseState.rgbButtons[nCntButton] ^ g_Mouse.State.rgbButtons[nCntButton]) & MouseState.rgbButtons[nCntButton];

				// プレス情報の保存
				g_Mouse.State.rgbButtons[nCntButton] = MouseState.rgbButtons[nCntButton];
			}
		}
		else
		{// アクセス権の取得
			g_Mouse.g_lpMIDevice->Acquire();
		}
	}
}

//=====================================================================================================================================================================//
// ボタン情報の取得
//=====================================================================================================================================================================//
bool GetMouseTrigger(int nKey)
{// トリガー情報の確認
	return (g_Mouse.Trigger.rgbButtons[nKey] & 0x80) ? true : false;
}
bool GetMousePresse(int nKey)
{// プレス情報の確認
	return (g_Mouse.State.rgbButtons[nKey] & 0x80) ? true : false;
}
bool GetMouseReleace(int nKey)
{// リリース情報の確認
	return (g_Mouse.Release.rgbButtons[nKey] & 0x80) ? true : false;
}

//=====================================================================================================================================================================//
// コールバック関数
//=====================================================================================================================================================================//
BOOL CALLBACK EnumMouseCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	hr = g_lpMI->CreateDevice(pdidInstance->guidInstance, &g_Mouse.g_lpMIDevice, NULL);

	return DIENUM_CONTINUE;
}

//=====================================================================================================================================================================//
// スティック情報の取得
//=====================================================================================================================================================================//
void MousePressInfo(DIMOUSESTATE State)
{
	bool bPress[JPPRESS_MAX] = { false,false,false,false };

	if (State.lX >= 7000)
	{// 右
		bPress[JPPRESS_RIGTH] = true;
	}
	else if (State.lX <= -7000)
	{// 左
		bPress[JPPRESS_LEFT] = true;
	}
	else if (State.lY >= 7000)
	{
		bPress[JPPRESS_DOWN] = true;
	}
	else if (State.lY <= -7000)
	{
		bPress[JPPRESS_UP] = true;
	}

	// 情報
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bMPress[nCuntPress] = bPress[nCuntPress];
	}
}

void MouseTriggerInfo(DIMOUSESTATE State)
{
	bool bTrigger[JPTRIGGER_MAX] = { false,false,false,false };

	if (State.lX >= 7000)
	{// 右
		bTrigger[JPTRIGGER_RIGTH] = true;
	}
	else if (State.lX <= -7000)
	{// 左
		bTrigger[JPTRIGGER_LEFT] = true;
	}
	else if (State.lY >= 7000)
	{
		bTrigger[JPTRIGGER_UP] = true;
	}
	else if (State.lY <= -7000)
	{
		bTrigger[JPTRIGGER_DOWN] = true;
	}


}


//=====================================================================================================================================================================//
// スティック情報の取得
//=====================================================================================================================================================================//
bool *GetMousePlress(void)
{
	return &g_bMPress[0];
}
bool *GetMouseTrigger(void)
{
	return &g_bMTrigger[0];
}