//==============================================================================
//
// キャラクター描画処理〔chara.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "sign.h"
#include "chara.h"
#include "input.h"
#include "game.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CChara::CChara(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CChara::~CChara()
{
}

//==============================================================================
// キャラクターの初期化処理
//==============================================================================
HRESULT CChara::Init(void)
{
	// 初期化
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = CScene2D::Create();
			
			m_apScene2D[nCnt]->SetSize(CHARA_SIZE);
			m_apScene2D[nCnt]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);

			// 左右差
			if (nCnt == 0)
			{// 左
				m_apScene2D[nCnt]->SetPosition(CHARA_POS_LEFT);
				m_apScene2D[nCnt]->BindTexture("CHARACTER_LEFT");
			}
			else
			{// 右
				m_apScene2D[nCnt]->SetPosition(CHARA_POS_RIGHT);
				m_apScene2D[nCnt]->BindTexture("CHARACTER_RIGHT");
			}
		}
	}


	return S_OK;
}

//==============================================================================
// キャラクターの終了処理
//==============================================================================
void CChara::Uninit(void)
{
	// ポリゴンの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================================================
// キャラクターの更新処理
//==============================================================================
void CChara::Update(void)
{
	GameEnd();
}

//==============================================================================
// キャラクターの描画処理
//==============================================================================
void CChara::Draw(void)
{

}

//==============================================================================
// キャラクターの生成処理
//==============================================================================
CChara *CChara::Create(void)
{
	// インスタンス生成
	CChara *pChara;
	pChara = new CChara;

	// 初期化
	if (pChara != NULL)
	{
		pChara->Init();
	}

	return pChara;
}

//==============================================================================
// サインの挙動
//==============================================================================
void CChara::CharaMove(void)
{
	// 移動
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		D3DXVECTOR2 size = m_apScene2D[nCnt]->GetSize();	// サイズの取得
		D3DXVECTOR3 pos = m_apScene2D[nCnt]->GetPosition();	// 位置の取得

		size += D3DXVECTOR2(0.5f, 1.0f);

		if (nCnt == 0)
		{
			pos.x -= 1.0f;
			pos.y += 0.5f;
		}
		else
		{
			pos.x += 1.0f;
			pos.y += 0.5f;
		}
		
		m_apScene2D[nCnt]->SetSize(size);
		m_apScene2D[nCnt]->SetPosition(pos);
	}
}

// ゲームエンド
void CChara::GameEnd(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 posLeft = m_apScene2D[0]->GetPosition();
	D3DXVECTOR3 posRight = m_apScene2D[1]->GetPosition();

	// 負けが落ちる
	switch (CGame::GetMatch())
	{
	case CGame::MATCH_LEFT:

		if (m_bFallSide == true)
		{
			posRight.x += 2.0f;
		}
		else
		{
			posRight.x -= 2.0f;
		}

		posRight.y += 1.0f;

		m_apScene2D[1]->SetPosition(posRight);

		break;

	case CGame::MATCH_RIGHT:

		if (m_bFallSide == true)
		{
			posLeft.x += 2.0f;
		}
		else
		{
			posLeft.x -= 2.0f;
		}

		posLeft.y += 1.0f;

		m_apScene2D[0]->SetPosition(posLeft);

		break;
	}

	m_bFallSide = !m_bFallSide;
}