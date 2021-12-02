//*****************************************************************************
//
// �`���[�g���A������ [tutorial.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "tutorial.h"
#include "keyinput.h"
#include "manager.h"
#include "fade.h"
#include "scene2D.h"
#include "player.h"
#include "mesh.h"
#include "sound.h"
#include "boss.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define PLAYER_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))
#define PLAYER_POS		(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 0.0f))

#define BG_SIZE			(D3DXVECTOR3(WIDTH_HALF,HEIGHT_HALF,0.0f))

#define FIELD_POS		(D3DXVECTOR3(0.0f, 668.0f, 0.0f))
#define FIELD_SIZE		(D3DXVECTOR3(WIDTH_HALF+100.0f, 100.0f, 0.0f))
#define FIELD_VERTICAL	(40)
#define FIELD_SIDE		(0)

#define OPE_POS			(D3DXVECTOR3((100.0f+(150.0f*nCnt)), 100.0f, 0.0f))
#define OPE_SIZE		(D3DXVECTOR3(70.0f, 70.0f, 0.0f))
#define OPE_VERTICAL	(30)
#define OPE_SIDE		(0)

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
CPlayer*	CTutorial::m_pPlayer = NULL;
CScene2D*	CTutorial::m_pBg = NULL;
CMesh*		CTutorial::m_pField = NULL;
CBoss*		CTutorial::m_pBoss = NULL;
CMesh*		CTutorial::m_pOperation[OPERA_MAX] = {};
bool		CTutorial::m_OperationStop = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial() : CScene(OBJ_NONE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// �`���[�g���A���̐���
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	// �������m��
	CTutorial* pTutorial = new CTutorial();

	// ����������
	pTutorial->Init();

	return pTutorial;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CSound *pSound = CManager::GetSound();

	//m_pBg = CScene2D::Create(CENTER_POS, BG_SIZE);													// �w�i
	//m_pField = CMesh::Create(FIELD_VERTICAL, FIELD_SIDE, FIELD_POS, FIELD_SIZE,CScene::OBJ_NONE);	// �n��
	//m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);											// �v���C���[
	//m_pBoss = CBoss::Create(BOSS_POS, BOSS_SIZE, BOSS_LIFE);										// �{�X

	//for (int nCnt = 0; nCnt < OPERA_MAX; nCnt++)
	//{// ��������摜
	//	D3DXVECTOR3 pos = D3DXVECTOR3((100.0f + (150.0f*nCnt)), 100.0f, 0.0f);						// �ʒu�̍X�V
	//	m_pOperation[nCnt] = CMesh::Create(OPE_VERTICAL, OPE_SIDE, pos, OPE_SIZE,CScene::OBJ_NONE); // �|���S���̐���
	//	m_bButton[nCnt] = false;																	// �E�F�[�u�̗L��
	//}

	//// �摜�̓\��t��
	//m_pBoss->CreateTexture("data/TEXTURE/Boss_tutorial.png");
	//m_pBg->CreateTexture("data/TEXTURE/BG.png");
	//m_pField->CreateTexture("data/TEXTURE/Field.png");
	//m_pOperation[KEY_A]->CreateTexture("data/TEXTURE/Move_a.png");
	//m_pOperation[KEY_D]->CreateTexture("data/TEXTURE/Move_d.png");
	//m_pOperation[KEY_W]->CreateTexture("data/TEXTURE/Move_w.png");
	//m_pOperation[KEY_NUM_6]->CreateTexture("data/TEXTURE/Bullet_6.png");

	// �T�E���h�̊J�n
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// �T�E���h�̒�~
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CKey *pKey = CManager::GetKey();	   // �L�[���
	CFade::FADE Fade = CFade::GetFade();   // �t�F�[�h���


	if (pKey->GetState(CKey::STATE_RELEASE, DIK_SPACE) && Fade == CFade::FADE_NONE)
	{// RETURN�L�[�������ꂽ��
		CManager::GetFade()->SetFade(CManager::MODE_GAME);	// GAME�EMODE��
	}
	// ���߂ĉ����ꂽ�L�[�̊m�F
	//OnKeyOperat(pKey);
	//OperatUpdate();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
// ���̃L�[�����߂ĉ����ꂽ�烁�b�V����h�炷���߂̊m�F
//=============================================================================
void CTutorial::OnKeyOperat(CKey *pKey)
{// ���̃L�[�������ꂽ��AMOVE�I���ɂ���
	//if (pKey->GetState(CKey::STATE_TRIGGER, DIK_A))			{ m_bButton[KEY_A] = true; }
	//if (pKey->GetState(CKey::STATE_TRIGGER, DIK_D))			{ m_bButton[KEY_D] = true; }
	//if (pKey->GetState(CKey::STATE_TRIGGER, DIK_W))			{ m_bButton[KEY_W] = true; }
	//if (pKey->GetState(CKey::STATE_TRIGGER, DIK_NUMPAD6))	{ m_bButton[KEY_NUM_6] = true; }
}

//=============================================================================
// �����p�摜�̍X�V
//=============================================================================
void CTutorial::OperatUpdate(void)
{
	//// �J�E���g�����Z
	//m_nCntTimeOP++;

	//for (int nCnt = 0; nCnt < OPERA_MAX; nCnt++)
	//{
	//	if (m_bButton[nCnt] == true)
	//	{// ���̃L�[�������ꂽ���Ƃ��킩���Ă�����
	//		for (int nVtx = 0; nVtx < m_pOperation[nCnt]->GetVtxNum()/2; nVtx++)
	//		{// �g���N��������
	//			D3DXVECTOR3 pos = ZeroVector3;
	//			pos.y = Move::SinWave(100.0f, 10.0f, 60.0f, (float)m_nCntTimeOP + nVtx);
	//			m_pOperation[nCnt]->SetVtxPosY(nVtx, pos.y);
	//			pos.y += 70.0f;
	//			m_pOperation[nCnt]->SetVtxPosY(nVtx + (m_pOperation[nCnt]->GetVtxNum() / 2), pos.y);
	//		}
	//	}
	//}
}
