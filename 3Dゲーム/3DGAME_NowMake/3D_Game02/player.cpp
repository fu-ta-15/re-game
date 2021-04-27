//##################################################################################################################################################################//
//																																									//
// プレイヤー処理 [player.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "player.h"
#include "keyinput.h"
#include "camera.h"
#include "shadow.h"
#include "memory.h"
#include "effect.h"
#include "Dinput.h"
#include "light.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.5f)					// モデルのスピード
#define MAX_SIZE_MEMORY		(1000)					// メモリのサイズ
#define PI_TWICE			(D3DX_PI * 2.0f)	
#define SPEED_CONTROL		(0.08f)
#define NEXT_KEY			(g_Player.nKey_No + 1)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Player g_Player;	// プレイヤー（モデル）の構造体
MOTION_TYPE g_MotionType = MOTION_TYPE_NOMAL;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// プロトタイプ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void MovePlayerKey(void);
void MovePlayerPad(void);
void MotionPlayer(MOTION_TYPE type);
void RotControlPlayer(void);
void SetMotionPlayer(void);
void SetPlayerModel(void);
void GetVtxPlayer(void);

//==================================================================================================================================================================//
// 初期化処理
//==================================================================================================================================================================//
void InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	SetPlayerModel();

	/* プレイヤー */
	g_Player.pos = VECTOR_ZERO;
	g_Player.rot = VECTOR_ZERO;
	g_Player.move = VECTOR_ZERO;
	g_Player.rotDest = VECTOR_ZERO;
	g_Player.nNumShadow = 1;
	g_Player.nNumModel = MODEL_MAX;

	// 影の設定
	g_Player.nNumShadow = SetShadow(g_Player.pos, 10.0f, 10.0f);

	/* モーション */
	g_Player.nKey_No = 0;
	g_Player.nCounterMotion = 0;
	g_Player.bLoopMotion = false;

	// モーションの設定
	SetMotionPlayer();

	// ファイルの読み込み
	/* No.0 体 */
	D3DXLoadMeshFromX("data\\suzuki_model\\body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].NumMat, &g_Player.aModel[0].pMesh);
	
	/* No.1 頭 */
	D3DXLoadMeshFromX("data\\suzuki_model\\hed.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].NumMat, &g_Player.aModel[1].pMesh);
	
	// パーツの頂点座標取得
	GetVtxPlayer();
}

//==================================================================================================================================================================//
// 終了処理
//==================================================================================================================================================================//
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{// メッシュの破棄
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{// マテリアルの破棄
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//==================================================================================================================================================================//
// 更新処理
//==================================================================================================================================================================//
void UpdatePlayer(void)
{
	// カメラのポインタ
	Camera *pCamera = GetCamera();

	// モデルの移動
	MovePlayerPad();   // パッド

	MovePlayerKey();   // キーボード

	// モデルのモーション
	MotionPlayer(g_MotionType);

	// 位置の更新
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// 回転の制御
	RotControlPlayer();

	// 移動・回転量の減衰
	g_Player.move.x += (0 - g_Player.move.x) * SPEED_CONTROL;
	g_Player.move.y += (0 - g_Player.move.y) * SPEED_CONTROL;
	g_Player.move.z += (0 - g_Player.move.z) * SPEED_CONTROL;

	// 影の設定
	SetPositionShadow(g_Player.nNumShadow, g_Player.pos);
}

//==================================================================================================================================================================//
// 描画処理
//==================================================================================================================================================================//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX mtxShadow;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, nomal;
	D3DXPLANE plane;
	D3DLIGHT9 *pLight = &GetLight();

	VecLight = D3DXVECTOR4(pLight->Direction.x, -pLight->Direction.y, pLight->Direction.z, 0.0f);
	pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	nomal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	/* プレイヤー（見えない原点）の設定 */
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用
		D3DXMATRIX mtxParent;					// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// 各パーツの向き
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// 各パーツの位置
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// 各パーツの親マトリックスを設定
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{// 親のインデックスを設定
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{// プレイヤーマトリックスを設定
			mtxParent = g_Player.mtxWorld;
		}

		// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
							&g_Player.aModel[nCntModel].mtxWorld,
							&mtxParent);


		// 各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_Player.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデルの描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}

		// 影の描画
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//プレイヤーのワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxShadow);
			D3DXPlaneFromPointNormal(&plane, &pos, &nomal);
			D3DXMatrixShadow(&mtxShadow, &VecLight, &plane);
			D3DXMatrixMultiply(&mtxShadow, &g_Player.aModel[nCntModel].mtxWorld, &mtxShadow);
			pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

			// モデルの描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================================================================================//
// モデルの移動(キーボード)
//==================================================================================================================================================================//
void MovePlayerKey(void)
{
	Camera *pCamera = GetCamera();

	/*モデル操作*/

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{// SPACEをしたら
		g_Player.move.x += (g_Player.move.x) * 2.3f;
		g_Player.move.z += (g_Player.move.z) * 2.3f;
	}

	// 前移動・後移動
	if (GetKeyboardPresse(DIK_UP) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 4 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 4 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = 0.0f - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_DOWN) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_RIGHT) == true)
	{// 右移動・左移動
		g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 + pCamera->rot.y ;
	}
	else if (GetKeyboardPresse(DIK_LEFT) == true)
	{
		g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;
	}

	if (GetKeyboardPresse(DIK_LEFT) == true || GetKeyboardPresse(DIK_RIGHT) == true || GetKeyboardPresse(DIK_DOWN) == true || GetKeyboardPresse(DIK_UP) == true) g_MotionType = MOTION_TYPE_MOVE;
	else g_MotionType = MOTION_TYPE_NOMAL;
}

//==================================================================================================================================================================//
// モデルの移動(パッド)
//==================================================================================================================================================================//
void MovePlayerPad(void)
{
	// カメラのポインタ
	Camera *pCamera = GetCamera();

	if (GetKeypadTrigger(D_BUUTON_Y) == true)
	{// SPACEをしたら
		g_Player.move.x += (g_Player.move.x) * 2.3f;
		g_Player.move.z += (g_Player.move.z) * 2.3f;
	}

	// 上移動・下移動
	if (GetKeypadPresse(D_BUUTON_RT) == true)
	{
		g_Player.move.y += MODEL_SPEED;
	}
	if (GetKeypadPresse(D_BUUTON_LT) == true)
	{
		g_Player.move.y -= MODEL_SPEED;
	}

	DIJOYSTATE2 *pController = pGetPadCont();					// コントローラー情報のポインタ

	if (pController->lX != 0 || pController->lY != 0)
	{// スティックが傾いたら
	 // スティックの傾けている位置
		float fAngle = atan2f((float)pController->lX, -(float)pController->lY);

		g_Player.move.x += sinf((D3DX_PI + fAngle) - pCamera->rot.y) * MODEL_SPEED;			// X軸移動量の決定
		g_Player.move.z += cosf((D3DX_PI + fAngle) - pCamera->rot.y) * MODEL_SPEED;			// Z軸移動量の決定

		g_Player.rotDest.y = fAngle - pCamera->rot.y;

		// モーション情報
		g_MotionType = MOTION_TYPE_MOVE;
	}
	else g_MotionType = MOTION_TYPE_NOMAL;
}

//==================================================================================================================================================================//
// モーション管理
//==================================================================================================================================================================//
void MotionPlayer(MOTION_TYPE type)
{
	if (type == MOTION_TYPE_NOMAL)
	{
		// 次のキー
		int NextKey;

		// 現在のキーがキーの総数を超えたら
		if ((g_Player.nKey_No + 1) > g_Player.aMotionInfo[type].nNumKey)
		{
			NextKey = 0;
		}
		else
		{
			NextKey = NEXT_KEY;
		}

		// モーションカウンター開始
		g_Player.nCounterMotion++;

		if (g_Player.nCounterMotion > g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame)
		{// モーションカウンターがそのキーのフレームより大きくなったら

			g_Player.nCounterMotion = 0;	// カウンターを初期化する
			g_Player.nKey_No++;				// キーを次に

			if (g_Player.nKey_No + 1 > g_Player.aMotionInfo[type].nNumKey && g_Player.aMotionInfo[type].bLoop == true)
			{// 現在のキーのナンバーがそのモーションのキー数を超えた場合
				g_Player.nKey_No = 0;	// キーの初期化
			}
		}

		// モーションの更新
		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aModel[nCntModel].pos.x += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_X + (g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Pos_X - g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_X) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].pos.y += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Y + (g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Pos_Y - g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Y) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].pos.z += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Z + (g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Pos_Z - g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Z) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);

			g_Player.aModel[nCntModel].rot.x += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_X + (g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_X - g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Rot_X) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].rot.y += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Y + (g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Y - g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Rot_Y) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].rot.z += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Z + (g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Z - g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Rot_Z) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
		}
	}
}

