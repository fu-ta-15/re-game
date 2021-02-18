//##################################################################################################################################################################//
//
// パーティクル処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "particle.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_PARTICLE	(2000)
#define PARTICLE_SIZE	(20)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;		 // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	 // 頂点バッファのポインタ
PARTICLE g_aParticle[MAX_PARTICLE];					 // パーティクルの構造体

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\images.jfif", &g_pTextureParticle);

	// 各変数初期化
	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		g_aParticle[nCounterParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCounterParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCounterParticle].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCounterParticle].fRadius = 0.0f;
		g_aParticle[nCounterParticle].nLife = 0;
		g_aParticle[nCounterParticle].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファのロック
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		//各頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);

		//rhwの設定		=	1.0f固定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定・赤・緑・青
		pVtx[0].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);

		//テクスチャの頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点情報をサイズ分進める
		pVtx += 4;
	}
	// 頂点バッファのアンロック
	g_pVtxBuffParticle->Unlock();
	return S_OK;
}


//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitParticle(void)
{
	if (g_pVtxBuffParticle != NULL)
	{	// 頂点バッファの破棄
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
	if (g_pTextureParticle != NULL)
	{	// テクスチャの破棄
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
}


//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateParticle(void)
{
	VERTEX_3D *pVtx;

	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	PARTICLE *pParticle = &g_aParticle[0];

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			pParticle->nLife--;

			pParticle->pos -= pParticle->move;


			if (pParticle->nLife <= 0)
			{
				pParticle->bUse = false;
			}

		}
		pVtx += 4;
	}
	g_pVtxBuffParticle->Unlock();
}


//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawParticle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxTrans;
	// ビューマトリックス取得用
	D3DXMATRIX mtxView;

	PARTICLE *pParticle = &g_aParticle[0];
	
	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		if (g_aParticle[nCounterParticle].bUse == true)
		{


			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pParticle->mtxWorld);

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pParticle->mtxWorld, NULL, &mtxView); // 逆行列を求める

			pParticle->mtxWorld._41 = 0.0f;
			pParticle->mtxWorld._42 = 0.0f;
			pParticle->mtxWorld._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pParticle->pos.x, pParticle->pos.y, pParticle->pos.z);
			D3DXMatrixMultiply(&pParticle->mtxWorld, &pParticle->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pParticle->mtxWorld);


			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureParticle);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCounterParticle * 4, 2);

		}
	}
	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//=====================================================================================================================================================================//
// Particleの設定
//=====================================================================================================================================================================//
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, int number, int Life, D3DXCOLOR color)
{
	PARTICLE *pParticle;
	pParticle = &g_aParticle[0];

	for (int nCounterParticle = 0; nCounterParticle < number; nCounterParticle++, pParticle++)
	{
		for (int nCounterParticle = 0; nCounterParticle < number; nCounterParticle++, pParticle++)
		{
			if (pParticle->bUse == false)
			{
				// Particleの各ステータスを代入
				pParticle->pos = pos;		// 位置
				pParticle->color = color;	// 色
				pParticle->nLife = Life;	// 生存時間

				// 生成する角度
				float fAngle = (float)((rand() % 628) - 628) / 100.f;
				pParticle->move.x = move.x;	 // X方向の移動
				pParticle->move.z = move.z;	 // Y方向の移動
				pParticle->fRadius = (float)(rand() % 30) + 11;					 // 半径（大きさ）
				pParticle->bUse = true;											 // 使用中
				break;
			}
		}
	}
}

PARTICLE *GetParticle(void)
{
	return &g_aParticle[0];
}

