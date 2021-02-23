//##################################################################################################################################################################//
//
// 弾処理 [bullet.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "bulletptcl.h"
#include "model.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define BULLET_SIZE						(4.0f)						// 弾のサイズ
#define COLOR_RED						(255)						// 赤色
#define COLOR_BULUE						(255)						// 青色
#define COLOR_GREEN						(255)						// 緑色
#define COLOR_ALPHA						(255)						// アルファ値
#define PVTEX_MAX						(4)							// pVtx
#define MAX_BULLETPTCL					(1000)						// 弾の最大数


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureBulletp = NULL;		// テクスチャの情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBulletp = NULL;	// 頂点バッファの情報
BParticle g_aBulletPtcl[MAX_BULLETPTCL];			// 弾の情報


//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitBulletPT(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ
	BParticle *pBulletPtcl = &g_aBulletPtcl[0];

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureBulletp);

	if (g_apTextureBulletp == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\bullet000.png");
	}

	// 弾の初期化設定
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		pBulletPtcl->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBulletPtcl->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBulletPtcl->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pBulletPtcl->BulletSize = BULLET_SIZE;
		pBulletPtcl->nLife = 0;
		pBulletPtcl->bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_BULLETPTCL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBulletp,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファのロック
	g_pVtxBuffBulletp->Lock(0, 0, (void**)&pVtx, 0);

	pBulletPtcl = &g_aBulletPtcl[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		// 各頂点座標
		pVtx[0].pos = D3DXVECTOR3(pBulletPtcl->pos.x - pBulletPtcl->BulletSize, pBulletPtcl->pos.y + pBulletPtcl->BulletSize, pBulletPtcl->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pBulletPtcl->pos.x + pBulletPtcl->BulletSize, pBulletPtcl->pos.y + pBulletPtcl->BulletSize, pBulletPtcl->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pBulletPtcl->pos.x - pBulletPtcl->BulletSize, pBulletPtcl->pos.y - pBulletPtcl->BulletSize, pBulletPtcl->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pBulletPtcl->pos.x + pBulletPtcl->BulletSize, pBulletPtcl->pos.y - pBulletPtcl->BulletSize, pBulletPtcl->pos.z);

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
	g_pVtxBuffBulletp->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitBulletPT(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBulletp != NULL)
	{
		g_pVtxBuffBulletp->Release();
		g_pVtxBuffBulletp = NULL;
	}
	if (g_apTextureBulletp != NULL)
	{
		g_apTextureBulletp->Release();
		g_apTextureBulletp = NULL;
	}
}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateBulletPT(void)
{
	// 構造体のポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	BParticle *pBulletPtcl;
	Player *pPlayer;
	pPlayer = GetPlayer();
	pBulletPtcl = &g_aBulletPtcl[0];

	// 頂点バッファのロック
	g_pVtxBuffBulletp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		if (pBulletPtcl->bUse == true)
		{
			// 位置の更新
			pBulletPtcl->pos.z -= pBulletPtcl->move.z * 2.5f;
			pBulletPtcl->pos.x += pBulletPtcl->move.x * 2.5f;
			pBulletPtcl->pos.y = pPlayer->aModel[0].pos.y + pPlayer->pos.y;

			// ライフの減少
			pBulletPtcl->nLife -= 2;

			// 寿命チェック
			if (pBulletPtcl->nLife == 0)
			{
				// 0になったらフォルスに変える
				pBulletPtcl->bUse = false;
			}
		}
		// 4頂点ずつずれる
		pVtx += PVTEX_MAX;
	}
	// 頂点バッファのアンロック
	g_pVtxBuffBulletp->Unlock();
}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawBulletPT(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxTrans;
	// ビューマトリックス取得用
	D3DXMATRIX mtxView;
	// 構造体の情報取得
	BParticle *pBulletPtcl;
	pBulletPtcl = &g_aBulletPtcl[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		if (pBulletPtcl->bUse == true)
		{
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pBulletPtcl->mtxWorld);

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pBulletPtcl->mtxWorld, NULL, &mtxView); // 逆行列を求める

			pBulletPtcl->mtxWorld._41 = 0.0f;
			pBulletPtcl->mtxWorld._42 = 0.0f;
			pBulletPtcl->mtxWorld._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBulletPtcl->pos.x, pBulletPtcl->pos.y, pBulletPtcl->pos.z);
			D3DXMatrixMultiply(&pBulletPtcl->mtxWorld, &pBulletPtcl->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pBulletPtcl->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBulletp, 0, sizeof(VERTEX_3D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBulletp);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);

			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}
}

//=====================================================================================================================================================================//
// 弾の設定処理
//=====================================================================================================================================================================//
void SetBulletPT(D3DXVECTOR3 pos, float movex, float movez, int nLife)
{
	//ポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	BParticle *pBulletPtcl;
	Player *pPlayer = GetPlayer();
	pBulletPtcl = &g_aBulletPtcl[0];

	//頂点バッファのロック
	g_pVtxBuffBulletp->Lock(0, 0, (void**)&pVtx, 0);

	//弾の設定
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{

			if (pBulletPtcl->bUse == false)
			{//使用されていない弾

			 // 位置の設定
				pBulletPtcl->pos.x = pos.x - sinf(pPlayer->rot.y) * 10.0f;
				pBulletPtcl->pos.z = pos.z - cosf(pPlayer->rot.y) * 10.0f;
				pBulletPtcl->pos.y = pos.y + 2.0f;

				// 移動の設定
				float fAngle = (float)((rand() % 628) - 628) / 100.f;
				pBulletPtcl->move.z = movez - sinf(fAngle);
				pBulletPtcl->move.x = movex - cosf(fAngle);

				// 寿命の設定
				pBulletPtcl->nLife = nLife;

				// 弾を発射
				pBulletPtcl->bUse = true;

				break;
		}
		pVtx += PVTEX_MAX;	// 頂点情報を4進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffBulletp->Unlock();
}

BParticle * GetBulletPT(void)
{
	return &g_aBulletPtcl[0];
}
