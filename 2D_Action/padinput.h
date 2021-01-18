//##################################################################################################################################################################//
//
// パッド入力ヘッダファイル [padinput.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _PADINPUT_H_
#define _PADINPUT_H_

#include "main.h"

typedef enum
{
	JPPRESS_RIGTH = 0,
	JPPRESS_LEFT,
	JPPRESS_UP,
	JPPRESS_DOWN,
	JPPRESS_MAX
}JPPRESS;

typedef enum
{
	JPTRIGGER_RIGTH = 0,
	JPTRIGGER_LEFT,
	JPTRIGGER_UP,
	JPTRIGGER_DOWN,
	JPTRIGGER_MAX
}JPTRIGGER;

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitKeypad(HINSTANCE hInstance, HWND hWnd);
void UninitKeypad(void);
void UpdateKeypad(void);
bool GetKeypadTrigger(int nKey);
bool GetKeypadPresse(int nKey);
bool GetKeypadReleace(int nKey);
void JoypadPressInfo(DIJOYSTATE2 State);
void JoypadTriggerInfo(DIJOYSTATE2 State);
//DIJOYSTATE2 GetPadPless(void);
bool *GetPadPlress(void);
bool *GetPadTrigger(void);
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);

#endif