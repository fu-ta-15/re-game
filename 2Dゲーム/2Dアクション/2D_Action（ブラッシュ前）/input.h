//##################################################################################################################################################################//
//
// 入力ヘッダファイル [input.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardPresse(int nKey);

#endif