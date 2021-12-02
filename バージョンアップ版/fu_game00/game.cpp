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
#include "mesh3D.h"

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
CMesh*		CGame::m_pField		= NULL;
CMesh3D*	CGame::m_pBg3D		= NULL;

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
	m_nWaveCnt = 0;

	// 3D�w�i�̐���
	m_pBg3D = CMesh3D::Create(40, 40, D3DXVECTOR3(-40.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 0.0f, 200.0f));

	// 3D�w�i�̃e�N�X�`���ݒ�
	m_pBg3D->CreateTexture("data/TEXTURE/BG.jpg");
	
	// �n�ʂ̐���
	m_pField = CMesh::Create(FIELD_VERTICAL, 0, FIELD_POS, FIELD_SIZE,CScene::OBJ_NONE2);

	// �n�ʂ̃e�N�X�`��
	m_pField->CreateTexture(FIELD_TEXTURE);
	
	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);
	
	// �^�C���̐��� *���ŉ񂵂Ă��邽�߃|���S���Ƃ��Ă͕\�����Ȃ�
	m_pTime = CTime::Create(ZeroVector3, ZeroVector3, 0);
	
	// �{�X�̐���
	m_pBoss = CBoss::Create(BOSS_POS, BOSS_SIZE, BOSS_LIFE);

	// �{�X�̃e�N�X�`��
	m_pBoss->CreateTexture(BOSS_TEXTURE);

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

	// �g�̕\��
	m_pBg3D->MeshWave(D3DXVECTOR3(180.0f,0.0f,100.0f), (int)m_nWaveCnt, 10, 30);

	// �E�F�[�u�̃J�E���g
	m_nWaveCnt++;

	// ���Ԃ̃J�E���g�A�b�v
	if ((m_pTime->AddCnt(1) % 60) == 0) { m_pTime->AddTime(1); }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	
}
