//##################################################################################################################################################################//
//
// 敵の処理 [enemy.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "moneyblock.h"
#include "input.h"
#include "score.h"
#include "player.h"
#include "brock.h"
#include "sound.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_MONEYBLOCK_TYPE			(300)																										// 敵の種類
#define MAX_MoneyBrock				(256)																										// 敵の数
#define COLOR_RED					(255)																										// 赤色
#define COLOR_BULUE					(255)																										// 青色
#define COLOR_GREEN					(255)																										// 緑色
#define COLOR_ALPHA					(255)																										// アルファ値
#define MAX_COLOR					(255)																										// 色の最大値
#define COLOR_DAMAGEALPHA			(255/5)																										// ダメージ状態のアルファ値
#define VECTORO_ZERO				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))																				// VECTOROの初期化
#define MOVE_ZERO					(D3DXVECTOR3(0.0f, 0.0f, 0.0f))																				// スピードゼロ
#define COLOR_ZERO					(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))																			// 色の初期化
#define ALPHA_INTERVAL				(5)																											// アルファ値のインターバル
#define PVTEX_MAX					(4)																											// pVtx
#define TEXPOS_ONE					(1.0f)																										// テクスチャ座標１
#define TEXPOS_HALF					(0.5f)																										// テクスチャ座標２
#define TEXPOS_ZERO					(0.0f)																										// テクスチャ座標３
#define ADD_SCORE					(1)																											// スコア
#define MONEYBLOCK_SIZE				(30)																										// エネミーのサイズ
#define MONEYBLOCK_TEX				(30)
#define MOVE_SPEED_RIGTH			(D3DXVECTOR3(-5.1f,0.0f,0.0f))
#define MOVE_SPEED_LEFT				(D3DXVECTOR3(5.1f,0.0f,0.0f))


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureMoneyBlock = {};			// テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoneyBlock = NULL;	// 頂点バッファへのポインタ
MONEYBLOCK g_aMoneyBlock[MAX_MoneyBrock];				// 敵の種類
int g_AppCuntBlock;

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitMoneyBlock(void)
{
	//ポインタ
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	MONEYBLOCK *pMoneyBlock;

	//デバイスの取得
	pDevice = GetDevice();
	pMoneyBlock = &g_aMoneyBlock[0];

	// ランダム
	srand((unsigned int)time(NULL));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\brock.png", &g_apTextureMoneyBlock);

	//敵の情報の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{// 敵の構造体
		g_aMoneyBlock[nCntEnemy].pos = VECTORO_ZERO;
		g_aMoneyBlock[nCntEnemy].PlayerMove = MOVE_ZERO;
		g_aMoneyBlock[nCntEnemy].bUse = false;
		g_aMoneyBlock[nCntEnemy].nCounterState = 0;
		g_aMoneyBlock[nCntEnemy].nLife = 0;
		g_aMoneyBlock[nCntEnemy].state = MONEYBLOCKSTATE_NORMAL;
	}
	g_AppCuntBlock = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX * MAX_MoneyBrock, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyBlock, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファのロック
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);
	//敵の初期化設定
	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		//各頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);

		//rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定・赤・緑・青
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		//プラス4進める
		pVtx += PVTEX_MAX;
	}
	//頂点バッファのアンロック
	g_pVtxBuffMoneyBlock->Unlock();
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitMoneyBlock(void)
{
	if (g_pVtxBuffMoneyBlock != NULL)
	{//頂点バッファの開放
		g_pVtxBuffMoneyBlock->Release();
		g_pVtxBuffMoneyBlock = NULL;
	}
	if (g_apTextureMoneyBlock != NULL)
	{//テクスチャの開放
		g_apTextureMoneyBlock->Release();
		g_apTextureMoneyBlock = NULL;
	}
}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateMoneyBlock(void)
{
	//構造体のポインタ
	VERTEX_2D *pVtx;

	//頂点バッファのロック
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		if (g_aMoneyBlock[nCntEnemy].bUse == true)
		{// 敵が存在しているとき
		 //頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);

			// 地面の当たり判定
			if (g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_TEX > 400)
			{// 縦の範囲
				g_aMoneyBlock[nCntEnemy].pos.y = 400 - MONEYBLOCK_TEX;
			}
			//敵の状態管理
			StateMoneyBlock(nCntEnemy);
		}
		//プラス4進める
		pVtx += PVTEX_MAX;
	}
	//敵の配置
	RandSetMoneyBlock();
	//頂点バッファのアンロック
	g_pVtxBuffMoneyBlock->Unlock();
}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawMoneyBlock(void)
{
	//ポインタ
	LPDIRECT3DDEVICE9 pDevice;
	MONEYBLOCK *pEnemy;

	//デバイスの取得
	pDevice = GetDevice();
	pEnemy = &g_aMoneyBlock[0];

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMoneyBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureMoneyBlock);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * PVTEX_MAX, 2);
		}
	}
}

//=====================================================================================================================================================================//
//敵の設置するときの設定											                                                                                                   //
//=====================================================================================================================================================================//
void SetMoneyBlock(D3DXVECTOR3 pos, int nLife)
{
	// 頂点ポインタ
	VERTEX_2D *pVtx;
	// 頂点バッファのロック
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		if (g_aMoneyBlock[nCntEnemy].bUse == false)
		{// 使用していない敵
		 // 敵の位置と種類の情報
			g_aMoneyBlock[nCntEnemy].pos = pos;				// 位置
			g_aMoneyBlock[nCntEnemy].nLife = nLife;			// 体力
															// 地面に立たせる
			g_aMoneyBlock[nCntEnemy].pos.y = 400 - MONEYBLOCK_TEX;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);

			//敵が存在している
			g_aMoneyBlock[nCntEnemy].bUse = true;
			break;
		}
		//頂点を４進める
		pVtx += PVTEX_MAX;
	}
	//頂点バッファのアンロック
	g_pVtxBuffMoneyBlock->Unlock();
}

