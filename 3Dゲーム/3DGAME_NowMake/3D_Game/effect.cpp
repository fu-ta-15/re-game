//##################################################################################################################################################################//
//
// エフェクト処理 [effect.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "effect.h"
#include "model.h"
#include "mob.h"
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define EFFECT_SIZEW					(6.0f)						// 弾のサイズ
#define EFFECT_SIZEH					(8.0f)						// 弾のサイズ
#define COLOR_RED						(255)						// 赤色
#define COLOR_BULUE						(255)						// 青色
#define COLOR_GREEN						(255)						// 緑色
#define COLOR_ALPHA						(255)						// アルファ値
#define PVTEX_MAX						(4)							// pVtx
#define MAX_EFFECT						(1000)						// 弾の最大数


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureEffect = NULL;		// テクスチャの情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファの情報
Effect g_aEffect[MAX_EFFECT];			// 弾の情報


//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ
	Effect *pEffect = &g_aEffect[0];

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Particle04_clear_hard.png", &g_apTextureEffect);

	if (g_apTextureEffect == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\bullet000.png");
	}

	// 弾の初期化設定
	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		pEffect->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);
		pEffect->EffectSizeW = EFFECT_SIZEW;
		pEffect->EffectSizeH = EFFECT_SIZEH;
		pEffect->fAngle = 0.0f;
		pEffect->fRadius = 0.0f;
		pEffect->nIdx = 0;
		pEffect->nLife = 0;
		pEffect->bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pEffect = &g_aEffect[0];

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		// 各頂点座標
		pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - pEffect->EffectSizeW, pEffect->pos.y + pEffect->EffectSizeH, pEffect->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x + pEffect->EffectSizeW, pEffect->pos.y + pEffect->EffectSizeH, pEffect->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x - pEffect->EffectSizeW, pEffect->pos.y - pEffect->EffectSizeH, pEffect->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + pEffect->EffectSizeW, pEffect->pos.y - pEffect->EffectSizeH, pEffect->pos.z);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定・赤・緑・青
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		// テクスチャの頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// プラス4進める
		pVtx += PVTEX_MAX;
	}

	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitEffect(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
	if (g_apTextureEffect != NULL)
	{
		g_apTextureEffect->Release();
		g_apTextureEffect = NULL;
	}
}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateEffect(void)
{
	// 構造体のポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	Effect *pEffect;
	Player *pPlayer;
	pPlayer = GetPlayer();
	pEffect = &g_aEffect[0];

	// 頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			// 過去の位置を保存
			pEffect->oldpos = pEffect->pos;

			// 位置の更新
			pEffect->move.y -= 1.3f;
			pEffect->pos.z += pEffect->move.z;
			pEffect->pos.x += pEffect->move.x;
			pEffect->pos.y += pEffect->move.y;

			// 移動量の減衰
			pEffect->move.z += (0.0f - pEffect->move.z) * 0.4f;
			pEffect->move.x += (0.0f - pEffect->move.x) * 0.4f;
			pEffect->move.y += (0.0f - pEffect->move.y) * 0.013f;

			if (pEffect->oldpos.y - EFFECT_SIZEW < 0)
			{// 前回の位置が床より下に行ったら

				// 移動の設定
				float fAngle = (float)((rand() % 628) - 628) / 100.f;

				pEffect->move.z = cosf(fAngle + D3DX_PI) * 8.0f;
				pEffect->move.x = sinf(fAngle - D3DX_PI) * 8.0f;

				pEffect->pos.y = 0 + EFFECT_SIZEW;
				pEffect->move.y += 20.0f;
			}

			// ライフの減少
			pEffect->nLife -= 1;

			// 寿命チェック
			if (pEffect->nLife == 0)
			{
				// 0になったらフォルスに変える
				pEffect->bUse = false;
			}
		}
		// 4頂点ずつずれる
		pVtx += PVTEX_MAX;
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawEffect(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxTrans;
	// ビューマトリックス取得用
	D3DXMATRIX mtxView;
	// 構造体の情報取得
	Effect *pEffect;
	Moblayer *pMoblayer = GetMoblayer();
	pEffect = &g_aEffect[0];

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	// ゼットバッファを無効
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ライトをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pEffect->mtxWorld, NULL, &mtxView); // 逆行列を求める

			pEffect->mtxWorld._41 = 0.0f;
			pEffect->mtxWorld._42 = 0.0f;
			pEffect->mtxWorld._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEffect);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);

				for (int nCntMob = 0; nCntMob < MOB_MAX; nCntMob++, pMoblayer++)
				{
					if (pMoblayer->bUse == true)
					{
						if (pMoblayer->pos.z > pEffect->pos.z)
						{
							pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
							pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

						}
					}
				}
		}
	}
	//ライトをオフにする														
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//=====================================================================================================================================================================//
// エフェクトの設定処理
//=====================================================================================================================================================================//
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float movex, float movez, float movey, int nIdx, int nLife)
{
	//ポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	Effect *pEffect;
	Player *pPlayer = GetPlayer();
	pEffect = &g_aEffect[0];


	//頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//弾の設定
	for (int nCntBullet = 0; nCntBullet < nIdx; nCntBullet++, pEffect++)
	{
			if (pEffect->bUse == false)
			{//使用されていない弾


			 // 位置の設定
				pEffect->pos.x = pos.x;
				pEffect->pos.z = pos.z;
				pEffect->pos.y = pos.y;

				// 移動の設定
				float fAngle = (float)((rand() % 628) - 628) / 100.f;
				// 情報代入
				pEffect->move.z = cosf(fAngle + D3DX_PI) * 3.0f;
				pEffect->move.x = sinf(fAngle - D3DX_PI) * 3.0f;
				pEffect->move.y = movey ;
				// 色情報を設定
				pEffect->color.r = col.r;
				pEffect->color.b = col.b;
				pEffect->color.g = col.g;
				pEffect->color.a = col.a;
				// 色情報を代入
				pVtx[0].col = pEffect->color;
				pVtx[1].col = pEffect->color;
				pVtx[2].col = pEffect->color;
				pVtx[3].col = pEffect->color;

				// 寿命の設定
				pEffect->nLife = nLife;

				// 弾を発射
				pEffect->bUse = true;

				break;
			}
		pVtx += PVTEX_MAX;	// 頂点情報を4進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();


}


Effect * GetEffect(void)
{
	return &g_aEffect[0];
}

