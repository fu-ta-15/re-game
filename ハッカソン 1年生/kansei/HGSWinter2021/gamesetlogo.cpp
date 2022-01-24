//==============================================================================
//
// ƒQ[ƒ€Œ‹‰ÊƒƒSˆ—kgamesetlogo.cppl
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "gamesetlogo.h"
#include "game.h"

//==============================================================================
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//==============================================================================
CGamesetLogo::CGamesetLogo(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// ƒfƒXƒgƒ‰ƒNƒ^
//==============================================================================
CGamesetLogo::~CGamesetLogo()
{

}

//==============================================================================
// ƒQ[ƒ€Œ‹‰ÊƒƒS‚Ì‰Šú‰»ˆ—
//==============================================================================
HRESULT CGamesetLogo::Init(void)
{
	if (m_pScene2D == NULL)
	{
		// 2Dƒ|ƒŠƒSƒ“‚ð¶¬
		m_pScene2D = CScene2D::Create();

		// ˆÊ’uÝ’è
		m_pScene2D->SetPosition(LOGO_POS);

		// ƒTƒCƒYÝ’è
		m_pScene2D->SetSize(LOGO_SIZE);

		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);

		// ƒeƒNƒXƒ`ƒƒÝ’è
		//if (pPlayer->GetGameClear() == true)
		//{
		//	m_pScene2D->BindTexture("G_RESULT_CLEAR");
		//}
		//else
		//{
		//	m_pScene2D->BindTexture("G_RESULT_GAMEOVER");
		//}
	}

	return S_OK;
}

//==============================================================================
// ƒQ[ƒ€Œ‹‰ÊƒƒS‚ÌI—¹ˆ—
//==============================================================================
void CGamesetLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// ƒQ[ƒ€Œ‹‰ÊƒƒS‚ÌXVˆ—
//==============================================================================
void CGamesetLogo::Update(void)
{

}

//==============================================================================
// ƒQ[ƒ€Œ‹‰ÊƒƒS‚Ì•`‰æˆ—
//==============================================================================
void CGamesetLogo::Draw(void)
{

}

//==============================================================================
// ƒQ[ƒ€Œ‹‰ÊƒƒS‚Ì¶¬ˆ—
//==============================================================================
CGamesetLogo *CGamesetLogo::Create(void)
{
	// ƒCƒ“ƒXƒ^ƒ“ƒX¶¬
	CGamesetLogo *pGamesetLogo;
	pGamesetLogo = new CGamesetLogo;

	// CNumber‚Ì‰Šú‰»
	if (pGamesetLogo != NULL)
	{
		pGamesetLogo->Init();
	}

	return pGamesetLogo;
}