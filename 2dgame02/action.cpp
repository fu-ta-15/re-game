//##################################################################################################################################################################//
//
// 敵オブジェクト処理 [point.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "point.h"
#include "input.h"
#include "player.h"
#include "brock.h"
#include "padinput.h"
#include "action.h"
#include "enemy.h"
#include "moneyblock.h"
#include "stock.h"
#include "gauge.h"
#include "score.h"
#include "sound.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED						(255)											// 赤色
#define COLOR_BULUE						(255)											// 青色
#define COLOR_GREEN						(255)											// 緑色
#define COLOR_ALPHA						(255)											// アルファ値

#define POINT_X							(15)											// 中心座標X
#define POINT_Y							(15)											// 中心座標Y
#define POINT_POS						(50.0f)

#define ENEMY_SIZE						(30)											// エネミーのサイズ
#define MONEYBLOCK_SIZE					(30)											// エネミーのサイズ

#define MAX_MoneyBrock					(256)											// 敵の数
#define MAX_ENEMY						(256)											// 敵の数
#define PATICLE_LIFE					(20)

#define ACTION_TYPE						(2)
#define ACTION_HEITH_UP					(25)
#define ACTION_HEITH_DOWN				(25)
#define ACTION_WIDTH_RIGHT				(25)
#define ACTION_WIDTH_LEFT				(25)
#define ACTION_MOVE						(8.0f)
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureAction = NULL;			// テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAction = NULL;	// 頂点バッファへのポインタ
ACTIONPLAYER g_Action;
float g_ActionAddMove;

//=====================================================================================================================================================================//
// アクションの初期化処理
//=====================================================================================================================================================================//
HRESULT InitAction(void)
{
	VERTEX_2D *pVtx;							// VERTEXのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ

	// 構造体の初期化
	g_Action.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Action.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Action.MOVE = D3DXVECTOR3(ACTION_MOVE, 0.0f, 0.0f);
	g_Action.Amode = ACTION_MODE_ATTACK;
	g_Action.Hit = false;

	g_ActionAddMove = ACTION_MOVE;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\actionpoint00.png", &g_pTextureAction);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffAction, NULL)))
	{
		return E_FAIL;
	}

	g_Action.pos = D3DXVECTOR3(20.0f, 550.0f, 0.0f);

	// 頂点バッファのロック
	g_pVtxBuffAction->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_Action.pos.x - ACTION_WIDTH_LEFT, g_Action.pos.y + ACTION_HEITH_DOWN, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Action.pos.x - ACTION_WIDTH_LEFT, g_Action.pos.y - ACTION_HEITH_UP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Action.pos.x + ACTION_WIDTH_RIGHT, g_Action.pos.y + ACTION_HEITH_DOWN, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Action.pos.x + ACTION_WIDTH_RIGHT, g_Action.pos.y - ACTION_HEITH_UP, 0.0f);

	// テクスチャの頂点座標
	pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

	// rhwの設定		=	1.0f固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定・赤・緑・青
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	// 頂点バッファのアンロック
	g_pVtxBuffAction->Unlock();

	// S_OKを返す
	return S_OK;
}

//=====================================================================================================================================================================//
// アクションの終了処理
//=====================================================================================================================================================================//
void UninitAction(void)
{
	if (g_pVtxBuffAction != NULL)
	{
		g_pVtxBuffAction->Release();
		g_pVtxBuffAction = NULL;
	}
	if (g_pTextureAction != NULL)
	{
		g_pTextureAction->Release();
		g_pTextureAction = NULL;
	}
	StopSound(SOUND_LABEL_SE_ATTACK);	//BGM
	StopSound(SOUND_LABEL_SE_BLOCK);	//BGM
	StopSound(SOUND_LABEL_SE_CAENGE);	//BGM
	StopSound(SOUND_LABEL_SE_OK);	//BGM
	StopSound(SOUND_LABEL_SE_NO);	//BGM
}

//=====================================================================================================================================================================//
// アクションの更新処理
//=====================================================================================================================================================================//
void UpdateAction(void)
{
	// 構造体のポインタ
	PLAYER *pPlayer;
	POINTER *pPoint;

	pPlayer = GetPlayer();
	pPoint = GetPointer();

	if (GetKeypadTrigger(2) == true)
	{
		ActionPlayer();
	}
	if (GetKeypadTrigger(5) == true)
	{
		g_Action.Amode = ACTION_MODE_DIG;
		PlaySound(SOUND_LABEL_SE_CAENGE);
	}
	if (GetKeypadTrigger(4) == true)
	{
		g_Action.Amode = ACTION_MODE_ATTACK;
		PlaySound(SOUND_LABEL_SE_CAENGE);
	}

	ActionCondributor();
}


//=====================================================================================================================================================================//
// アクションの描画処理
//=====================================================================================================================================================================//
void DrawAction(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffAction, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureAction);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//=====================================================================================================================================================================//
// アクション開始の処理
//=====================================================================================================================================================================//
void ActionPlayer(void)
{
	switch (g_Action.Amode)
	{// プレイヤーの状態
	case ACTION_MODE_ATTACK:	// 攻撃
		EnemyColision();
		break;

	case ACTION_MODE_DIG:		// 探索
		MoneyBlockColision();
		break;

	case ACTION_MODE_BAG:		// メニュー画面
		MenyuPause();
		break;

	default:
		break;
	}
}

