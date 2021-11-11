//*****************************************************************************
//
// �Q�[������ [game.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "game.h"
#include "result.h"

#include "manager.h"
#include "sound.h"
#include "fade.h"
#include "keyinput.h"

#include "player.h"

#include "scene2D.h"

#include "time.h"
#include "move.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame() : CScene(OBJ_NONE)
{
	m_pNote = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// �Q�[���̐���
//=============================================================================
CGame * CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame;
	
	// NULL�`�F�b�N
	if (pGame != NULL)
	{
		// ����������
		pGame->Init();
	}

	return pGame;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(void)
{
	// �T�E���h�N���X�̃|�C���^
	CSound *pSound = CManager::GetSound();

	if (m_pNote == NULL)
	{
		m_pNote = CMesh3D::Create(4, 4, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	// �T�E���h�N���X�̃|�C���^
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̒�~
	pSound->StopSound();

	m_pNote->Uninit();

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[���̓N���X�̃|�C���^
	CKey *pKey = CManager::GetKey();
	// �t�F�[�h���
	CFade::FADE Fade = CFade::GetFade();

	fTime++;

	m_pNote->VtxPos(4, fHeight);

	m_pNote->MeshWave(m_WaveCenter, fTime);

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_NUMPAD8))
	{
		fHeight+=1.5f;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_NUMPAD2))
	{
		fHeight -= 1.5f;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_W))
	{
		m_WaveCenter.z++;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_A))
	{
		m_WaveCenter.x--;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_S))
	{
		m_WaveCenter.z--;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_D))
	{
		m_WaveCenter.x++;
	}

	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_SPACE) && Fade == CFade::FADE_NONE)
	{
		// ���U���g�V�[���Ɉړ�
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	
}
