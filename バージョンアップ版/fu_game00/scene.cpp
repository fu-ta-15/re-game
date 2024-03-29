//*****************************************************************************
//
// シーン処理 [scene.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
CScene *CScene::m_pPauseScene = NULL;		  // ポーズポインタ
CScene *CScene::m_pPauseObj[PAUSE_MAX] = {};  // ポーズオブジェクトのポインタ
CScene *CScene::m_pTop[OBJ_MAX] = {};		  // シーンの先頭
CScene *CScene::m_pCur[OBJ_MAX] = {};		  // シーンの最後尾

//=============================================================================
// オブジェクトのコンストラクタ
//=============================================================================
CScene::CScene(Priority type)
{
	// 順番の種類を記憶
	m_type = type;		 

	// 死亡フラグ
	m_bDeath = false;	 

	// 先頭に情報が入っていたら
	if (m_pTop[m_type] != NULL)
	{
		// 先頭がいるので、最後尾から追加する。
		m_pCur[m_type]->m_pNext = this; 

		// 自身の次はNULLである。
		this->m_pNext = NULL;			

		// 自身の前は今の最後尾である。
		this->m_pPrev = m_pCur[m_type];	
	}
	else // 先頭に情報が入っていなかったら
	{
		// あなたは先頭です。
		m_pTop[m_type] = this;

		// 次はNULL
		this->m_pNext = NULL;		

		// 前はNULL
		this->m_pPrev = NULL;			
	}

	// 自身を最後尾
	m_pCur[m_type] = this;
}

//=============================================================================
// ポーズオブジェクトのコンストラクタ
//=============================================================================
CScene::CScene(PauseType type)
{
	// NULLチェック
	if (m_pPauseObj[type] == NULL)
	{
		// ポーズシーンに情報を入れる
		m_pPauseObj[type] = this;
	}
}

//=============================================================================
// ポーズ合図用のコンストラクタ
//=============================================================================
CScene::CScene(bool bpause)
{
	// ポーズされていなかったら・NULLチェック
	if (bpause == true && m_pPauseScene == NULL)
	{
		// ポーズを行う合図
		m_pPauseScene = this;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// すべての終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		// ポインタに先頭の情報を入れる
		CScene *pScene = m_pTop[nCntType];

		while (pScene)
		{
			// 次のシーンを保存
			CScene *pSceneNext = pScene->m_pNext;

			// シーンの削除
			pScene->Uninit();

			// NULLを代入
			pScene = NULL;

			// 次のシーンを取得
			pScene = pSceneNext;
		}
	}
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// ポインタに先頭の情報を入れる
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// 次のシーンを保存
				CScene *pSceneNext = pScene->m_pNext;

				// 死亡フラグを持っていたら
				if (pScene->m_bDeath == true)
				{
					// 死亡フラグが立っているのでリストから削除
					pScene->DeathRelease();

					// シーンをNULL
					pScene = NULL;
				}

				// 次のシーンを取得
				pScene = pSceneNext;
			}
		}
	}

	// ポーズされていたら
	if (m_pPauseScene != NULL)
	{
		for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
		{
			if (m_pPauseObj[nCntPause] != NULL)
			{
				// ポーズのシーンを削除
				m_pPauseObj[nCntPause]->Uninit();
			}
		}
	}
}

//=============================================================================
// すべての更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	// ポーズ中じゃなかったら
	if (m_pPauseScene == NULL)
	{
		for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
		{
			if (m_pTop[nCntType] != NULL)
			{
				// ポインタに先頭の情報を入れる
				CScene *pScene = m_pTop[nCntType];

				while (pScene != NULL) 
				{
					// 次のシーンを保存
					CScene *pSceneNext = pScene->m_pNext;

					// 死亡フラグを持っていなかったら
					if (pScene->m_bDeath != true)
					{
						// 更新処理
						pScene->Update();
					}

					// 次のシーンを取得
					pScene = pSceneNext;
				}
			}
		}
	}

	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// ポインタに先頭の情報を入れる
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// 次のシーンを保存
				CScene *pSceneNext = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// 死亡フラグが立っているシーンをリストから削除
					pScene->DeathRelease();

					// NULLを代入
					pScene = NULL;
				}

				// 次のシーンを取得
				pScene = pSceneNext;
			}
		}
	}

	// ポーズ中だったら
	if (m_pPauseScene != NULL)
	{
		// ポーズの更新
		m_pPauseScene->Update();

		for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
		{
			if (m_pPauseObj[nCntPause] != NULL)
			{
				// ポーズシーンの更新
				m_pPauseObj[nCntPause]->Update();
			}
		}
	}
}

//=============================================================================
// すべての描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	CManager::GetCamera()->SetCamera();

	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// ポインタに先頭の情報を入れる
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// 次のシーンを保存
				CScene *pSceneNext = pScene->m_pNext;

				// 死亡フラグを持っていなかったら
				if (pScene->m_bDeath != true)
				{
					// 更新処理
					pScene->Draw();
				}

				// 次のシーンを取得
				pScene = pSceneNext;
			}
		}
	}

	// ポーズ中だったら
	if (m_pPauseScene != NULL)
	{
		for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
		{
			if (m_pPauseObj[nCntPause] != NULL)
			{
				// ポーズシーンの描画
				m_pPauseObj[nCntPause]->Draw();
			}
		}
	}
}

//=============================================================================
// シーンの削除処理
//=============================================================================
void CScene::Release(void)
{
	// 死亡フラグを立てる
	m_bDeath = true;
}

//=============================================================================
// 死亡フラグが立っているシーンの削除
//=============================================================================
void CScene::DeathRelease(void)
{
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] == this)
		{
			// 自身が先頭だったら次のシーンを先頭にする
			m_pTop[nCntType] = this->m_pNext;
		}

		if (m_pCur[nCntType] == this)
		{
			// 自身が最後尾だったら前のシーンを最後尾にする
			m_pCur[nCntType] = this->m_pPrev;
		}

		if (this->m_pPrev != NULL)
		{
			// 自身のリストに次のシーンを入れる
			this->m_pPrev->m_pNext = this->m_pNext;
		}

		if (this->m_pNext != NULL)
		{
			// 自身のリストに前のシーンを入れる
			this->m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	// 自身を削除
	delete this;
}

//=============================================================================
// ポーズの削除
//=============================================================================
void CScene::PauseRelease(void)
{
	if (m_pPauseScene != NULL)
	{
		for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
		{
			if (m_pPauseObj[nCntPause] != NULL)
			{
				// ポーズシーンを削除
				delete m_pPauseObj[nCntPause];

				// NULLを代入
				m_pPauseObj[nCntPause] = NULL;
			}
		}
		// ポーズを削除
		delete m_pPauseScene;

		// NULLを代入
		m_pPauseScene = NULL;
	}
}

//=============================================================================
// thisのNextシーンの取得
//=============================================================================
CScene * CScene::GetSceneNext(void)
{
	// シーンのポインタ
	CScene *pSceneNext;

	// 次に情報があれば
	if (this->m_pNext != NULL)
	{
		// 情報取得
		pSceneNext = this->m_pNext;
	}
	else
	{
		// NULLを代入
		pSceneNext = NULL;
	}

	return pSceneNext;
}