//=====================================================================================================================================================================//
//敵のランダム配置																																					   //
//=====================================================================================================================================================================//
void RandSetMoneyBlock(void)
{
	g_AppCuntBlock++;
	// 左右の敵の配置の初期値
	int RandPosRight = SCREEN_WIDTH + (rand() % 30 + 20);
	int RandPosLeft = 0 - (rand() % 30 + 20);
	int MOVE = rand() % 1 + 4;
	if ((g_AppCuntBlock % (rand() % 400 + 500)) == 0)
	{
		SetMoneyBlock(D3DXVECTOR3(((float)RandPosRight), 0.0f, 0.0f), 10);
	}
	if ((g_AppCuntBlock % (rand() % 600 + 600)) == 0)
	{
		SetMoneyBlock(D3DXVECTOR3(((float)RandPosLeft), 0.0f, 0.0f), 10);
	}
}

//=====================================================================================================================================================================//
// 敵の状態管理　　                                                                                                                                                   
//=====================================================================================================================================================================//
void StateMoneyBlock(int nIdx)
{
	// ポインタ
	VERTEX_2D *pVtx;

	// 変数の初期化
	int nScore = 0;

	// 頂点バッファのロック
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);
	if (g_aMoneyBlock[nIdx].state == MONEYBLOCKSTATE_FALSE)
	{// 敵が消滅するとき

	 // その敵の頂点番号まで進める
		pVtx += (PVTEX_MAX * nIdx);

		// テクスチャ座標の更新
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		// 各頂点のカラー情報
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);

		// アルファ値を減らす
		//g_fEnemyAlpha[nIdx] -= ALPHA_INTERVAL;

		//	if (g_fEnemyAlpha[nIdx] <= 0)
		//	{// アルファ値がゼロ以下のとき
		//	 // スコア
		//		nScore += ADD_SCORE;
		//		// スコア加算
		//		//AddScore(nScore);

		//		// テクスチャ座標の更新
		//		pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
		//		pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
		//		pVtx[2].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		//		pVtx[3].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);

		//		// 各頂点のカラー情報
		//		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//		// アルファ値を戻す
		//		g_fEnemyAlpha[nIdx] = COLOR_ALPHA;

		//		// 敵を消す
		//		g_aMoneyBlock[nIdx].bUse = false;

		//		// 敵の状態をノーマルに
		//		g_aMoneyBlock[nIdx].state = ENEMYSTATE_NORMAL;
		//	}
		//}
		//else if (g_aMoneyBlock[nIdx].state == ENEMYSTATE_DAMAGE)
		//{//ダメージ状態
		// // プラス4進める
		//	pVtx += (PVTEX_MAX * nIdx);

		//	// カウンターをマイナス
		//	g_aMoneyBlock[nIdx].nCounterState--;

		//	if (g_aMoneyBlock[nIdx].nCounterState <= 0)
		//	{// カウンターがゼロの場合

		//	 // ノーマル状態
		//		g_aMoneyBlock[nIdx].state = ENEMYSTATE_NORMAL;

		//		// 色の更新
		//		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	}
	}
	// 頂点バッファのアンロック
	g_pVtxBuffMoneyBlock->Unlock();
}

//=====================================================================================================================================================================//
// 敵の移動管理　　                                                                                                                                                   
//=====================================================================================================================================================================//
void MoveMoneyBlock(void)
{
	PLAYER *pPlayer;
	BROCK *pBrock;

	pPlayer = GetPlayer();
	pBrock = GetBrock();

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		if (g_aMoneyBlock[nCntEnemy].bUse == true)
		{//敵が存在しているとき

			if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
			{
				g_aMoneyBlock[nCntEnemy].PlayerMove = MOVE_SPEED_RIGTH;
			}
			else if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
			{
				g_aMoneyBlock[nCntEnemy].PlayerMove = MOVE_SPEED_LEFT;
			}

			g_aMoneyBlock[nCntEnemy].pos.x += g_aMoneyBlock[nCntEnemy].PlayerMove.x;
		}
	}
}


//=====================================================================================================================================================================//
// 敵が弾の当たった時                                                                                                                                                   //
//=====================================================================================================================================================================//
bool HitMoneyBlock(int nIdx, int nDamage)
{
	// ポインタ
	VERTEX_2D *pVtx;

	// 敵の体力減少
	g_aMoneyBlock[nIdx].nLife -= nDamage;

	if (g_aMoneyBlock[nIdx].nLife <= 0)
	{// 体力がゼロのとき
	 // 敵の消滅
		g_aMoneyBlock[nIdx].state = MONEYBLOCKSTATE_FALSE;
		return true;
	}
	else
	{// ゼロじゃないとき
	 // ダメージ音
	 //PlaySound(SOUND_LABEL_SE_HIT);

	 // ダメージ状態
		g_aMoneyBlock[nIdx].state = MONEYBLOCKSTATE_DAMAGE;

		// 状態のカウンター
		g_aMoneyBlock[nIdx].nCounterState = ALPHA_INTERVAL;

		// 頂点バッファのロック
		g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);

		// 敵の情報分進める
		pVtx += (PVTEX_MAX * nIdx);

		// 色の更新
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);

		// 頂点バッファのアンロック
		g_pVtxBuffMoneyBlock->Unlock();
		return false;
	}
}

//=====================================================================================================================================================================//
// 敵の情報　　　　　                                                                                                                                                   //
//=====================================================================================================================================================================//
MONEYBLOCK *GetMoneyBlock(void)
{
	return &g_aMoneyBlock[0];
}
