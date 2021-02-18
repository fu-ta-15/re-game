//##################################################################################################################################################################//
//
// プレイヤー処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "player.h"
#include "input.h"
#include "brock.h"
#include "prebg.h"
#include "backbg.h"
#include "stage.h"
#include "padinput.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MOVE_SPEED			(4)									// スピード
#define LENGTH_PLAYER_X		(30)								// 中心から各頂点の距離を求める数値
#define LENGTH_PLAYER_Y		(50)								// 中心から各頂点の距離を求める数値
#define COLOR_RED			(255)								// 赤色
#define COLOR_BULUE			(255)								// 青色
#define COLOR_GREEN			(255)								// 緑色
#define COLOR_ALPHA			(255)								// アルファ値
#define PVTEX_MAX			(4)									// pVtx
#define FRAME_COUNT			(10)								// FRAMEのカウント
#define RHW					(10/10)								// rhwの数値1.0固定
#define PLAYER_TEX			(13)								// テクスチャの余白
#define TEXTURE_PLAYER_X	(4)									// テクスチャｘの分割数
#define TEXTURE_PLAYER_Y	(1)									// テクスチャyの分割数
#define HEIGTH_SIZE			(510)								// 地面の上辺の高さ



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;			// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;					// テクスチャの情報
PLAYER g_Player;											// プレイヤー情報
int g_nConterAnim;											// アニメーションのカウンター
int g_nPatternAnim;											// アニメーション
int g_nNextAnim;											// 次のアニメーションに行くまでのカウント
int g_nAlpha;												// α値
float g_fTexY;												// テクスチャy座標
bool g_bLandP;												// 当たり判定

