//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	camera.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "camera.h"

#include "main.h"
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "field.h"
#include "train.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCamera::CCamera()
{
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCamera::~CCamera()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CCamera::Init(void)
{
    //カメラの初期(位置・注意点・上方向)設定
    m_posV = D3DXVECTOR3(-350.0f, 1000.0f, 200.0f);
    m_posR = D3DXVECTOR3(400.0f, 0.0f, 0.0f);
    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //カメラの向き設定
    m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
    //カメラのプレイヤーからの距離設定
    //視点-注意点の距離の計算
    m_fDistance = (float)sqrt(pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCamera::Uninit(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCamera::Update(void)
{
	D3DXVECTOR3 pos;
	CTrain *pTrain = CGame::GetField()->GetTrain();
	
	pos = pTrain->GetPos();

	m_posR = pos + D3DXVECTOR3(0.0f, 0.0f, 250.0f);
	m_posR.x = 400.0f;
	m_posV = pos + D3DXVECTOR3(0.0f, 1000.0f, 325.0f);
	m_posV.x = -350.0f;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//カメラによる描画
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCamera::SetCamera(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    //デバイスへのポインタ
    //ビューマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxView);
    //ビューマトリックスの作成
    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    //ビューマトリックスの設定
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
    //プロジェクションマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxProjection);
    //プロジェクションマトリックスの作成
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
    //プロジェクションマトリックスの設定
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CCamera::GetRot(void)
{
    return m_rot;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
    //注視点を距離分の長さに補正して出力
    D3DXVECTOR3 vec;
    D3DXVec3Normalize(&vec, &(m_posR - m_posV));
    vec = vec * m_fDistance + m_posV;
    return vec;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCamera::SetRot(D3DXVECTOR3 rot)
{
    m_rot = rot;
}
