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

#include "enemy.h"
#include "boss.h"
#include "player.h"

#include "scene2D.h"
#include "mesh.h"

#include "time.h"
#include "move.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define PLAYER_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))
#define PLAYER_POS		(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 0.0f))

#define SCORE_POS		(D3DXVECTOR3(100.0f, 100.0f, 0.0f))
#define SCORE_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))

#define FIELD_POS		(D3DXVECTOR3(0.0f, 668.0f, 0.0f))
#define FIELD_SIZE		(D3DXVECTOR3(WIDTH_HALF+100.0f, 100.0f, 0.0f))
#define FIELD_VERTICAL	(100)

#define BG_POS			(CENTER_POS)
#define BG_SIZE			(D3DXVECTOR3(WIDTH_HALF,HEIGHT_HALF,0.0f))

#define BG_TEXTURE		("data/TEXTURE/BG.png")
#define BOSS_TEXTURE	("data/TEXTURE/Boss.png")
#define FIELD_TEXTURE	("data/TEXTURE/Field.png")

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
CPlayer*	CGame::m_pPlayer	= NULL;
CScore*		CGame::m_pScore		= NULL;
CTime*		CGame::m_pTime		= NULL;
CBoss*		CGame::m_pBoss		= NULL;
CScene2D*	CGame::m_pBg		= NULL;
CMesh*		CGame::m_pField		= NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame() : CScene(OBJ_NONE)
{
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

	// �g���N�������߂̃J�E���g
	m_nWaveCnt = 0.0f;

	// �g�̍���
	m_fWaveHeight = 20.0f;

	// �w�i�̐���
	m_pBg = CScene2D::Create(BG_POS, BG_SIZE);

	// �_���[�W�\���p�̃��b�V���|���S������
	m_pLifeMesh = CMesh::Create(100, 0, D3DXVECTOR3(0.0f,HEIGHT_HALF,0.0f), D3DXVECTOR3(SCREEN_WIDTH, 5.0f, 0.0f), CScene::OBJ_NONE2);
	
	// �n�ʂ̐���
	m_pField = CMesh::Create(FIELD_VERTICAL, 0, FIELD_POS, FIELD_SIZE,CScene::OBJ_NONE2);
	
	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);
	
	// �^�C���̐��� *���ŉ񂵂Ă��邽�߃|���S���Ƃ��Ă͕\�����Ȃ�
	m_pTime = CTime::Create(ZeroVector3, ZeroVector3, 0);
	
	// �{�X�̐���
	m_pBoss = CBoss::Create(BOSS_POS, BOSS_SIZE, BOSS_LIFE);

	// �{�X�̃e�N�X�`��
	m_pBoss->CreateTexture(BOSS_TEXTURE);

	// �w�i�̃e�N�X�`��
	m_pBg->CreateTexture(BG_TEXTURE);

	// �n�ʂ̃e�N�X�`��
	m_pField->CreateTexture(FIELD_TEXTURE);

	// �T�E���h�̊J�n
	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

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

	// �v���C���[�����S������
	if (m_pPlayer->GetAlive() == false)
	{
		// ���U���g�Ɍ��ʂ��
		CResult::GameEndResult(false);

		// ���U���g�V�[���Ɉړ�
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

	// �{�X�����S������
	if (m_pBoss->GetAlive() == false)
	{
		// ���U���g�Ɍ��ʂ��
		CResult::GameEndResult(true);

		// ���U���g�V�[���Ɉړ�
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

	// �E�F�[�u�̃J�E���g
	m_nWaveCnt += 0.52f;

	for (int nVtx = 0; nVtx < m_pLifeMesh->GetVtxNum() / 2; nVtx++)
	{
		// ���W�ۊǗp
		D3DXVECTOR3 pos = ZeroVector3;

		// �{�X���_���[�W���󂯂���
		if (m_pBoss->GetState() == CBoss::STATE_NOT_DAMAGE)
		{
			m_fWaveHeight = (float)(rand() % 300 - 200);
			m_nWaveCnt += rand() % 15 + 2;
			pos.y = Move::CosWave(HEIGHT_HALF, m_fWaveHeight, 320.0f, (m_nWaveCnt) + nVtx);
		}
		else
		{
			m_fWaveHeight += (20.0f - m_fWaveHeight) * 0.0025f;
			pos.y = Move::CosWave(HEIGHT_HALF, m_fWaveHeight, 240.0f, (m_nWaveCnt) + nVtx);
		}

		m_pLifeMesh->SetVtxPosY(nVtx, pos.y);
		pos.y += 5;
		m_pLifeMesh->SetVtxPosY(nVtx + (m_pLifeMesh->GetVtxNum() / 2), pos.y);
	}

	/* �^�C�}�[���� */
	if ((m_pTime->AddCnt(1) % 60) == 0)
	{
		m_pTime->AddTime(1);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	
}
