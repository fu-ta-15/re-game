//##################################################################################################################################################################//
//
// メインヘッダファイル [main.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION	(0x0800)
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "d3dx9.h"	//描画処理に必要 //プロパティから、ライブラリ・インクルードファイルを編集Window(:C)からｘ８６へ、フォルダを選択する
#include "dinput.h"	//入力処理に必要
#include "xaudio2.h"
#include "XInput.h"
//=====================================================================================================================================================================//
//ライブラリのリンク
//=====================================================================================================================================================================//
#pragma comment(lib, "d3d9.lib")	//描画処理に必要
#pragma comment(lib, "d3dx9.lib")	//拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	//コンポーネント使用に必要
#pragma comment(lib, "dinput8.lib")	//入力処理に必要
#pragma comment(lib, "winmm.lib")	
#pragma comment(lib, "xinput.lib")	

//=====================================================================================================================================================================//
//マクロ定義
//=====================================================================================================================================================================//
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(600)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット・頂点座標・頂点カラー・テクスチャ座標

//=====================================================================================================================================================================//
//モードの列挙型
//=====================================================================================================================================================================//
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_TUTORIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_RANKING,	//ランキング画面
	MODE_MAX		//MAX数値
}MODE;

//=====================================================================================================================================================================//
//頂点フォーマットに合わせた構造体
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//1.0で固定
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

//=====================================================================================================================================================================//
//プロトタイプ宣言
//=====================================================================================================================================================================//
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawFPS(void);

#endif // !_MAIN_H_

