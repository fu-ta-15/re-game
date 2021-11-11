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
#define CAMERA_POS_Y		(100.0f)										 // カメラのY座標
#define CAMERA_POS_Z		(-200.0f)										 // カメラのZ座標
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

	// キー入力クラスのポインタ
	CKey *pKey = CManager::GetKey();

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_Z))
	{
		m_rot.y -= 0.005f;

		if (m_rot.y < -D3DX_PI)
		{// 3.14fより大きくなったとき値を-3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}

		// 注視点の更新
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_C))
	{
		m_rot.y += 0.005f;

		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったとき値を-3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}

		// 注視点の更新
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_Q))
	{
		m_rot.y -= 0.05f;						// 回転量

		if (m_rot.y < -D3DX_PI)
		{// 3.14fより大きくなったとき値を-3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}

		// 視点の更新
		m_posV.x = m_posR.x - sinf(m_rot.y) * 200;
		m_posV.z = m_posR.z - cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_E))
	{
		m_rot.y += 0.05f;						// 回転量

		if (m_rot.y > D3DX_PI)
		{// -3.14fより小さくなったとき値を3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		// 視点の更新
		m_posV.x = m_posR.x - sinf(m_rot.y) * 200;
		m_posV.z = m_posR.z - cosf(m_rot.y) * 200;
	}

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_T))
	{
		// 注視点の上移動
		m_posR.y += 1.0f;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_B))
	{
		// 注視点の下移動
		m_posR.y -= 1.0f;
	}

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_UP))
	{
		// 視点の前移動
		m_posV.x += 1.0f * sinf(m_rot.y);
		m_posV.z += 1.0f * cosf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_DOWN))
	{
		// 視点の後ろ移動
		m_posV.x -= 1.0f * sinf(m_rot.y);
		m_posV.z -= 1.0f * cosf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_LEFT))
	{
		// 視点の左移動
		m_posV.x -= 1.0f * cosf(m_rot.y);
		m_posV.z += 1.0f * sinf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_RIGHT))
	{
		// 視点の右移動
		m_posV.x += 1.0f * cosf(m_rot.y);
		m_posV.z -= 1.0f * sinf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_Y))
	{
		// 視点の上移動
		m_posV.y += 3.0f;

	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_N))
	{
		// 視点の下移動
		m_posV.y -= 3.0f;
	}


	// 視点の更新
	//m_posV.x += (m_posVDest.x - m_posV.x) * 0.04f;
	//m_posV.z += (m_posVDest.z - m_posV.z) * 0.04f;
	//m_posV.y += (m_posVDest.y - m_posV.y) * 0.04f;

	// 注視点の更新
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
