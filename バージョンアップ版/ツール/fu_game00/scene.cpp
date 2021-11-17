//*****************************************************************************
//
// �V�[������ [scene.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
CScene *CScene::m_pTop[OBJ_MAX] = {};		  // �V�[���̐擪
CScene *CScene::m_pCur[OBJ_MAX] = {};		  // �V�[���̍Ō��

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene::CScene(Priority type)
{
	// ���Ԃ̎�ނ��L��
	m_type = type;		 

	// ���S�t���O
	m_bDeath = false;	 

	// �擪�ɏ�񂪓����Ă�����
	if (m_pTop[m_type] != NULL)
	{
		// �擪������̂ŁA�Ō������ǉ�����B
		m_pCur[m_type]->m_pNext = this; 

		// ���g�̎���NULL�ł���B
		this->m_pNext = NULL;			

		// ���g�̑O�͍��̍Ō���ł���B
		this->m_pPrev = m_pCur[m_type];	
	}
	else // �擪�ɏ�񂪓����Ă��Ȃ�������
	{
		// ���Ȃ��͐擪�ł��B
		m_pTop[m_type] = this;

		// ����NULL
		this->m_pNext = NULL;		

		// �O��NULL
		this->m_pPrev = NULL;			
	}

	// ���g���Ō��
	m_pCur[m_type] = this;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// ���ׂĂ̏I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		// �|�C���^�ɐ擪�̏�������
		CScene *pScene = m_pTop[nCntType];

		while (pScene)
		{
			// ���̃V�[����ۑ�
			CScene *pSceneNext = pScene->m_pNext;

			// �V�[���̍폜
			pScene->Uninit();

			// NULL����
			pScene = NULL;

			// ���̃V�[�����擾
			pScene = pSceneNext;
		}
	}
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// �|�C���^�ɐ擪�̏�������
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// ���̃V�[����ۑ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������Ă�����
				if (pScene->m_bDeath == true)
				{
					// ���S�t���O�������Ă���̂Ń��X�g����폜
					pScene->DeathRelease();

					// �V�[����NULL
					pScene = NULL;
				}

				// ���̃V�[�����擾
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// ���ׂĂ̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// �|�C���^�ɐ擪�̏�������
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// ���̃V�[����ۑ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������Ă��Ȃ�������
				if (pScene->m_bDeath != true)
				{
					// �X�V����
					pScene->Update();
				}

				// ���̃V�[�����擾
				pScene = pSceneNext;
			}
		}
	}

	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// �|�C���^�ɐ擪�̏�������
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// ���̃V�[����ۑ�
				CScene *pSceneNext = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// ���S�t���O�������Ă���V�[�������X�g����폜
					pScene->DeathRelease();

					// NULL����
					pScene = NULL;
				}

				// ���̃V�[�����擾
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// ���ׂĂ̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	CManager::GetCamera()->SetCamera();

	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] != NULL)
		{
			// �|�C���^�ɐ擪�̏�������
			CScene *pScene = m_pTop[nCntType];

			while (pScene != NULL)
			{
				// ���̃V�[����ۑ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������Ă��Ȃ�������
				if (pScene->m_bDeath != true)
				{
					// �X�V����
					pScene->Draw();
				}

				// ���̃V�[�����擾
				pScene = pSceneNext;
			}
		}
	}

}

//=============================================================================
// �V�[���̍폜����
//=============================================================================
void CScene::Release(void)
{
	// ���S�t���O�𗧂Ă�
	m_bDeath = true;
}

//=============================================================================
// ���S�t���O�������Ă���V�[���̍폜
//=============================================================================
void CScene::DeathRelease(void)
{
	for (int nCntType = 0; nCntType < OBJ_MAX; nCntType++)
	{
		if (m_pTop[nCntType] == this)
		{
			// ���g���擪�������玟�̃V�[����擪�ɂ���
			m_pTop[nCntType] = this->m_pNext;
		}

		if (m_pCur[nCntType] == this)
		{
			// ���g���Ō����������O�̃V�[�����Ō���ɂ���
			m_pCur[nCntType] = this->m_pPrev;
		}

		if (this->m_pPrev != NULL)
		{
			// ���g�̃��X�g�Ɏ��̃V�[��������
			this->m_pPrev->m_pNext = this->m_pNext;
		}

		if (this->m_pNext != NULL)
		{
			// ���g�̃��X�g�ɑO�̃V�[��������
			this->m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	// ���g���폜
	delete this;
}

//=============================================================================
// this��Next�V�[���̎擾
//=============================================================================
CScene * CScene::GetSceneNext(void)
{
	// �V�[���̃|�C���^
	CScene *pSceneNext;

	// ���ɏ�񂪂����
	if (this->m_pNext != NULL)
	{
		// ���擾
		pSceneNext = this->m_pNext;
	}
	else
	{
		// NULL����
		pSceneNext = NULL;
	}

	return pSceneNext;
}