//==================================================================================================================================================================//
// 角度制御
//==================================================================================================================================================================//
void RotControlPlayer(void)
{
	// 目的回転制限
	if ((g_Player.rotDest.y - g_Player.rot.y) > D3DX_PI)
	{
		g_Player.rotDest.y -= PI_TWICE;
	}
	if ((g_Player.rotDest.y - g_Player.rot.y) < (-D3DX_PI))
	{
		g_Player.rotDest.y += PI_TWICE;
	}

	// 向いてる方向
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	// 回転制限
	if (g_Player.rot.y < (-D3DX_PI))
	{
		g_Player.rot.y += PI_TWICE;
	}
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= PI_TWICE;
	}
}

//==================================================================================================================================================================//
// モーションの設定
//==================================================================================================================================================================//
void SetMotionPlayer(void)
{
	/* モーション情報 */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].nNumKey = 2;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].bLoop = true;

	/* キー情報 */
	/* ニュートラル　キー１ */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].nFrame = 50;

	/* No.0 体 */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Pos_Y = 0.5f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Rot_Z = 0.0f;

	/* No.1 頭 */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Pos_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Rot_Z = 0.0f;

	/* ニュートラル　キー２ */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].nFrame = 50;

	/* No.0 体 */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Pos_Y = -0.5f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Rot_Z = 0.0f;

	/* No.1 頭 */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Pos_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Rot_Z = 0.0f;
}

