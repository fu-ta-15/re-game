//==============================================================================
//
// ”wŒi•`‰æˆ—kbg.cppl
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "game.h"
#include "bg.h"
#include "texture.h"
#include "result.h"
#include "mode.h"

// Ã“Iƒƒ“ƒo•Ï”éŒ¾
D3DXVECTOR3 CBg::m_pos = SCREEN_CENTER;

//==============================================================================
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//==============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	m_pScene2D = NULL;
}

//==============================================================================
// ƒfƒXƒgƒ‰ƒNƒ^
//==============================================================================
CBg::~CBg()
{
}

//==============================================================================
// ”wŒi‚Ì‰Šú‰»ˆ—
//==============================================================================
HRESULT CBg::Init(void)
{
	// ƒ‚[ƒh‚ÌŽæ“¾
	CMode::MODE mode = CManager::GetModePoint()->GetMode();

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(m_pos);
		m_pScene2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
		
		switch (mode)
		{
		case CMode::MODE_TITLE:
			
			m_pScene2D->BindTexture("TITLE_BG");

			break;

		case CMode::MODE_GAME:

			m_pScene2D->BindTexture("GAME_BG");

			break;

		case CMode::MODE_RESULT:
			m_pScene2D->BindTexture("RESULT_BG");
			break;

		case CMode::MODE_RANKING:
			//switch (CStageSelect::GetSelectingStage())
			//{
			//case CStageSelect::STAGE_SELECT_1:

			//	m_pScene2D->BindTexture("RANKING_VALLEY");

			//	break;

			//case CStageSelect::STAGE_SELECT_2:

			//	m_pScene2D->BindTexture("RANKING_SEA");

			//	break;

			//case CStageSelect::STAGE_SELECT_3:

			//	m_pScene2D->BindTexture("RANKING_LAVA");

			//	break;
			//}
			break;
		}
	}

	return S_OK;
}

//==============================================================================
// ”wŒi‚ÌI—¹ˆ—
//==============================================================================
void CBg::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULLƒ`ƒFƒbƒNŒã‚É”jŠü
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// CBgƒCƒ“ƒXƒ^ƒ“ƒX‚ÌƒfƒŠ[ƒg
}

//==============================================================================
// ”wŒi‚ÌXVˆ—
//==============================================================================
void CBg::Update(void)
{
	// ƒ‚[ƒh‚ÌŽæ“¾
	CMode::MODE mode = CManager::GetModePoint()->GetMode();
}

//==============================================================================
// ”wŒi‚Ì•`‰æˆ—
//==============================================================================
void CBg::Draw(void)
{
	/*CScene‚É‚ÄŽÀs*/
}

//==============================================================================
// ”wŒi‚Ì¶¬ˆ—
//==============================================================================
CBg *CBg::Create(void)
{
	// CBg‚ÌƒCƒ“ƒXƒ^ƒ“ƒX¶¬
	CBg *pBg;
	pBg = new CBg;

	// CBg‚Ì‰Šú‰»
	if (pBg != NULL)
	{
		pBg->Init();
	}

	return pBg;
}