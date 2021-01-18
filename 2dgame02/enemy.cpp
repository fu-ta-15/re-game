//##################################################################################################################################################################//
//
// 敵の処理 [enemy.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "enemy.h"
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
#define MAX_ENYMY_TYPE				(ENEMY_TYPE_MAX)																							// 敵の種類
#define MAX_ENEMY					(256)																										// 敵の数
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
#define ENEMY_SIZE					(30)																										// エネミーのサイズ
#define ENEMY_TEX					(30)
#define MOVE_SPEED_RIGTH			(D3DXVECTOR3(-5.1f,0.0f,0.0f))
#define MOVE_SPEED_LEFT				(D3DXVECTOR3(5.1f,0.0f,0.0f))
#define POS_Y_MAX					(400)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_ENYMY_TYPE] = {};	//テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファへのポインタ
ENEMY g_aEnemy[MAX_ENEMY];									//敵の種類
float g_fAngleEnemy;										//敵の対角線の角度
int g_fEnemyAlpha[MAX_ENEMY];								//敵の透明度
int g_AppCuntEnemy;

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitEnemy(void)
{
	//ポインタ
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;

	//デバイスの取得
	pDevice = GetDevice();
	pEnemy = &g_aEnemy[0];

	// ランダム
	srand((unsigned int)time(NULL));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy3.png", &g_apTextureEnemy[ENEMY_TYPE_MANY]);
	//敵の情報の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// 敵の構造体
		g_aEnemy[nCntEnemy].pos = VECTORO_ZERO;
		g_aEnemy[nCntEnemy].move = MOVE_ZERO;
		g_aEnemy[nCntEnemy].PlayerMove = MOVE_ZERO;
		g_aEnemy[nCntEnemy].Type = {};
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].bScreenVisible = false;
		// 配列の変数
		g_fEnemyAlpha[nCntEnemy] = COLOR_ALPHA;
	}

	g_AppCuntEnemy = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX * MAX_ENEMY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEnemy, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファのロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	//敵の初期化設定
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//各頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitEnemy(void)
{
	if (g_pVtxBuffEnemy != NULL)
	{//頂点バッファの開放
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENYMY_TYPE; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{//テクスチャの開放
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateEnemy(void)
{
	//構造体のポインタ
	VERTEX_2D *pVtx;

	//頂点バッファのロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が存在しているとき

		 // 移動の更新
			g_aEnemy[nCntEnemy].move.y += 1.0f;
			//g_aEnemy[nCntEnemy].move.x = 1.0f;
			// 位置の更新
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;

			// 移動・回転量の減衰
			g_aEnemy[nCntEnemy].move.y += (0 - g_aEnemy[nCntEnemy].move.y) * 0.002f;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);

			// 地面の当たり判定
			if (g_aEnemy[nCntEnemy].pos.y + ENEMY_TEX > POS_Y_MAX)
			{// 縦の範囲
				g_aEnemy[nCntEnemy].move.y = 0.0f;
				g_aEnemy[nCntEnemy].pos.y = POS_Y_MAX - ENEMY_TEX;
			}
			//敵の状態管理
			StateEnemy(nCntEnemy);
		}
		//プラス4進める
		pVtx += PVTEX_MAX;
	}
	//敵の配置
	RandSetEnemy();
	//頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawEnemy(void)
{
	//ポインタ
	LPDIRECT3DDEVICE9 pDevice;
	ENEMY *pEnemy;

	//デバイスの取得
	pDevice = GetDevice();
	pEnemy = &g_aEnemy[0];

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->Type]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * PVTEX_MAX, 2);
		}
	}
}

//=====================================================================================================================================================================//
//敵の設置するときの設定											                                                                                                   //
//=====================================================================================================================================================================//
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY_TYPE Type, int nLife)
{
	// 頂点ポインタ
	VERTEX_2D *pVtx;
	// 頂点バッファのロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{// 使用していない敵
		 // 敵の位置と種類の情報
			g_aEnemy[nCntEnemy].pos = pos;				// 位置
			g_aEnemy[nCntEnemy].Type = Type;			// 種類
			g_aEnemy[nCntEnemy].nLife = nLife;			// 体力

			if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH / 2)
			{
				g_aEnemy[nCntEnemy].move = move * -1;		// 移動
			}
			if (g_aEnemy[nCntEnemy].pos.x < SCREEN_WIDTH / 2)
			{
				g_aEnemy[nCntEnemy].move = move;			// 移動
			}

			// 地面に立たせる
			g_aEnemy[nCntEnemy].pos.y = POS_Y_MAX - ENEMY_TEX;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);

			//敵が存在している
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
		//頂点を４進める
		pVtx += PVTEX_MAX;
	}
	//頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
