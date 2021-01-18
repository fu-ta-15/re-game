//##################################################################################################################################################################//
//
// ゲージ処理 [gauge.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "gauge.h"
#include "input.h"
#include "fade.h"
#include "point.h"
#include "action.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define GAUGE_TYPE				(2)						//ゲージの種類
#define COLOR_RED				(255)					//赤色
#define COLOR_BULUE				(255)					//青色
#define COLOR_GREEN				(255)					//緑色
#define COLOR_ALPHA				(255)					//アルファ値

#define GAUGE_HEITH				(570)
#define GAUGE_START				(620.0f)
#define GAUGE_GOLE				(660.0f)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureGauge[GAUGE_TYPE] = {};	//テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;		//頂点バッファへのポインタ
GAUGE g_Gauge;

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitGauge(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Gauge.g_GaugeStart = GAUGE_START;
	g_Gauge.g_GaugeGole = GAUGE_GOLE;
	g_Gauge.g_GaugeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\life-geage.png", &g_apTextureGauge[0]);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGE_TYPE , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGauge, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunt = 0; nCunt < GAUGE_TYPE; nCunt++)
	{
		if (nCunt == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, GAUGE_HEITH, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, GAUGE_HEITH, 0.0f);

			//頂点カラーの設定・赤・緑・青
			pVtx[0].col = g_Gauge.g_GaugeColor;
			pVtx[1].col = g_Gauge.g_GaugeColor;
			pVtx[2].col = g_Gauge.g_GaugeColor;
			pVtx[3].col = g_Gauge.g_GaugeColor;
		}
		else if (nCunt == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, GAUGE_HEITH, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, GAUGE_HEITH, 0.0f);

			//頂点カラーの設定・赤・緑・青
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
		}

		//rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		pVtx += 4;
	}
	g_pVtxBuffGauge->Unlock();

	return S_OK;
}

//=====================================================================================================================================================================//
//
//=====================================================================================================================================================================//
void UninitGauge(void)
{
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
	for (int nCunt = 0; nCunt < GAUGE_TYPE; nCunt++)
	{
		if (g_apTextureGauge[nCunt] != NULL)
		{
			g_apTextureGauge[nCunt]->Release();
			g_apTextureGauge[nCunt] = NULL;
		}
	}
}

//=====================================================================================================================================================================//
//ゲージの更新
//=====================================================================================================================================================================//
void UpdateGauge(void)
{
	VERTEX_2D *pVtx;
	POINTER *pPoint = GetPointer();
	ACTIONPLAYER *pActionPlayer = GetAction();

	switch (pActionPlayer->Amode)
	{
	case ACTION_MODE_ATTACK:
		g_Gauge.g_GaugeStart = 620.0f;
		g_Gauge.g_GaugeGole = 660.0f;
		break;
	case ACTION_MODE_DIG:
		g_Gauge.g_GaugeStart = 625.0f;
		g_Gauge.g_GaugeGole = 655.0f;
		break;
	default:
		break;
	}
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, GAUGE_HEITH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, GAUGE_HEITH, 0.0f);

	//頂点カラーの設定・赤・緑・青
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);

	g_pVtxBuffGauge->Unlock();
}

//=====================================================================================================================================================================//
//
//=====================================================================================================================================================================//
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunt = 0; nCunt < GAUGE_TYPE; nCunt++)
	{
		pDevice->SetTexture(0, g_apTextureGauge[nCunt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCunt * 4 , 2);
	}
}

//=====================================================================================================================================================================//
//
//=====================================================================================================================================================================//
GAUGE *GetGauge(void)
{
	return &g_Gauge;
}