//=====================================================================================================================================================================//
// プレイヤーの初期化処理
//=====================================================================================================================================================================//
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	VERTEX_2D *pVtx;			// 頂点ポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// グローバル変数の初期化
	g_nConterAnim = 0;
	g_nPatternAnim = 0;
	g_nNextAnim = 0;
	g_fTexY = 0.0f;
	g_nAlpha = COLOR_ALPHA;
	g_bLandP = false;

	// プレイヤー情報の初期化
	g_Player.nCounterState = 0;
	g_Player.nCounterDisp = 0;
	g_Player.Oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.PlayerDire = DIRECTION_RIGTH;
	g_Player.PlayerBrock = HIT_BROCK_NO;
	g_Player.PlayerState = PLAYERSTATE_NORMAL;
	g_Player.Junp = true;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tori_tokage3.png", &g_pTexturePlayer);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロック
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 初期の場所に戻す
	g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH / 5, 400 - LENGTH_PLAYER_Y, 0.0f);

	//各頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);

	// 回転角度
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = RHW;
	pVtx[1].rhw = RHW;
	pVtx[2].rhw = RHW;
	pVtx[3].rhw = RHW;

	// 頂点カラーの設定・赤・緑・青・アルファ
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	// テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));

	// 頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitPlayer(void)
{
	// テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	//StopSound(SOUND_LABEL_SE_SHOT);	//BGM

}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdatePlayer(void)
{
	// ポインタ
	VERTEX_2D *pVtx;	// 頂点のポインタ 
	PLAYER *pPlayer;	// プレイヤーのポインタ
	MODE pMode;

	// 情報取得
	pPlayer = &g_Player;// プレイヤー
	pMode = GetMode();

	// 過去の位置
	g_Player.Oldpos = g_Player.pos;

	// 位置の更新
	g_Player.move.y += 1.0f;
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.rot.z += g_Player.move.z;

	// 移動・回転量の減衰
	g_Player.move.x += (0 - g_Player.move.x) * 0.8f;
	g_Player.move.y += (0 - g_Player.move.y) * 0.002f;
	g_Player.move.z += (0 - g_Player.move.z) * 1.0f;

	// ブロックとの当たり判定
	g_bLandP = CollisionBrock(&g_Player.pos, &g_Player.Oldpos, &g_Player.move, PLAYER_TEX, LENGTH_PLAYER_Y);

	if (g_bLandP == true)
	{// ブロックの上にいるとき
		pPlayer->Junp = false;
	}
	if (g_Player.pos.y + LENGTH_PLAYER_Y > HEIGTH_SIZE)
	{// 縦の範囲
		g_Player.move.y = 0.0f;
		g_Player.pos.y = HEIGTH_SIZE - LENGTH_PLAYER_Y;
		pPlayer->Junp = false;
	}
	if ((g_nPatternAnim + 1) % 5 == 0)
	{// 四番目まで来たら初期に戻す
		g_nPatternAnim = 0;
	}

	// バッファのロック
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));

	// 各頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);

	// 頂点カラーの設定・赤・緑・青・アルファ（透明度）
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	// プレイヤーバッファのアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawPlayer(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================================================================================================================================================//
// プレイヤーの移動
//=====================================================================================================================================================================//
void MovePlayer(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	bool *pPad = GetPadPlress();

	if (GetKeyboardPresse(DIK_D) == true || pPad[JPPRESS_RIGTH] == true)
	{// 右
		g_Player.PlayerDire = DIRECTION_RIGTH;				// 向き
		g_fTexY = DIRECTION_RIGTH;							// アニメテクスチャY
		if (g_Player.Junp == false)
		{// アニメーションカウンター開始
			g_nConterAnim += 1;								// アニメーションカウンター
			if ((g_nConterAnim % 5) == 0)
			{// アニメーション速度
				g_nPatternAnim += 1;						// アニメテクスチャX
			}
		}
	}
	//else if (GetKeyboardPresse(DIK_A) == true || pPad[JPPRESS_LEFT] == true)
	//{// 左
	//	g_Player.PlayerDire = DIRECTION_LEFT;				// 向き
	//	g_fTexY = DIRECTION_LEFT;							// アニメテクスチャY

	//	if (g_Player.Junp == false)
	//	{// アニメーションカウンター開始
	//		g_nConterAnim += 1;								// アニメーションカウンター
	//		if ((g_nConterAnim % 5) == 0)
	//		{// アニメーション速度
	//			g_nPatternAnim += 1;						// アニメテクスチャX
	//		}
	//	}
	//}
	//else if (GetKeyboardPresse(DIK_A) == false)
	//{// 止まった時
	//	g_nPatternAnim = 0;									// アニメーションストップ
	//}
	else if (GetKeyboardPresse(DIK_D) == false)
	{// 止まった時
		g_nPatternAnim = 0;									// アニメーションストップ
	}
	if (g_Player.Junp == false)
	{// 空中にいないとき
		if (GetKeyboardTrigger(DIK_J) == true || GetKeypadTrigger(0) == true)
		{// ジャンプ開始
			g_Player.move.y -= 20.0f;						// ジャンプ力
			g_Player.Junp = true;							// ジャンプ中
		}
	}
	if (g_Player.Junp == true)
	{// 空中にいるとき
		g_nPatternAnim = 1;									// アニメーションストップ
	}
	if (g_Player.move.y != 0.0f)
	{// ジャンプ不可
		g_Player.Junp = true;								// 空中
	}
}

//=====================================================================================================================================================================//
// プレイヤーのダメージ
//=====================================================================================================================================================================//
bool HitPlayer(int Damage)
{
	// ダメージ
	g_Player.nLife -= Damage;

	if (g_Player.nLife == 0)
	{// LIFEがゼロになった場合

		// プレイヤー死亡
		g_Player.PlayerState = PLAYERSTATE_DEATH;

		// 透明度を半分にする
		g_nAlpha /= 2;

		// 出現状態にする
		g_Player.PlayerState = PLAYERSTATE_WAIT;

		return true;
	}
	else
	{
		// 状態をダメージ
		g_Player.PlayerState = PLAYERSTATE_DAMAGE;

		return false;
	}
}


//=====================================================================================================================================================================//
// プレイヤー情報の取得
//=====================================================================================================================================================================//
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

