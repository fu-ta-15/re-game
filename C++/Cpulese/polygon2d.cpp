//##################################################################################################################################################################//
//
// ポリゴン2Dソースファイル [polygon2d.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
//　インクルードファイル
//=====================================================================================================================================================================//
#include "polygon2d.h"
#include "manager.h"
#include "renderer.h"


CPolygon2d::CPolygon2d()
{
}

CPolygon2d::~CPolygon2d()
{
}

HRESULT CPolygon2d::Init(void)
{
	CPolygon::Init();
	return S_OK;
}

void CPolygon2d::Uninit(void)
{
	CPolygon::Uninit();
}

void CPolygon2d::Update(void)
{
	CPolygon::Update();
}

void CPolygon2d::Draw(void)
{
	CPolygon::Draw();
}

CPolygon2d * CPolygon2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPolygon2d *pPolygon2d = nullptr;
	pPolygon2d = new CPolygon2d;
	pPolygon2d->SetPos(pos);
	pPolygon2d->SetSize(size);
	pPolygon2d->Init();

	return pPolygon2d;
}
