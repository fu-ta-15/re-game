//##################################################################################################################################################################//
//
// レンダラーヘッダファイル [renderer.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _RENDERER_H_
#define	_RENDERER_H_


//=====================================================================================================================================================================//
//　インクルードファイル
//=====================================================================================================================================================================//
#include "main.h"


//=====================================================================================================================================================================//
//モードの列挙型
//=====================================================================================================================================================================//
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_TUTORIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX		//MAX数値
}MODE;

//=====================================================================================================================================================================//
//プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


void DrawPlayerInfo(void);
void DrawMode(void);
void SetMode(MODE mode);
MODE GetMode(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#endif // !_