//敵のランダム配置																																					   //
//=====================================================================================================================================================================//
void RandSetEnemy(void)
{
	g_AppCuntEnemy++;
	// 左右の敵の配置の初期値
	int RandPosRight = SCREEN_WIDTH + (rand() % 30 + 20);
	int RandPosLeft = 0 - (rand() % 30 + 20);
	int MOVE = rand() % 1 + 4;
	if ((g_AppCuntEnemy % (rand() % 400 + 500)) == 0)
	{
		SetEnemy(D3DXVECTOR3(((float)RandPosRight), 0.0f, 0.0f), D3DXVECTOR3((float)(MOVE), 0.0f, 0.0f), ENEMY_TYPE_MANY, 10);
	}
	if ((g_AppCuntEnemy % (rand() % 600 + 600)) == 0)
	{
		SetEnemy(D3DXVECTOR3(((float)RandPosLeft), 0.0f, 0.0f), D3DXVECTOR3((float)(MOVE), 0.0f, 0.0f), ENEMY_TYPE_MANY, 10);
	}

}

//=====================================================================================================================================================================//
// 敵の状態管理　　                                                                                                                                                   
//=====================================================================================================================================================================//
void StateEnemy(int nIdx)
{
	// ポインタ
	VERTEX_2D *pVtx;

	// 変数の初期化
	int nScore = 0;

	// 頂点バッファのロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	if (g_aEnemy[nIdx].state == ENEMYSTATE_FALSE)
	{// 敵が消滅するとき

	 // その敵の頂点番号まで進める
		pVtx += (PVTEX_MAX * nIdx);

		// 移動停止
		g_aEnemy[nIdx].move = MOVE_ZERO;

		// テクスチャ座標の更新
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		// 各頂点のカラー情報
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);

		// アルファ値を減らす
		g_fEnemyAlpha[nIdx] -= ALPHA_INTERVAL;

		if (g_fEnemyAlpha[nIdx] <= 0)
		{// アルファ値がゼロ以下のとき
		 // スコア
			nScore += ADD_SCORE;
			// スコア加算
			//AddScore(nScore);

			// テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
			pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
			pVtx[2].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
			pVtx[3].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);

			// 各頂点のカラー情報
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

			// アルファ値を戻す
			g_fEnemyAlpha[nIdx] = COLOR_ALPHA;

			// 敵を消す
			g_aEnemy[nIdx].bUse = false;

			// 敵の状態をノーマルに
			g_aEnemy[nIdx].state = ENEMYSTATE_NORMAL;
		}
	}
	else if (g_aEnemy[nIdx].state == ENEMYSTATE_DAMAGE)
	{//ダメージ状態
	 // プラス4進める
		pVtx += (PVTEX_MAX * nIdx);

		// カウンターをマイナス
		g_aEnemy[nIdx].nCounterState--;

		if (g_aEnemy[nIdx].nCounterState <= 0)
		{// カウンターがゼロの場合

		 // ノーマル状態
			g_aEnemy[nIdx].state = ENEMYSTATE_NORMAL;

			// 色の更新
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		}
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
// 敵の移動管理　　                                                                                                                                                   
//=====================================================================================================================================================================//
void MoveEnemy(void)
{
	PLAYER *pPlayer;
	BROCK *pBrock;

	pPlayer = GetPlayer();
	pBrock = GetBrock();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が存在しているとき

			if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
			{
				g_aEnemy[nCntEnemy].PlayerMove = MOVE_SPEED_RIGTH;
			}
			else if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
			{
				g_aEnemy[nCntEnemy].PlayerMove = MOVE_SPEED_LEFT;
			}

			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].PlayerMove.x;
		}
	}
}


//=====================================================================================================================================================================//
// 敵が弾の当たった時                                                                                                                                                   //
//=====================================================================================================================================================================//
bool HitEnemy(int nIdx, int nDamage)
{
	// ポインタ
	VERTEX_2D *pVtx;

	// 敵の体力減少
	g_aEnemy[nIdx].nLife -= nDamage;

	if (g_aEnemy[nIdx].nLife <= 0)
	{// 体力がゼロのとき
	 // 敵の消滅
		g_aEnemy[nIdx].state = ENEMYSTATE_FALSE;
		return true;
	}
	else
	{// ゼロじゃないとき
	 // ダメージ音
	 //PlaySound(SOUND_LABEL_SE_HIT);

	 // ダメージ状態
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;

		// 状態のカウンター
		g_aEnemy[nIdx].nCounterState = ALPHA_INTERVAL;

		// 頂点バッファのロック
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		// 敵の情報分進める
		pVtx += (PVTEX_MAX * nIdx);

		// 色の更新
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);

		// 頂点バッファのアンロック
		g_pVtxBuffEnemy->Unlock();
		return false;
	}
}

//=====================================================================================================================================================================//
// 敵の情報　　　　　                                                                                                                                                   //
//=====================================================================================================================================================================//
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
