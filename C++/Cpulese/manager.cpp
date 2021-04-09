//##################################################################################################################################################################//
//
// メイン処理 [main.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
//　インクルードファイル
//=====================================================================================================================================================================//
#include "manager.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer = nullptr;

CManager::CManager()
{
}

CManager::~CManager()
{
}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pRenderer = new CRenderer;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}


	return S_OK;
}

void CManager::Uninit(void)
{
	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの終了処理呼び出し
		m_pRenderer->Uninit();

		//メモリの削除
		delete m_pRenderer;

		//メモリのクリア
		m_pRenderer = nullptr;
	}
}

void CManager::Update(void)
{
	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの更新処理呼び出し
		m_pRenderer->Update();
	}
}

void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの描画処理呼び出し
		m_pRenderer->Draw();
	}
}

CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}
