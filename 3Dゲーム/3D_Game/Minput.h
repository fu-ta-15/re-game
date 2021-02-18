//##################################################################################################################################################################//
//
// パッド入力ヘッダファイル [mouseinput.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MOUSEINPUT_H_
#define _MOUSEINPUT_H_

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
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);

bool GetMouseTrigger(int nKey);
bool GetMousePresse(int nKey);
bool GetMouseReleace(int nKey);
void MousePressInfo(DIMOUSESTATE State);
void MouseTriggerInfo(DIMOUSESTATE State);
//DIJOYSTATE2 GetPadPless(void);
bool *GetMousePlress(void);
bool *GetMouseTrigger(void);
BOOL CALLBACK EnumMouseCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);

#endif