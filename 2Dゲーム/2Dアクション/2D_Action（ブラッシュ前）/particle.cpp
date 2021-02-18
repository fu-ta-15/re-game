//##################################################################################################################################################################//
//
// プレイヤー処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//


#include "particle.h"
#include "point.h"
#include <stdlib.h>
#include <time.h>


#define MAX_PARTICLE	(2000)
#define PARTICLE_SIZE	(20)


LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;
PARTICLE g_aParticle[MAX_PARTICLE];
D3DXVECTOR3 g_posBase;



HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;


	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wepon0.png", &g_pTextureParticle);

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
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		//各頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y + PARTICLE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y - PARTICLE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y + PARTICLE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y - PARTICLE_SIZE, 0.0f);

		//rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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

		pVtx += 4;
	}
	g_pVtxBuffParticle->Unlock();
	return S_OK;
}



void UninitParticle(void)
{
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
}


void UpdateParticle(void)
{
	VERTEX_2D *pVtx;
	PARTICLE *pParticle;
	POINTER *pPoint = GetPointer();


	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	pParticle = &g_aParticle[0];

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			pParticle->nLife--;

			pParticle->pos -= pParticle->move;

			//各頂点座標
			pVtx[0].pos = D3DXVECTOR3(pParticle->pos.x - pParticle->fRadius, pParticle->pos.y + pParticle->fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pParticle->pos.x - pParticle->fRadius, pParticle->pos.y - pParticle->fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pParticle->pos.x + pParticle->fRadius, pParticle->pos.y + pParticle->fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pParticle->pos.x + pParticle->fRadius, pParticle->pos.y - pParticle->fRadius, 0.0f);


			if (pParticle->nLife <= 0)
			{
				pParticle->bUse = false;
			}

		}
		pVtx += 4;
	}
	g_pVtxBuffParticle->Unlock();
}



void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureParticle);

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		if (g_aParticle[nCounterParticle].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCounterParticle * 4, 2);
		}
	}
	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//3
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//4
}

void SetParticle(D3DXVECTOR3 pos, int number, int Life, D3DXCOLOR color)
{
	PARTICLE *pParticle;
	pParticle = &g_aParticle[0];

	for (int nCounterParticle = 0; nCounterParticle < number; nCounterParticle++, pParticle++)
	{
		for (int nCounterParticle = 0; nCounterParticle < number; nCounterParticle++, pParticle++)
		{
			if (pParticle->bUse == false)
			{
				pParticle->pos = pos;
				pParticle->color = color;
				pParticle->nLife = Life;

				float fAngle = (float)((rand() % 628) - 628) / 100.f;
				pParticle->move.x = sinf(fAngle) * (float)((rand() % 12) + 3);
				pParticle->move.y = cosf(fAngle) * (float)((rand() % 14) + 5);
				pParticle->fRadius = (float)(rand() % 30) + 11;
				pParticle->bUse = true;
				break;
			}
		}
	}
}