//=====================================================================================================================================================================//
// 敵の当たり判定
//=====================================================================================================================================================================//
void EnemyColision(void)
{
	// 構造体の情報取得
	ENEMY *pEnemy = GetEnemy();
	POINTER *pPointer = GetPointer();
	STOCK *pStock = GetStock();

	(pStock += 1);

	if (pStock->nStock != 0)
	{
		AddStock(-1, 1);

		for (int nCunt = 0; nCunt < MAX_ENEMY; nCunt++, pEnemy++)
		{
			if (pEnemy->bUse == true)
			{// 敵が存在しているとき
				if (pPointer->pos.x < pEnemy->pos.x + ENEMY_SIZE && pPointer->pos.x > pEnemy->pos.x - ENEMY_SIZE)
				{
					g_Action.Hit = true;	// 敵の当たった
					pEnemy->bUse = false;	// 敵を消す
					AddScore(10);
					PlaySound(SOUND_LABEL_SE_ATTACK);
				}
				else
				{
					g_Action.Hit = false;	// あたっていない
				}
			}
		}
	}
}

//=====================================================================================================================================================================//
// 鉱石の当たり判定
//=====================================================================================================================================================================//
void MoneyBlockColision(void)
{
	MONEYBLOCK *pMoneyBlock = GetMoneyBlock();
	POINTER *pPointer = GetPointer();
	STOCK *pStock = GetStock();

	(pStock += 2);

	if (pStock->nStock != 0)
	{
		AddStock(-1, 2);
		for (int nCuntBlock = 0; nCuntBlock < MAX_MoneyBrock; nCuntBlock++, pMoneyBlock++)
		{
			if (pMoneyBlock->bUse == true)
			{
				if (pPointer->pos.x < pMoneyBlock->pos.x + MONEYBLOCK_SIZE && pPointer->pos.x > pMoneyBlock->pos.x - MONEYBLOCK_SIZE)
				{
					g_Action.Hit = true;
					pMoneyBlock->bUse = false;
					AddScore(100);
					AddStock(1, 0);
					PlaySound(SOUND_LABEL_SE_BLOCK);
				}
				else
				{
					g_Action.Hit = false;
				}
			}
		}
	}
}

//=====================================================================================================================================================================//
// メニュー画面
//=====================================================================================================================================================================//
void MenyuPause(void)
{




}

//=====================================================================================================================================================================//
// アクションの判定　ゲージの判定
//=====================================================================================================================================================================//
void ActionCondributor(void)
{
	GAUGE *pGauge = GetGauge();
	POINTER *pPoint = GetPointer();
	STOCK *pStock = GetStock();

	g_Action.move.x = g_Action.MOVE.x;
	g_ActionAddMove = (float)(rand() % 8 + 8);

	if (g_Action.pos.x + ACTION_WIDTH_RIGHT > SCREEN_WIDTH)
	{
		g_Action.pos.x = SCREEN_WIDTH - ACTION_WIDTH_RIGHT;
		g_Action.MOVE.x = -g_ActionAddMove;
	}
	else if (g_Action.pos.x - ACTION_WIDTH_LEFT < 0)
	{
		g_Action.pos.x = 0 + ACTION_WIDTH_LEFT;
		g_Action.MOVE.x = g_ActionAddMove;
	}
	if (GetKeypadTrigger(1) == true)
	{
		if (g_Action.pos.x < pGauge->g_GaugeGole && g_Action.pos.x > pGauge->g_GaugeStart)
		{
			switch (g_Action.Amode)
			{
			case ACTION_MODE_ATTACK:	// 攻撃
				AddStock(1, 1);
				PlaySound(SOUND_LABEL_SE_OK);
				break;

			case ACTION_MODE_DIG:		// 探索
				AddStock(1, 2);
				PlaySound(SOUND_LABEL_SE_OK);
				break;

			default:
				break;
			}
		}
		else if (g_Action.pos.x > pGauge->g_GaugeGole || g_Action.pos.x < pGauge->g_GaugeStart)
		{
			//SetParticle(pPoint->pos, 9, PATICLE_LIFE, D3DXCOLOR(0.2f, 0.2f, 0.6f, 1.0f));
			switch (g_Action.Amode)
			{
			case ACTION_MODE_ATTACK:	// 攻撃
				(pStock += 1);
				if (pStock->nStock != 0)
				{
					AddStock(-1, 1);
					PlaySound(SOUND_LABEL_SE_NO);
				}
				break;

			case ACTION_MODE_DIG:		// 探索
				(pStock += 2);
				if (pStock->nStock != 0)
				{
					AddStock(-1, 2);
					PlaySound(SOUND_LABEL_SE_NO);
				}
				break;

			default:
				break;
			}

		}
	}
	g_Action.pos += g_Action.move;

	// VERTEXのポインタ
	VERTEX_2D *pVtx;							

	// 頂点バッファのロック
	g_pVtxBuffAction->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_Action.pos.x - ACTION_WIDTH_LEFT, g_Action.pos.y + ACTION_HEITH_DOWN, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Action.pos.x - ACTION_WIDTH_LEFT, g_Action.pos.y - ACTION_HEITH_UP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Action.pos.x + ACTION_WIDTH_RIGHT, g_Action.pos.y + ACTION_HEITH_DOWN, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Action.pos.x + ACTION_WIDTH_RIGHT, g_Action.pos.y - ACTION_HEITH_UP, 0.0f);

	// 頂点バッファのアンロック
	g_pVtxBuffAction->Unlock();
}


//=====================================================================================================================================================================//
// アクションの情報
//=====================================================================================================================================================================//
ACTIONPLAYER *GetAction(void)
{
	return &g_Action;
}
