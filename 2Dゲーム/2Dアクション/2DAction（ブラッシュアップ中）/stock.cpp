//##################################################################################################################################################################//
//
// スコア処理 [score.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "stock.h"
#include "ranking.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_STOCK			(6)

#define POS_DINTANCE		(30)
#define STOCK_STZEX			(90)
#define STOCK_SIZEXX		(120)


#define TAkARA_POSX			(90)
#define TAkARA_POSXX		(120)
#define TAkARA_POSY			(85)
#define TAkARA_POSYY		(45)

#define ATTACK_POSX			(90)
#define ATTACK_POSXX		(120)
#define ATTACK_POSY			(140)
#define ATTACK_POSYY		(100)

#define BLOCK_POSX			(200)
#define BLOCK_POSXX			(230)
#define BLOCK_POSY			(140)
#define BLOCK_POSYY			(100)

#define STOCK_TAKARA		(2)
#define STOCK_ATTACK		(4)
#define STOCK_BLOCK			(6)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureStock = NULL;;		//テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStock = NULL;	//頂点バッファへのポインタ
int g_nStock;
STOCK g_Stock[STOCK_TYPE_MAX];

//初期化処理
HRESULT InitStock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntStock = 0; nCntStock < STOCK_TYPE_MAX; nCntStock++)
	{
		g_Stock[nCntStock].nStock = 0;
	}

	//変数の初期化
	g_nStock = 0;
	srand((unsigned int)time(0));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cunt00.png", &g_pTextureStock);

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_STOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffStock, NULL)))
	{// 頂点バッファの生成
		return E_FAIL;
	}

	//ポリゴン・テクスチャの初期化設定
	for (int nCntStock = 0; nCntStock < STOCK_TYPE_MAX; nCntStock++)
	{
		pVtxSet(nCntStock);
	}

	AddStock(0, 0);
	AddStock(0, 1);
	AddStock(0, 2);

	return S_OK;
}

//終了処理
void UninitStock(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffStock != NULL)
	{
		g_pVtxBuffStock->Release();
		g_pVtxBuffStock = NULL;
	}

	//テクスチャの開放
	if (g_pTextureStock != NULL)
	{
		g_pTextureStock->Release();
		g_pTextureStock = NULL;
	}
}

//更新処理
void UpdateStock(void)
{


}

//描画処理
void DrawStock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStock);

	for (int nCntStock = 0; nCntStock < MAX_STOCK; nCntStock++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntStock * 4, 2);
	}
}

// ストックの加算
void AddStock(int nValue, int Type)
{
	int nMath = 100;	//スコア計算

	int aNumber[2];	//スコアのナンバー

	g_Stock[Type].nStock += nValue;		//スコア

	VERTEX_2D *pVtx;		//ポインタ

	switch (Type)
	{
	case STOCK_TYPE_TAKARA:
		//バッファのロック
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++)
		{
			//スコアの計算
			aNumber[nCntStock] = (g_Stock[STOCK_TYPE_TAKARA].nStock % nMath / (nMath / 10));

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 0);

			pVtx += 4;		//ポインタ座標を四つ進める
			nMath /= 10;	//割る10をして次の桁に
		}
		//バッファのアンロック
		g_pVtxBuffStock->Unlock();
		break;

	case STOCK_TYPE_ATTACK:
		//バッファのロック
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++)
		{
			//スコアの計算
			aNumber[nCntStock] = (g_Stock[STOCK_TYPE_ATTACK].nStock % nMath / (nMath / 10));

			//テクスチャ座標
			pVtx[8].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 1.0f);
			pVtx[9].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 0);
			pVtx[10].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 1.0f);
			pVtx[11].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 0);

			pVtx += 4;		//ポインタ座標を四つ進める
			nMath /= 10;	//割る10をして次の桁に
		}
		//バッファのアンロック
		g_pVtxBuffStock->Unlock();
		break;

	case STOCK_TYPE_BLOCK:
		//バッファのロック
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++)
		{
			//スコアの計算
			aNumber[nCntStock] = (g_Stock[STOCK_TYPE_BLOCK].nStock % nMath / (nMath / 10));

			//テクスチャ座標
			pVtx[16].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 1.0f);
			pVtx[17].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 0);
			pVtx[18].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 1.0f);
			pVtx[19].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 0);

			pVtx += 4;		//ポインタ座標を四つ進める
			nMath /= 10;	//割る10をして次の桁に
		}
		//バッファのアンロック
		g_pVtxBuffStock->Unlock();
		break;

	default:
		break;
	}
}

