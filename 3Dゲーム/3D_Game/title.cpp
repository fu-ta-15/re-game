//##################################################################################################################################################################//
//
// プレイヤー処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "title.h"
#include "fade.h"
#include "player.h"
#include "keyinput.h"
#include "Dinput.h"
#include "sound.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_TITLEMODEL	(TITLEMODEL_MAX)
#define COLOR_RED		(255)	//赤色
#define COLOR_BULUE		(255)	//青色
#define COLOR_GREEN		(255)	//緑色
#define COLOR_ALPHA		(255)	//アルファ値


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファの情報
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLEMODEL] = {};	//テクスチャの情報
int g_TitleY[2];
int g_Buuton[2];
int g_nCunt;

//=====================================================================================================================================================================//
//ポリゴンの初期化処理
//=====================================================================================================================================================================//
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevi;
	g_TitleY[0] = -50;
	g_TitleY[1] = 1;
	g_Buuton[0] = 0;
	g_Buuton[1] = 1;
	g_nCunt = 0;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevi = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\titlelog.png", &g_apTextureTitle[0]);
	//D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\bg000.png", &g_apTextureTitle[1]);

	//頂点バッファの生成
	if (FAILED(pDevi->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLEMODEL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//各テクスチャの初期化設定
	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		if (nCunTil == TITLEMODEL_BG)
		{// 背景
			//頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

			//頂点カラーの設定・赤・緑・青
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		}
		//else if (nCunTil == TITLEMODEL_TITLE)
		//{// タイトルロゴ
		// //頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
		//	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		//	pVtx[1].pos = D3DXVECTOR3(0, 570, 0.0f);
		//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 570, 0.0f);

		//	//頂点カラーの設定・赤・緑・青
		//	pVtx[0].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		//	pVtx[1].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		//	pVtx[2].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		//	pVtx[3].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);

		//}
		//else if (nCunTil == TITLEMODEL_BUUTON)
		//{// ボタン
		//	//頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
		//	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		//	pVtx[1].pos = D3DXVECTOR3(0, 570, 0.0f);
		//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 570, 0.0f);

		//	//頂点カラーの設定・赤・緑・青
		//	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//}

		//rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャの頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 0);

		//pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	//PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//ポリゴンの終了処理
void UninitTitle(void)
{
	if (g_pVtxBuffTitle != NULL)
	{	//頂点バッファの開放
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		//テクスチャの開放
		if (g_apTextureTitle[nCunTil] != NULL)
		{
			g_apTextureTitle[nCunTil]->Release();
			g_apTextureTitle[nCunTil] = NULL;
		}
	}
	//StopSound(SOUND_LABEL_BGM000);	//BGM
}

//ポリゴンの更新処理
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;
	// フェードの情報
	FADE pFade;
	pFade = GetFade();
	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトルロゴが完成している場合
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeypadTrigger(3) == true)
		{
			SetFade(FADE_OUT, MODE_TUTORIAL);	//フェードアウト・ゲームモードに移行
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
}

//ポリゴンの描画処理
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTitle[nCunTil]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCunTil * 4, 2);		// 0//描画を開始する頂点インデックス
	}

}