//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// タイトル
	SOUND_LABEL_BGM001,			// チュートリアル
	SOUND_LABEL_BGM002,			// ゲーム
	SOUND_LABEL_BGM003,			// result
	SOUND_LABEL_BGM004,			// ランキング

	SOUND_LABEL_SE_PAUSE0,		// 弾発射音
	SOUND_LABEL_SE_PAUSE1,			// ヒット音
	SOUND_LABEL_SE_PAUSE2,	// 爆発音
	SOUND_LABEL_SE_ATTACK,		// 弾発射音
	SOUND_LABEL_SE_BLOCK,
	SOUND_LABEL_SE_CAENGE,
	SOUND_LABEL_SE_OK,
	SOUND_LABEL_SE_NO,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
