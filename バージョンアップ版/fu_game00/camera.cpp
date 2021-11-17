//*****************************************************************************
//																																								
// カメラ処理 [camera.cpp]																																		
// Author : SUZUKI FUUTA																																		
//																																								
//*****************************************************************************
//-----------------------------------------------------------------------------
//　インクルードファイル
//-----------------------------------------------------------------------------
#include "camera.h"
#include "keyinput.h"
#include "Dinput.h"
#include "player.h"
#include "fade.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
// マクロ
//-----------------------------------------------------------------------------
#define CAMERA_POS_Y		(500.0f)										 // カメラのY座標
#define CAMERA_POS_Z		(500.0f)										 // カメラのZ座標
#define INIT_CAMERA_POSV	(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))	 // カメラの視点位置

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_posV = INIT_CAMERA_POSV;					// 視点(現在)
	m_posR = ZeroVector3;						// 注視点(現在)
	m_posVDest = ZeroVector3;					// 視点(目的)
	m_posRDest = ZeroVector3;					// 注視点(目的)
	m_moveX = ZeroVector3;						// 移動量
	m_moveZ = ZeroVector3;						// 移動量
	m_moveVY = ZeroVector3;						// 移動量
	m_moveRY = ZeroVector3;						// 移動量
	m_rot = ZeroVector3;						// カメラの向き
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 上方向ベクトル
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CCamera::Init(void)
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// カメラの更新
//=============================================================================
void CCamera::Update(void)
{
	//// 視点の更新
	//m_posV.x += (m_posVDest.x - m_posV.x) * 0.04f;
	//m_posV.z += (m_posVDest.z - m_posV.z) * 0.04f;
	//m_posV.y += (m_posVDest.y - m_posV.y) * 0.04f;

	//// 注視点の更新
	//m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
	//m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;
	//m_posR.y += (m_posRDest.y - m_posR.y) * 0.08f;
}

//=============================================================================
// カメラの設置
//=============================================================================
void CCamera::SetCamera(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							// 画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// 比率
		50.0f,											// 手前距離
		6000.0f);										// 奥の距離

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
