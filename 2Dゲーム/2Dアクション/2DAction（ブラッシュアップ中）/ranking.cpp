//##################################################################################################################################################################//
//
// ランキング処理 [ranking.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "stdio.h"
#include "sound.h"
#include "padinput.h"
#include "rankingbg.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// 赤色
#define COLOR_BULUE			(255)			// 青色
#define COLOR_GREEN			(255)			// 緑色
#define COLOR_ALPHA			(255)			// アルファ値
#define RANKING_TEX			(12)				// ランキングの数
#define RANKING_TEX_HERF	(12/2)				// ランキングの数

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;		// テクスチャの情報
RANKING_SCORE g_RScore;


//=====================================================================================================================================================================//
// 背景の初期化処理
//=====================================================================================================================================================================//
HRESULT InitRanking(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点ポインタ
	VERTEX_2D *pVtx;

	// 構造体の変数初期化
	g_RScore.ChangScore = 0;
	g_RScore.NewScore = 0;
	g_RScore.OldScore = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cunt00.png", &g_pTextureRanking);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_TEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL)))
	{
		return E_FAIL;
	}

	////頂点バッファをロック・頂点情報へのポインタを取得
	//g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
	//pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	////rhwの設定		=	1.0f固定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// 頂点カラーの設定・赤・緑・青・アルファ
	//pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	//pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	//pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	//pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	////テクスチャの頂点座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0, 1);
	//pVtx[1].tex = D3DXVECTOR2(0, 0);
	//pVtx[2].tex = D3DXVECTOR2(1, 1);
	//pVtx[3].tex = D3DXVECTOR2(1, 0);

	////頂点バッファをアンロック
	//g_pVtxBuffRanking->Unlock();

	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunt = 0; nCunt < RANKING_TEX; nCunt++)
	{
		if (nCunt < RANKING_TEX_HERF)
		{
			//頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
			pVtx[0].pos = D3DXVECTOR3(300.0f + (nCunt * 50), SCREEN_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f + (nCunt * 50), 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(350.0f + (nCunt * 50), SCREEN_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(350.0f + (nCunt * 50), 200.0f, 0.0f);
		}
		else if (nCunt >= RANKING_TEX_HERF)
		{
			//頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
			pVtx[0].pos = D3DXVECTOR3(50.0f + (nCunt * 50), 600.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(50.0f + (nCunt * 50), 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(100.0f + (nCunt * 50), 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(100.0f + (nCunt * 50), 500.0f, 0.0f);
		}

		//rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定・赤・緑・青・アルファ
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//テクスチャの頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();

	// 過去の記録の保存
	OldRankingScore();

	PlaySound(SOUND_LABEL_BGM004);

	// 処理完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitRanking(void)
{
	//テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	StopSound(SOUND_LABEL_BGM004);	//BGM
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateRanking(void)
{
	//ポインタ
	VERTEX_2D *pVtx;
	FADE pFade;
	pFade = GetFade();
	//スコアのナンバー
	int aNumber[RANKING_TEX];

	if (pFade == FADE_NONE)
	{//フェイドが終わったら
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeypadTrigger(3) == true)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}

	//バッファのロック
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//スコア計算
	int nMath = 1000000;

	// 最近のスコア
	g_RScore.NewScore = GetScore();

	//スコアの変更
	for (int nCunNum = 0; nCunNum < 6; nCunNum++)
	{
		//スコアの計算
		aNumber[nCunNum] = (g_RScore.NewScore % nMath / (nMath / 10));

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		nMath /= 10;	//割る10をして次の桁に

		pVtx += 4;		//ポインタ座標を四つ進める
	}

	nMath = 1000000;		//スコア計算

	//スコアの変更
	for (int nCunNum = 6; nCunNum < RANKING_TEX; nCunNum++)
	{

		//スコアの計算
		aNumber[nCunNum] = (g_RScore.OldScore%nMath / (nMath / 10));

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		nMath /= 10;	//割る10をして次の桁に

		pVtx += 4; 		//ポインタ座標を四つ進める

	}

	//バッファのアンロック
	g_pVtxBuffRanking->Unlock();

	if (g_RScore.NewScore > g_RScore.OldScore)
	{// 新記録更新
		FILE *pFile;
		pFile = fopen("ranking.txt", "w");
		if (pFile != NULL)
		{// 書き込み
			fprintf(pFile, "%d", g_RScore.NewScore);
			fclose(pFile);
		}
	}
}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawRanking(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nScor = 0; nScor < RANKING_TEX; nScor++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRanking);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nScor * 4, 2);
	}
}
// 過去のスコアの読み込み
void OldRankingScore(void)
{
	// ファイルのポインタ
	FILE *pFile;
	// 読み込みモード
	pFile = fopen("ranking.txt", "r");

	if (pFile != NULL)
	{// 記録を読み込む
		fscanf(pFile, "%d", &g_RScore.OldScore);
		fclose(pFile);
	}
}
