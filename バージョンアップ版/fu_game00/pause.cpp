//*****************************************************************************
//
// �|�[�Y���� [pause.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "pause.h"
#include "scene2D.h"
#include "renderer.h"
#include "keyinput.h"
#include "manager.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define PAUSE_SIZE		(D3DXVECTOR3(WIDTH_HALF, HEIGHT_HALF, 0.0f))
#define PAUSE_POS		(D3DXVECTOR3(WIDTH_HALF, HEIGHT_HALF, 0.0f))
#define PAUSE_COL		(D3DXCOLOR(0.7f,0.7f,0.7f,0.6f))
#define BUTTON_COL		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define BUTTON_POS		(D3DXVECTOR3(WIDTH_HALF, HEIGHT_HALF-200, 0.0f))
#define BUTTON_SIZE		(D3DXVECTOR3(200.0f, 50.0f, 0.0f))
#define PAUSE_OBJ_NUM	(CPause::MENU_MAX)
#define MENU_SELECTCOL	(D3DXCOLOR(0.4f,0.4f,0.4f,1.0f))

//-----------------------------------------------------------------------------
// �ÓI�ϐ�
//-----------------------------------------------------------------------------
CScene2D *CPause::m_pScene2D = NULL;
CScene2D *CPause::m_pPauseButton[MENU_MAX] = {};
int CPause::m_nMenuID = 0;

//=============================================================================
// �R���X�g���N�^�i�|�[�Y�p�̃I�[�o�[���[�h�j
//=============================================================================
CPause::CPause() : CScene(true)
{
	m_nMenuID = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// �|�[�Y�̐���
//=============================================================================
CPause * CPause::Create(void)
{
	CPause *pPause = NULL;	 // �|�[�Y�̕ϐ��i�|�C���^�j
	
	if (pPause == NULL)
	{// NULL�`�F�b�N
		pPause = new CPause; // �C���X�^���X����
		pPause->Init();		 // ������
	}

	return pPause;			 // ����Ԃ�
}

//=============================================================================
// ������
//=============================================================================
HRESULT CPause::Init(void)
{
	m_col = PAUSE_COL;	 // �F
	m_pos = PAUSE_POS;	 // �ʒu
	m_ButtonPos = BUTTON_POS;
	m_size = PAUSE_SIZE; // �T�C�Y

	// �|�[�YBG�̍쐬
	m_pScene2D = new CScene2D(PAUSE_BG); // �|���S���̍쐬
	m_pScene2D->Init(m_pos, m_size);	 // ����������
	m_pScene2D->SetCol(m_col);			 // �F�̐ݒ�
	m_pScene2D->SetUse(true);
	
	m_pPauseButton[0] = new CScene2D(PAUSE_BUTTON1);
	m_pPauseButton[0]->Init(m_ButtonPos, BUTTON_SIZE);
	m_pPauseButton[0]->SetCol(MENU_SELECTCOL);
	m_pPauseButton[0]->CreateTexture("data/TEXTURE/retry.png");
	m_pPauseButton[0]->SetUse(true);
	m_ButtonPos.y += 150;

	m_pPauseButton[1] = new CScene2D(PAUSE_BUTTON2);
	m_pPauseButton[1]->Init(m_ButtonPos, BUTTON_SIZE);
	m_pPauseButton[1]->SetCol(WhiteColor);
	m_pPauseButton[1]->CreateTexture("data/TEXTURE/quit.png");
	m_pPauseButton[1]->SetUse(true);
	m_ButtonPos.y += 150;

	m_pPauseButton[2] = new CScene2D(PAUSE_BUTTON3);
	m_pPauseButton[2]->Init(m_ButtonPos, BUTTON_SIZE);
	m_pPauseButton[2]->SetCol(WhiteColor);
	m_pPauseButton[2]->CreateTexture("data/TEXTURE/continue.png");
	m_pPauseButton[2]->SetUse(true);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	m_pScene2D->Uninit(true);	// �I�������i�|�[�Y�V�[���̂ݏ����p�j

	for (int nCnt = 0; nCnt < PAUSE_OBJ_NUM; nCnt++)
	{
		m_pPauseButton[nCnt]->Uninit(true);
	}
	//�I�u�W�F�N�g�̔j��
	PauseRelease();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	// �L�[�{�[�h���擾
	CKey *pKey = CManager::GetKey();

	/* �|�[�Y�̐؂�ւ� */
	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_UP) == true)			// �v���X�ED�������ꂽ�Ƃ�
	{
		m_nMenuID -= 1;
		if (m_nMenuID < 0)
		{
			m_nMenuID = 2;
		}

	}
	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_DOWN) == true)			// �v���X�ED�������ꂽ�Ƃ�
	{
		m_nMenuID = (m_nMenuID + 1) % 3;

	}
	SelectMenu(m_nMenuID);

	if (pKey->GetState(CKey::STATE_RELEASE, DIK_SPACE))
	{
		MenuOk(m_nMenuID);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{
	m_pScene2D->Draw();	 // �|���S���̕`��
	for (int nCnt = 0; nCnt < PAUSE_OBJ_NUM; nCnt++)
	{
		m_pPauseButton[nCnt]->Draw();
	}
}

//=============================================================================
// �I�����Ă��郁�j���[�̐F���X�V
//=============================================================================
void CPause::SelectMenu(const int nMenuID)
{
	for (int nCnt = 0; nCnt < PAUSE_OBJ_NUM; nCnt++)
	{
		if (nCnt == nMenuID)
		{
			m_pPauseButton[nCnt]->SetCol(MENU_SELECTCOL);
		}
		else
		{
			m_pPauseButton[nCnt]->SetCol(WhiteColor);
		}
	}
}

void CPause::MenuOk(const int nMenuID)
{
	switch (nMenuID)
	{
	case MENU_RETRY:
		CManager::SetPause(false);
		break;

	case MENU_QUIT:
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		Uninit();
		break;

	case MENU_CONTINUE:
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
		Uninit();
		break;

	default:
		break;
	}
}
