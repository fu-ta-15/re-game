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
#include "player.h"
#include "fade.h"
#include "renderer.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define CAMERA_POS_Y					(200.0f)
#define CAMERA_POS_Z					(500.0f)
#define CAMERA_DISTANCE_V				(600.0f)
#define INIT_CAMERA_POSV				(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))
#define CAMERA_PAD_SPEED				(0.02f)	


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Camera g_camera;	//カメラの情報


void PadMoveCamera(void);
void KeyMoveCamera(void);
void CameraControl(MODE Mode);

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
void InitCamera(void)
{
	g_camera.posV		= INIT_CAMERA_POSV;					// 視点(現在)
	g_camera.posR		= VECTOR_ZERO;						// 注視点(現在)
	g_camera.posVDest	= VECTOR_ZERO;						// 視点(目的)
	g_camera.posRDest	= VECTOR_ZERO;						// 注視点(目的)
	g_camera.moveX		= VECTOR_ZERO;						// 移動量
	g_camera.moveZ		= VECTOR_ZERO;						// 移動量
	g_camera.moveVY		= VECTOR_ZERO;						// 移動量
	g_camera.moveRY		= VECTOR_ZERO;						// 移動量
	g_camera.rot		= VECTOR_ZERO;						// カメラの向き
	g_camera.vecU		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル
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
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:	// ゲームモード

		// カメラの移動
		PadMoveCamera();
		// カメラの制御
		CameraControl(Mode);
	default:
		break;
	}

}

//=====================================================================================================================================================================//
// カメラの移動
//=====================================================================================================================================================================//
void PadMoveCamera(void)
{
	// コントローラー情報のポインタ
	DIJOYSTATE2 *pController = pGetPadCont();					

	// カメラの移動
	if (pController->lZ > 0) g_camera.rot.y += CAMERA_PAD_SPEED;
	if (pController->lZ < 0) g_camera.rot.y -= CAMERA_PAD_SPEED;

	if (pController->lRz > 0) g_camera.rot.z -= CAMERA_PAD_SPEED;
	if (pController->lRz < 0) g_camera.rot.z += CAMERA_PAD_SPEED;


	/*視点の操作*/
	// 右旋回・左旋回
	if (GetKeypadPresse(D_BUUTON_RB) == true)
	{
		g_camera.rot.y -= CAMERA_PAD_SPEED;
	}
	if (GetKeypadPresse(D_BUUTON_LB) == true)
	{
		g_camera.rot.y += CAMERA_PAD_SPEED;
	}

	// カメラの上下の制御
	if (g_camera.rot.z > D3DX_PI / 2.0f)		g_camera.rot.z = D3DX_PI / 2.0f;
	else if (g_camera.rot.z < -D3DX_PI / 2.0f)	g_camera.rot.z = -D3DX_PI / 2.1f;

	if (g_camera.rot.z > -0.05f) g_camera.rot.z = -0.05f;	// 下に突き抜けないようにする

	//D3DXPI超えた時の対処
	// 以上
	if (g_camera.rot.x > D3DX_PI)	g_camera.rot.x -= D3DX_PI * 2.0f;
	if (g_camera.rot.y > D3DX_PI)	g_camera.rot.y -= D3DX_PI * 2.0f;
	if (g_camera.rot.z > D3DX_PI)	g_camera.rot.z -= D3DX_PI * 2.0f;
	// 以下
	if (g_camera.rot.x < -D3DX_PI)	g_camera.rot.x += D3DX_PI * 2.0f;
	if (g_camera.rot.y < -D3DX_PI)	g_camera.rot.y += D3DX_PI * 2.0f;
	if (g_camera.rot.z < -D3DX_PI)	g_camera.rot.z += D3DX_PI * 2.0f;
}

void KeyMoveCamera(void)
{
}

void CameraControl(MODE Mode)
{
	Player *pPlayer = GetPlayer();

	switch (Mode)
	{
	case MODE_GAME:

		// 視点の制御
		g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y + D3DX_PI) * CAMERA_DISTANCE_V;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y - D3DX_PI) * CAMERA_DISTANCE_V;
		g_camera.posVDest.y = pPlayer->pos.y - cosf(g_camera.rot.z - D3DX_PI) * CAMERA_POS_Y;

		//// 注視点の制御
		g_camera.posRDest.x = pPlayer->pos.x;
		g_camera.posRDest.z = pPlayer->pos.z;
		g_camera.posRDest.y = pPlayer->pos.y;
		break;

	default:
		break;
	}

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
		6000.0f);										// 奥の距離

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
