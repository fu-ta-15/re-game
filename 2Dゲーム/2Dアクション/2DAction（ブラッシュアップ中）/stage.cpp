//##################################################################################################################################################################//
//
// ステージ管理処理 [stage.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "stage.h"
#include "player.h"
#include "brock.h"
#include "prebg.h"
#include "backbg.h"
#include "bg.h"
#include "input.h"
#include "padinput.h"
#include "enemy.h"
#include "moneyblock.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)								// 赤色
#define COLOR_BULUE			(255)								// 青色
#define COLOR_GREEN			(255)								// 緑色
#define COLOR_ALPHA			(255)								// アルファ値
#define HEIGTH_SIZE			(570)
#define MAX_RIGTH			(3000)
#define MAX_LEFT			(-3000)
#define MOVE_SPEED			(0.005f)
#define LENGTH_PLAYER_X		(30)								// 中心から各頂点の距離を求める数値
#define LENGTH_PLAYER_Y		(50)								// 中心から各頂点の距離を求める数値
#define MAX_BROCK			(1080)
#define PLAYER_TEX			(12)								// テクスチャの余白



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
STAGE g_Stage;
GAMEPOS g_Gamepos;											// ゲームの座標


															//=====================================================================================================================================================================//
															// ステージの初期化処理
															//=====================================================================================================================================================================//
HRESULT InitStage(void)
{
	g_Stage.fHeigth = 0.0f;
	g_Stage.fLeft = MAX_LEFT;
	g_Stage.fRigth = MAX_RIGTH;
	// ゲーム座標の初期化
	g_Gamepos.GamePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 処理完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ステージの終了処理
//=====================================================================================================================================================================//
void UninitStage(void)
{


}

//=====================================================================================================================================================================//
// ステージの更新処理
//=====================================================================================================================================================================//
void UpdateStage(void)
{
	// 構造体のポインタ
	PLAYER *pPlayer;
	BROCK *pBrock;
	BACKBG *pBackBg;
	PREBG *pPreBg;

	// 情報取得
	pPlayer = GetPlayer();
	pBrock = GetBrock();
	pBackBg = GetBackBg();
	pPreBg = GetPreBg();

	// プレイヤーの移動
	MovePlayer();
	MoveStage();


}

void MoveStage(void)
{
	BROCK *pBrock;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();
	pBrock = GetBrock();

	bool *pPad = GetPadPlress();

	if (GetKeyboardPresse(DIK_D) == true || pPad[JPPRESS_RIGTH] == true)
	{// 右
		if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->move.x != 0.0f)
		{// プレイヤーが右向き・ブロックが移動している・エリアの範囲にいる
			MoveBack();						// 奥
			MovePre();						// 手前
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x += 0.5f;	// ステージの座標
		}
		else if (pBrock->bUse == false)
		{// ブロックがない時・エリアの範囲にいる
			MoveBack();						// 奥
			MovePre();						// 手前
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x += 0.5f;	// ステージの座標
		}
		MoveBrock();					// ブロックの移動
	}
	else if (GetKeyboardPresse(DIK_A) == true || pPad[JPPRESS_LEFT] == true)
	{// 左
		if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->move.x != 0.0f)
		{
			MoveBack();						// 奥
			MovePre();						// 手前
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x -= 0.5f;	// ステージの座標
		}
		else if (pBrock->bUse == false)
		{
			MoveBack();						// 奥
			MovePre();						// 手前
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x -= 0.5f;	// ステージの座標
		}
		MoveBrock();					// ブロックの移動
	}
}

//=====================================================================================================================================================================//
// ステージの情報
//=====================================================================================================================================================================//
GAMEPOS *GetGamePos(void)
{
	return &g_Gamepos;
}

//=====================================================================================================================================================================//
// ブロックの当たり判定
//=====================================================================================================================================================================//
bool CollisionBrock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldpos, D3DXVECTOR3 *pMove, float fWidth, float fHeirth)
{
	// ポインタ
	BROCK *pBrock;
	// 情報取得
	pBrock = GetBrock();
	// 判定
	bool bLandBrock = false;

	if (pBrock->bUse == true)
	{// 使用中のみ
		if ((pPos->x + fWidth) > pBrock->pos.x && (pPos->x - fWidth) < (pBrock->pos.x + pBrock->fWidth))
		{// ブロックの範囲Xにポインタがいる
			if ((pOldpos->y + fHeirth) <= (pBrock->pos.y))
			{// ポインタがブロックより上にいる
				if ((pPos->y + fHeirth) > (pBrock->pos.y))
				{// ブロックの上で止まる
					pMove->y = 0.0f;
					pPos->y = pBrock->pos.y - fHeirth;
					bLandBrock = true;
				}
			}
			if ((pOldpos->y - fHeirth) >= (pBrock->pos.y + pBrock->fHeigth))
			{// ポインタがブロックより下にいる
				if ((pPos->y - fHeirth) < (pBrock->pos.y + pBrock->fHeigth))
				{// ポインタの頭がブロックに当たる
					pMove->y = 1.0f;
					pPos->y = (pBrock->pos.y + pBrock->fHeigth) + fHeirth;
				}
			}
		}
		if ((pPos->y + fHeirth) > pBrock->pos.y && (pPos->y - fHeirth) < (pBrock->pos.y + pBrock->fHeigth))
		{// ポインタがブロックのY座標にいる
			if ((pOldpos->x + fWidth) <= pBrock->pos.x)
			{// ポインタが左側
				if ((pPos->x + fWidth) > pBrock->pos.x)
				{// 右側にめり込む
					pPos->x = pBrock->pos.x - fWidth;
				}
			}
			if ((pOldpos->x - fWidth) >= (pBrock->pos.x + pBrock->fWidth))
			{// ポインタが右側
				if ((pPos->x - fWidth) < (pBrock->pos.x + pBrock->fWidth))
				{// 左側にめり込む
					pPos->x = pBrock->pos.x + pBrock->fWidth + fWidth;
				}
			}
		}
	}
	// 判定を返す
	return bLandBrock;
}
//=====================================================================================================================================================================//
// プレイヤーの当たり判定
//=====================================================================================================================================================================//
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldpos, D3DXVECTOR3 *pMove, float fWidth, float fHeirth)
{
	bool bLandPlayer = false;
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if ((pPos->y + fHeirth) > (pPlayer->pos.y - LENGTH_PLAYER_Y) && (pPos->y) < (pPlayer->pos.y + LENGTH_PLAYER_Y))
	{// プレイヤーがブロックのY座標にいる
		if ((pOldpos->x + fWidth) <= pPlayer->pos.x - PLAYER_TEX)
		{// プレイヤーが左側
			if ((pPos->x + fWidth) > pPlayer->pos.x - PLAYER_TEX)
			{// 右側にめり込む
				pPos->x = pPlayer->pos.x - PLAYER_TEX - fWidth;
				pMove->x = 0.0f;
				bLandPlayer = true;
			}
		}
		if ((pOldpos->x) >= (pPlayer->pos.x + PLAYER_TEX))
		{// プレイヤーが右側
			if ((pPos->x) < (pPlayer->pos.x + PLAYER_TEX))
			{// 左側にめり込む
				pPos->x = pPlayer->pos.x + PLAYER_TEX;
				pMove->x = 0.0f;
				bLandPlayer = true;
			}
		}
	}
	return bLandPlayer;
}
