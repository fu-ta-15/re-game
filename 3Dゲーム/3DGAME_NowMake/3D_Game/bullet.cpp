//##################################################################################################################################################################//
//
// 弾処理 [bullet.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "bullet.h"
#include "model.h"
#include "particle.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define BULLET_SIZE						(2.0f)							// 弾のサイズ
#define COLOR_RED						(255)						// 赤色
#define COLOR_BULUE						(255)						// 青色
#define COLOR_GREEN						(255)						// 緑色
#define COLOR_ALPHA						(255)						// アルファ値
#define RHW								(10/10)						// rhwの数値1.0固定
#define HALF_MATH						(2)							// 半分
#define PVTEX_MAX						(4)							// pVtx

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureBullet = NULL;		// テクスチャの情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファの情報
BULLET g_aBullet[MAX_BULLET];						// 弾の情報


//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ
	BULLET *pBullet = &g_aBullet[0];

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureBullet);

	if (g_apTextureBullet == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\bullet000.png");
	}

	// 弾の初期化設定
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pBullet->BulletSize = BULLET_SIZE;
		pBullet->nLife = 0;
		pBullet->bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファのロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		// 各頂点座標
		pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->BulletSize, pBullet->pos.y + pBullet->BulletSize, pBullet->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->BulletSize, pBullet->pos.y + pBullet->BulletSize, pBullet->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->BulletSize, pBullet->pos.y - pBullet->BulletSize, pBullet->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->BulletSize, pBullet->pos.y - pBullet->BulletSize, pBullet->pos.z);

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
	g_pVtxBuffBullet->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	if (g_apTextureBullet != NULL)
	{
		g_apTextureBullet->Release();
		g_apTextureBullet = NULL;
	}
}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateBullet(void)
{
	// 構造体のポインタ
	VERTEX_3D *pVtx;
	BULLET *pBullet;
	Player *pPlayer = GetPlayer();


	// 構造体の情報取得
	pBullet = &g_aBullet[0];

	// 頂点バッファのロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// 位置の更新
			pBullet->pos.z -= pBullet->move.z * 2.5f;
			pBullet->pos.x += pBullet->move.x * 2.5f;
			pBullet->pos.y = pPlayer->aModel[0].pos.y + pPlayer->pos.y;

			// ライフの減少
			pBullet->nLife -= 2;

			// 寿命チェック
			if (pBullet->nLife == 0)
			{
				// 0になったらフォルスに変える
				pBullet->bUse = false;
			}
		}
		// 4頂点ずつずれる
		pVtx += PVTEX_MAX;
	}
	// 頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawBullet(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxTrans;
	// ビューマトリックス取得用
	D3DXMATRIX mtxView;

	BULLET *pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pBullet->mtxWorld);

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView); // 逆行列を求める

			pBullet->mtxWorld._41 = 0.0f;
			pBullet->mtxWorld._42 = 0.0f;
			pBullet->mtxWorld._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBullet);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);

			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		}
	}
}

//=====================================================================================================================================================================//
// 弾の設定処理
//=====================================================================================================================================================================//
void SetBullet(D3DXVECTOR3 pos, float movex, float movez, int nLife)
{
	//ポインタ
	VERTEX_3D *pVtx;

	//頂点バッファのロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	BULLET *pBullet = &g_aBullet[0];
	Player *pPlayer = GetPlayer();


	//弾の設定
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{//使用されていない弾

			// 位置の設定
			pBullet->pos.x = pos.x - sinf(pPlayer->rot.y) * 10.0f;
			pBullet->pos.z = pos.z - cosf(pPlayer->rot.y) * 10.0f;
			pBullet->pos.y = pos.y + 2.0f;

			// 移動の設定
			pBullet->move.z = movez;
			pBullet->move.x = movex;

			// 寿命の設定
			pBullet->nLife = nLife;

			// 弾を発射
			pBullet->bUse = true;

			SetParticle(pos, D3DXVECTOR3(movex,0.0f, movez), 10, 50, D3DXCOLOR(0.37f, 0.28f, 0.78f, 1.0f));

			break;
		}
		pVtx += PVTEX_MAX;	// 頂点情報を4進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();


}

BULLET * GetBullet(void)
{
	return &g_aBullet[0];
}
