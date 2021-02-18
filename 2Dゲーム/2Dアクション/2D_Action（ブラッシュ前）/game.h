//##################################################################################################################################################################//
//
// ゲームヘッダファイル [game.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitGame();
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetPause(bool bPause);

#endif 