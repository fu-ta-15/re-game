//##################################################################################################################################################################//
//
// ブロック処理 [brock.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "brock.h"
#include "player.h"
#include "stage.h"
#include "backbg.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_BROCK			(1080)
#define MAX_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))
#define LENGTH_PLAYER_X		(30)								// 中心から各頂点の距離を求める数値
#define LENGTH_PLAYER_Y		(50)								// 中心から各頂点の距離を求める数値
#define MOVE_SPEED_RIGTH	(D3DXVECTOR3(-5.1f,0.0f,0.0f))
#define MOVE_SPEED_LEFT		(D3DXVECTOR3(5.1f,0.0f,0.0f))

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureBrock = NULL;;		//テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBrock = NULL;		//頂点バッファへのポインタ
BROCK g_Brock;
//=====================================================================================================================================================================//
//初期化処理
//=====================================================================================================================================================================//
HRESULT InitBrock(void)
{
	// ポインタ
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	g_Brock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Brock.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Brock.Oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Brock.bUse = false;
	g_Brock.fHeigth = 0.0f;
	g_Brock.fWidth = 0.0f;
	g_Brock.HitPlayer = false;
	g_Brock.BrockStop = BROCK_STOP_NO;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block.jpg", &g_pTextureBrock);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BROCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBrock, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファのロック
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	//rhwの設定		=	1.0f固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定・赤・緑・青
	pVtx[0].col = MAX_COLOR;
	pVtx[1].col = MAX_COLOR;
	pVtx[2].col = MAX_COLOR;
	pVtx[3].col = MAX_COLOR;

	//テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 1);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 0);

	//頂点バッファのアンロック
	g_pVtxBuffBrock->Unlock();

	return S_OK;
}

//=====================================================================================================================================================================//
//終了処理
//=====================================================================================================================================================================//
void UninitBrock(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBrock != NULL)
	{
		g_pVtxBuffBrock->Release();
		g_pVtxBuffBrock = NULL;
	}
	//テクスチャの開放
	if (g_pTextureBrock != NULL)
	{
		g_pTextureBrock->Release();
		g_pTextureBrock = NULL;
	}
}

//=====================================================================================================================================================================//
//更新処理
//=====================================================================================================================================================================//
void UpdateBrock(void)
{

}

//=====================================================================================================================================================================//
//描画処理
//=====================================================================================================================================================================//
void DrawBrock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBrock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBrock);

	if (g_Brock.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=====================================================================================================================================================================//
//ブロックの設置
//=====================================================================================================================================================================//
void SetBrock(D3DXVECTOR3 pos, float fWidth, float fHeigth)
{
	// ポインタ
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();


	//頂点バッファのロック
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Brock.bUse == false)
	{
		// 位置・高さ・幅
		g_Brock.pos = pos;
		g_Brock.pos.y -= fHeigth;
		if (pPlayer->PlayerDire == DIRECTION_LEFT)
		{
			g_Brock.pos.x -= fWidth;
		}
		g_Brock.fHeigth = fHeigth;
		g_Brock.fWidth = fWidth;

		//各頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_Brock.pos.x, g_Brock.pos.y + g_Brock.fHeigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Brock.pos.x, g_Brock.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Brock.pos.x + g_Brock.fWidth, g_Brock.pos.y + g_Brock.fHeigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Brock.pos.x + g_Brock.fWidth, g_Brock.pos.y, 0.0f);

		// 使用中にする
		g_Brock.bUse = true;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBrock->Unlock();
}


//=====================================================================================================================================================================//
//ブロックの移動
//=====================================================================================================================================================================//
void MoveBrock(void)
{
	// ポインタ
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;
	BROCK *pBrock;

	// 情報取得
	pPlayer = GetPlayer();
	pBrock = &g_Brock;

	//頂点バッファのロック
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	if (pBrock->bUse == true)
	{// 使用中
	 // 過去の座標保管
		pBrock->Oldpos.x = pBrock->pos.x;
		if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
		{// プレイヤーが右に進んでいる
		 // 移動量の代入
			pBrock->move = MOVE_SPEED_RIGTH;
		}
		else if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
		{// プレイヤーが左に進んでいる
		 // 移動量の代入
			pBrock->move = MOVE_SPEED_LEFT;
		}
		else if (pBrock->HitPlayer == true)
		{// プレイヤーにぶつかっている
			pBrock->move.x = 0.0f;
		}

		// 座標更新
		pBrock->pos.x += pBrock->move.x;

		// 判定を取得
		g_Brock.HitPlayer = CollisionPlayer(&pBrock->pos, &pBrock->Oldpos, &pBrock->move, pBrock->fWidth, pBrock->fHeigth);

		// 各頂点座標
		pVtx[0].pos = D3DXVECTOR3(pBrock->pos.x, pBrock->pos.y + pBrock->fHeigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pBrock->pos.x, pBrock->pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pBrock->pos.x + pBrock->fWidth, pBrock->pos.y + pBrock->fHeigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pBrock->pos.x + pBrock->fWidth, pBrock->pos.y, 0.0f);
	}
	//頂点バッファのアンロック
	g_pVtxBuffBrock->Unlock();
}

//=====================================================================================================================================================================//
//ブロックの情報
//=====================================================================================================================================================================//
BROCK *GetBrock(void)
{
	return &g_Brock;
}
