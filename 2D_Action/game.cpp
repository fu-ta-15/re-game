//##################################################################################################################################################################//
//
// プレイヤー処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//インクルードファイル　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "game.h"
#include "input.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "pause.h"
#include "time.h"
#include "player.h"
#include "brock.h"
#include "bg.h"
#include "prebg.h"
#include "backbg.h"
#include "point.h"
#include "stage.h"
#include "padinput.h"
#include "action.h"
#include "moneyblock.h"
#include "gauge.h"
#include "ui.h"
#include "stock.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
bool g_bPause;		// ポーズ
int g_nCuntTime;	// ゲーム開始までのカウント

//=====================================================================================================================================================================//
// ゲームの初期化処理                                                                                                                
//=====================================================================================================================================================================//
HRESULT InitGame()
{
	// 変数の初期化
	g_bPause = false;
	g_nCuntTime = 120;

	// 背景の初期化
	InitBg();
	InitBackBg();
	InitPreBg();

	// プレイヤーの初期化
	InitPlayer();

	// アクション
	InitAction();

	// ブロックの初期化
	InitBrock();

	// 鉱石
	InitMoneyBlock();

	// ポイント
	InitPoint();

	// ステージの初期化
	InitStage();

	// スコアの初期化設定
	InitScore();

	// タイムの初期化
	InitTime();

	// ポーズの初期化処理
	InitPause();

	// ゲージ
	InitGauge();

	// UI
	InitUi();

	// ストック
	InitStock();

	// サウンド開始
	//PlaySound(SOUND_LABEL_BGM002);

	return S_OK;
}

//=====================================================================================================================================================================//
// ゲームの終了処理
//=====================================================================================================================================================================//
void UninitGame(void)
{
	// サウンド停止
	StopSound();

	// 背景の終了処理
	UninitBg();
	UninitBackBg();
	UninitPreBg();

	// プレイヤーの終了処理
	UninitPlayer();

	// アクション
	UninitAction();

	// ブロックの終了処理
	UninitBrock();

	// 鉱石
	UninitMoneyBlock();

	// ポイント
	UninitPoint();

	// スコアの終了処理
	UninitScore();

	// タイムの終了処理
	UninitTime();

	// ポーズの終了処理
	UninitPause();

	// ゲージ
	UninitGauge();

	// UI
	UninitUi();

	// ストック
	UninitStock();

	// サウンドストップ
	//StopSound(SOUND_LABEL_BGM002);	//BGM
	//StopSound(SOUND_LABEL_SE_PAUSE2);	//BGM
}

//=====================================================================================================================================================================//
//ゲームの更新処理
//=====================================================================================================================================================================//
void UpdateGame(void)
{
	// フェードの情報
	FADE pFade;
	pFade = GetFade();

	// カウントダウン開始
	g_nCuntTime--;

	// ポーズ開始
	if (pFade == FADE_NONE)
	{// フェードが何もしていないとき
		if (GetKeyboardTrigger(DIK_P) == true || GetKeypadTrigger(11) == true)
		{// Pが押されたとき
			//PlaySound(SOUND_LABEL_SE_PAUSE2);
			g_bPause = g_bPause ? false : true;	// falseかtrueに切り替える
		}
	}
	if (g_bPause == true)
	{// ポーズ中
		UpdatePause();
	}
	else if (g_nCuntTime < 0)
	{
		// ステージ管理
		UpdateStage();

		// 背景
		UpdateBg();

		// 奥の背景
		UpdateBackBg();

		// ブロック
		UpdateBrock();

		// 鉱石
		UpdateMoneyBlock();

		// プレイヤー
		UpdatePlayer();

		// アクション
		UpdateAction();

		// ポイント
		UpdatePoint();

		// ゲージ
		UpdateGauge();

		// UI
		UpdateUi();

		// ストック
		UpdateStock();

		// スコアの更新処理
		UpdateScore();

		// タイムの更新処理
		UpdateTime();

#ifdef _DEBUG	// デバッグのみ
		if (pFade == FADE_NONE)
		{// フェードが何もしていない状態のとき
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{// フェードの更新
				SetFade(FADE_OUT, MODE_RESULT);
			}
		}
#endif
	}
}

//=====================================================================================================================================================================//
// ゲームの描画処理
//=====================================================================================================================================================================//
void DrawGame(void)
{
	//背景
	DrawBg();

	//奥の背景
	DrawBackBg();

	//手前の背景
	DrawPreBg();

	//ブロック
	DrawBrock();

	// 鉱石
	DrawMoneyBlock();

	//プレイヤー
	DrawPlayer();

	//ポイント
	DrawPoint();

	//アクション
	DrawAction();

	//タイムの描画処理
	DrawTime();

	// ゲージ
	DrawGauge();

	// アクション
	DrawAction();

	// UI
	DrawUi();

	//スコアの描画処理
	DrawScore();

	// ストック
	DrawStock();

	//ポーズの描画
	if (g_bPause == true)
	{//TRUEの場合
		DrawPause();
	}
}

//=====================================================================================================================================================================//
//ポーズのセット
//=====================================================================================================================================================================//
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