//==================================================================================================================================================================//
// モデルパーツの位置設定
//==================================================================================================================================================================//
void SetPlayerModel(void)
{
	/* モデル */
	/* No.0 体 */
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].pMesh = NULL;
	g_Player.aModel[0].NumMat = NULL;
	g_Player.aModel[0].pBuffMat = NULL;
	g_Player.aModel[0].nIdxModelParent = -1;

	/* No.1 頭 */
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].pMesh = NULL;
	g_Player.aModel[1].NumMat = NULL;
	g_Player.aModel[1].pBuffMat = NULL;
	g_Player.aModel[1].nIdxModelParent = 0;
}

//==================================================================================================================================================================//
// モデルの頂点座標の取得
//==================================================================================================================================================================//
void GetVtxPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{

		/* モデルの頂点情報抜き出し */
		int nNumVtx;								// 頂点数
		DWORD sizeFVF;								// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;								// 頂点バッファへのポインタ
		float MinModel_X = 0.0f, MinModel_Z = 0.0f, MinModel_Y = 0.0f;	// 最小値保管用
		float MaxModel_X = 0.0f, MaxModel_Z = 0.0f, MaxModel_Y = 0.0f;	// 最大値保管用

																		// 頂点数を取得
		nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();
		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());
		// 頂点バッファをロック
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

			/* 最小値 */
			if (Vtx.x < MinModel_X)
			{// X座標
				MinModel_X = Vtx.x;
				g_Player.aModel[nCntModel].g_VtxMinModel.x = MinModel_X;
			}
			if (Vtx.y < MinModel_Y)
			{// Y座標
				MinModel_Y = Vtx.y;
				g_Player.aModel[nCntModel].g_VtxMinModel.y = MinModel_Y;
			}
			if (Vtx.z < MinModel_Z)
			{// Z座標
				MinModel_Z = Vtx.z;
				g_Player.aModel[nCntModel].g_VtxMinModel.z = MinModel_Z;
			}

			/* 最大値 */
			if (Vtx.x > MaxModel_X)
			{// X座標
				MaxModel_X = Vtx.x;
				g_Player.aModel[nCntModel].g_VtxMaxModel.x = MaxModel_X;
			}
			if (Vtx.y > MaxModel_Y)
			{// Y座標
				MaxModel_Y = Vtx.y;
				g_Player.aModel[nCntModel].g_VtxMaxModel.y = MaxModel_Y;
			}
			if (Vtx.z > MaxModel_Z)
			{// Z座標
				MaxModel_Z = Vtx.z;
				g_Player.aModel[nCntModel].g_VtxMaxModel.z = MaxModel_Z;
			}
			pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
		}
		// 頂点バッファのアンロック
		g_Player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

}

//==================================================================================================================================================================//
// プレイヤーの情報
//==================================================================================================================================================================//
Player * GetPlayer(void)
{
	return &g_Player;
}