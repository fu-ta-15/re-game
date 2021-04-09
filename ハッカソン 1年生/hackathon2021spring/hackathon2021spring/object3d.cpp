//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene3d.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object3d.h"

#include "main.h"
#include "manager.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デフォルトコンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject3D::CObject3D()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject3D::~CObject3D()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CObject3D::Init()
{
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject3D::Uninit(void)
{
    CObject::Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject3D::Update(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject3D::Draw(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject3D::SetPosition(D3DXVECTOR3 pos)
{
    m_pos = pos;
}

void CObject3D::SetRotation(D3DXVECTOR3 rot)
{
    m_rot = rot;
}

void CObject3D::SetScale(D3DXVECTOR3 scale)
{
    m_size = scale;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CObject3D::GetPos(void)
{
    return m_pos;
}

D3DXVECTOR3 CObject3D::GetRot(void)
{
    return m_rot;
}

D3DXVECTOR3 CObject3D::GetSize(void)
{
    return m_size;
}