void pVtxSet(int Num)
{
	VERTEX_2D *pVtx;

	int nDice = 0;

	switch (Num)
	{
	case STOCK_TYPE_TAKARA:
		//頂点バッファのロック
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++, nDice++)
		{
			//各頂点座標
			pVtx[0].pos = D3DXVECTOR3(TAkARA_POSX + ((float)nDice * POS_DINTANCE), TAkARA_POSY, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(TAkARA_POSX + ((float)nDice * POS_DINTANCE), TAkARA_POSYY, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(TAkARA_POSXX + ((float)nDice * POS_DINTANCE), TAkARA_POSY, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(TAkARA_POSXX + ((float)nDice * POS_DINTANCE), TAkARA_POSYY, 0.0f);

			//rhwの設定		=	1.0f固定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定・赤・緑・青
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャの頂点座標の設定
			pVtx[0].tex = D3DXVECTOR2(0, 1);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(0.1f, 1);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

			//頂点4進める
			pVtx += 4;
		}
		break;
		//バッファのアンロック
		g_pVtxBuffStock->Unlock();

	case STOCK_TYPE_ATTACK:
		//頂点バッファのロック
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++, nDice++)
		{

			//各頂点座標
			pVtx[8].pos = D3DXVECTOR3(ATTACK_POSX + ((float)nDice * POS_DINTANCE), ATTACK_POSY, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(ATTACK_POSX + ((float)nDice * POS_DINTANCE), ATTACK_POSYY, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(ATTACK_POSXX + ((float)nDice * POS_DINTANCE), ATTACK_POSY, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(ATTACK_POSXX + ((float)nDice * POS_DINTANCE), ATTACK_POSYY, 0.0f);

			//rhwの設定		=	1.0f固定
			pVtx[8].rhw = 1.0f;
			pVtx[9].rhw = 1.0f;
			pVtx[10].rhw = 1.0f;
			pVtx[11].rhw = 1.0f;

			//頂点カラーの設定・赤・緑・青
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャの頂点座標の設定
			pVtx[8].tex = D3DXVECTOR2(0, 1);
			pVtx[9].tex = D3DXVECTOR2(0, 0);
			pVtx[10].tex = D3DXVECTOR2(0.1f, 1);
			pVtx[11].tex = D3DXVECTOR2(0.1f, 0);

			//頂点4進める
			pVtx += (4);
		}
		break;
		//バッファのアンロック
		g_pVtxBuffStock->Unlock();

	case STOCK_TYPE_BLOCK:
		//頂点バッファのロック
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++, nDice++)
		{
			//各頂点座標
			pVtx[16].pos = D3DXVECTOR3(BLOCK_POSX + ((float)nDice * POS_DINTANCE), BLOCK_POSY, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(BLOCK_POSX + ((float)nDice * POS_DINTANCE), BLOCK_POSYY, 0.0f);
			pVtx[18].pos = D3DXVECTOR3(BLOCK_POSXX + ((float)nDice * POS_DINTANCE), BLOCK_POSY, 0.0f);
			pVtx[19].pos = D3DXVECTOR3(BLOCK_POSXX + ((float)nDice * POS_DINTANCE), BLOCK_POSYY, 0.0f);

			//rhwの設定		=	1.0f固定
			pVtx[16].rhw = 1.0f;
			pVtx[17].rhw = 1.0f;
			pVtx[18].rhw = 1.0f;
			pVtx[19].rhw = 1.0f;

			//頂点カラーの設定・赤・緑・青
			pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[19].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャの頂点座標の設定
			pVtx[16].tex = D3DXVECTOR2(0, 1);
			pVtx[17].tex = D3DXVECTOR2(0, 0);
			pVtx[18].tex = D3DXVECTOR2(0.1f, 1);
			pVtx[19].tex = D3DXVECTOR2(0.1f, 0);

			//頂点4進める
			pVtx += (4);
		}
		break;
		//バッファのアンロック
		g_pVtxBuffStock->Unlock();

	default:
		break;
	}
}


STOCK *GetStock(void)
{
	return &g_Stock[0];
}