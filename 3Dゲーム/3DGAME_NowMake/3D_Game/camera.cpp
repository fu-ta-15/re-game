//##################################################################################################################################################################//
//																																									//
// カメラ処理 [camera.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "camera.h"
#include "keyinput.h"
#include "Dinput.h"
#include "model.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define CAMERA_POS_Y					(200.0f)
#define CAMERA_POS_Z					(-500.0f)
#define CAMERA_DISTANCE_V				(500.0f)
#define CAMERA_DISTANCE_R				(30.0f)
#define INIT_CAMERA_POSV				(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Camera g_camera;	//カメラの情報

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
void InitCamera(void)
{
	g_camera.posV = INIT_CAMERA_POSV;					// 視点(現在)
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点(現在)
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 視点(目的)
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 注視点(目的)
	g_camera.moveX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_camera.moveZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_camera.moveVY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_camera.moveRY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの向き
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 上方向ベクトル
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitCamera(void)
{



}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();

	MoveCamera();

	/*視点の操作*/
	// 右旋回・左旋回
	if (GetKeyboardPresse(DIK_Q) == true || GetKeypadPresse(D_BUUTON_LB) == true)
	{
		g_camera.rot.y -= 0.03f;
		if (g_camera.rot.y < (-D3DX_PI))
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPresse(DIK_E) == true || GetKeypadPresse(D_BUUTON_RB) == true)
	{
		g_camera.rot.y += 0.03f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI*2.0f;
		}
	}
	// 上移動・下移動
	if (GetKeyboardPresse(DIK_Y) == true)
	{
		g_camera.moveVY.y += 1.0f;
	}
	if (GetKeyboardPresse(DIK_N) == true)
	{
		g_camera.moveVY.y -= 1.0f;
	}
	/*注視点の操作*/
	// 上移動・下移動
	if (GetKeyboardPresse(DIK_T) == true)
	{
		g_camera.moveRY.y += 1.0f;
	}
	if (GetKeyboardPresse(DIK_B) == true)
	{
		g_camera.moveRY.y -= 1.0f;
	}

	// 視点の制御
	g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y + D3DX_PI) * CAMERA_DISTANCE_V;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y - D3DX_PI) * CAMERA_DISTANCE_V;
	g_camera.posVDest.y = pPlayer->pos.y + CAMERA_POS_Y + g_camera.moveVY.y;

	//// 注視点の制御
	g_camera.posRDest.x = pPlayer->pos.x;
	g_camera.posRDest.z = pPlayer->pos.z;
	g_camera.posRDest.y = pPlayer->pos.y;

	// 視点の更新
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.04f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.04f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.04f;

	// 注視点の更新
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.08f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.08f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.08f;
}

//=====================================================================================================================================================================//
// カメラの移動
//=====================================================================================================================================================================//
void MoveCamera(void)
{
	/*カメラの移動*/
	// 前移動・後移動
	if (GetKeyboardPresse(DIK_W) == true)
	{
		if (GetKeyboardPresse(DIK_A) == true)
		{
			g_camera.moveX.x -= sinf(g_camera.rot.y + D3DX_PI * 1 / 4);
			g_camera.moveZ.z += cosf(g_camera.rot.y + D3DX_PI * 1 / 4);
		}
		else if (GetKeyboardPresse(DIK_D) == true)
		{
			g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI * 3 / 4);
			g_camera.moveZ.z -= cosf(g_camera.rot.y + D3DX_PI * 3 / 4);
		}
		else
		{
			g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI);
			g_camera.moveZ.z -= cosf(g_camera.rot.y - D3DX_PI);
		}
	}
	else if (GetKeyboardPresse(DIK_S) == true)
	{
		if (GetKeyboardPresse(DIK_D) == true)
		{
			g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI * 1 / 4);
			g_camera.moveZ.z -= cosf(g_camera.rot.y + D3DX_PI * 1 / 4);
		}
		else if (GetKeyboardPresse(DIK_A) == true)
		{
			g_camera.moveX.x -= sinf(g_camera.rot.y + D3DX_PI * 3 / 4);
			g_camera.moveZ.z += cosf(g_camera.rot.y + D3DX_PI * 3 / 4);
		}
		else
		{
			g_camera.moveX.x -= (sinf(g_camera.rot.y + D3DX_PI));
			g_camera.moveZ.z += (cosf(g_camera.rot.y - D3DX_PI));
		}
	}
	else if (GetKeyboardPresse(DIK_A) == true)
	{// 左移動・右移動
		g_camera.moveX.x -= sinf(g_camera.rot.y + D3DX_PI / 2);
		g_camera.moveZ.z += cosf(g_camera.rot.y + D3DX_PI / 2);
	}
	else if (GetKeyboardPresse(DIK_D) == true)
	{
		g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI / 2);
		g_camera.moveZ.z -= cosf(g_camera.rot.y + D3DX_PI / 2);
	}

	/*注視点の操作*/
	//// 右旋回・左旋回
	//if (GetKeyboardPresse(DIK_Q) == true)
	//{
	//	g_camera.rot.y += 0.02f;
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI*2.0f;
	//	}
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y + D3DX_PI) * 150.0f;
	//	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y - D3DX_PI) * 150.0f;
	//}
	//if (GetKeyboardPresse(DIK_E) == true)
	//{
	//	g_camera.rot.y -= 0.02f;
	//	if (g_camera.rot.y < (-D3DX_PI))
	//	{
	//		g_camera.rot.y += D3DX_PI*2.0f;
	//	}
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y + D3DX_PI) * 150.0f;
	//	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y - D3DX_PI) * 150.0f;
	//}

}

//=====================================================================================================================================================================//
// 設定処理
//=====================================================================================================================================================================//
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),							// 画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// 比率
		50.0f,											// 手前距離
		3000.0f);										// 奥の距離

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}


Camera *GetCamera(void)
{
	return &g_camera;
}
