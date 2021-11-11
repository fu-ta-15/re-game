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
#include "sound.h"

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
	OnKeyOperat(pKey);
	OperatUpdate();
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
	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_A))			{ m_bButton[KEY_A] = true; }
	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_D))			{ m_bButton[KEY_D] = true; }
	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_W))			{ m_bButton[KEY_W] = true; }
	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_NUMPAD6))	{ m_bButton[KEY_NUM_6] = true; }
}

//=============================================================================
// �����p�摜�̍X�V
//=============================================================================
void CTutorial::OperatUpdate(void)
{
}
