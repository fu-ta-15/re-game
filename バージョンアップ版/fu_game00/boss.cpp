//*****************************************************************************
//
// �{�X�G���� [boss.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "boss.h"
#include "normalenemy.h"
#include "manager.h"
#include "renderer.h"
#include "move.h"
#include "collision.h"
#include "enemy.h"
#include "time.h"
#include "game.h"
#include "bulletmesh.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define EFFECT_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))				// �G�t�F�N�g�̏����F
#define LIFE_POS_X		(SCREEN_WIDTH - 100.0f)							// ���C�t��X���W
#define LIFE_POS_Y		(200.0f - (10 * nCntLife))						// ���C�t��Y���W
#define LIFE_POS		(D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f))		// ���C�t�̈ʒu
#define LIFE_SIZE		(D3DXVECTOR3(10.0f, 5.0f, 0.0f))				// ���C�t�̃T�C�Y
#define LIFE_DOWN		((m_fLife * 0.17f + 0.025f))					// ���C�t�̌����v�Z
#define LIFE_CNT		(nCntLife * 10)									// ���C�t�J�E���g
#define DAMAGE_TEXTUER	("data/TEXTURE/stateBoss.png")					// �_���[�W��ԃe�N�X�`�������N
#define SHILED_TEXTUER	("data/TEXTURE/AuroraRing.png")					// �o���A�e�N�X�`�������N
#define LIFE_TEXTURE	("data/TEXTURE/BossLife.png")					// ���C�t�e�N�X�`�������N

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
bool CBoss::m_bBoss_Alive = true;	  // �{�X�̐����m�F

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoss::CBoss() : CEnemy(OBJ_BOSS)
{
	this->m_pDamage = NULL;				// �_���[�W�G�t�F�N�g
	this->m_bDamage = false;			// �_���[�W�󂯂Ă��邩���Ȃ���
	this->m_State = STATE_NONE;			// ���
	this->m_LifeState = LIFE_RATE_0;	// ���C�t�̏��
	this->m_move = ZeroVector3;			// �ړ��ʏ�����
	this->m_bBoss_Alive = true;			// ��������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoss::~CBoss()
{
}

//=============================================================================
// �{�X�̐���
//=============================================================================
CBoss * CBoss::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nLife)
{
	CBoss *pBoss = new CBoss;

	// NULL�`�F�b�N
	if (pBoss != NULL)
	{
		pBoss->SetPos(pos);				// �ʒu
		pBoss->SetSize(size);			// �T�C�Y
		pBoss->m_fLife = (float)nLife;	// ���C�t
		pBoss->SetCol(WhiteColor);		// �F
		pBoss->SetType(ENEMY_BOSS);		// �^�C�v
		pBoss->Init();					// ������
	}

	return pBoss;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBoss::Init(void)
{	
	// ������
	CEnemy::Init();

	// �_���[�W�J�E���g
	m_nDamageCnt = 0;	 

	// �ړ��p�J�E���g
	m_fMoveTime = 0.0f;	 

	// ���C�t�̐���
	for (int nCntLife = 0; nCntLife < BOSS_LIFE_STOCK; nCntLife++)
	{
		D3DXVECTOR3 pos = LIFE_POS;						 // �ʒu
		D3DXVECTOR3 size = LIFE_SIZE;					 // �T�C�Y
		m_pLife[nCntLife] = CScene2D::Create(pos, size); // ����
		m_pLife[nCntLife]->CreateTexture(LIFE_TEXTURE);	 // �e�N�X�`���̐ݒ�
	}

	// �_���[�W�p�G�t�F�N�g�̐���
	m_pDamage = CEffect::Create(m_pos, m_size);	   // ����
	m_pDamage->CreateTexture(DAMAGE_TEXTUER);	   // �e�N�X�`���̐ݒ�
	m_pDamage->SetColor(EFFECT_COLOR);			   // �F�̐ݒ�
	m_StateCol = m_pDamage->GetColor();			   // �F�̎擾


	// �R�A�̐���
	m_pCore[0] = CCore::Create(m_pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), 0, OBJ_CORE);
	m_pCore[1] = CCore::Create(m_pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), 50, OBJ_CORE);
	m_pCore[2] = CCore::Create(m_pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), 100, OBJ_CORE);

	// �V�[���h�̐���
	m_pShiled = CScene2D::Create(m_pos, m_size * 1.5f);
	m_pShiled->CreateTexture("data/TEXTURE/t0003.png");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBoss::Uninit(void)
{
	// �R�A�̊J��
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pCore[nCnt] != NULL)
		{
			// �I������
			m_pCore[nCnt]->Uninit();

			// NULL����
			m_pCore[nCnt] = NULL;
		}
	}

	// �V�[���h�̊J��
	if (m_pShiled != NULL)
	{
		// �I������
		m_pShiled->Uninit();

		// NULL����
		m_pShiled = NULL;
	}

	// ���g�̊J��
	CEnemy::Uninit();	
}

//=============================================================================
// �X�V����
//=============================================================================
void CBoss::Update(void)
{
	// ���b�V���|���S���̏��擾
	switch (CManager::GetMode())
	{
		// �Q�[�����[�h
	case CManager::MODE_GAME:

		// �X�V
		CEnemy::Update();

		// �_���[�W��ԍX�V
		DamageBoss();

		// ��Ԃ̍X�V
		StateUpdate();

		// �ړ�����
		MoveBoss();

		// �G��������
		SummonsEnemy();

		break;

	default:
		break;
	}

	// �ʒu�̍X�V
	m_pShiled->SetPos(m_pos); 	

	// �ʒu�̍X�V
	CScene2D::SetPos(m_pos);

	// �T�C�Y�̍X�V
	CScene2D::SetSize(m_size);	

	// ���C�t���[��
	if (m_fLife <= 0)
	{
		// �{�X�̐�����false
		m_bBoss_Alive = false;

		// ���g�̊J��
		CEnemy::Uninit();	
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBoss::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �_���[�W���󂯂���
//=============================================================================
void CBoss::DamageBoss(void)
{
	// �_���[�W���󂯂���
	if (m_State == STATE_DAMAGE)
	{
		// �_���[�W���}
		m_bDamage = true;

		// �̗͂̌���
		m_fLife -= LIFE_DOWN;

		// ���݂̗̑͏��
		m_LifeState = LifeState((int)m_fLife);

		// �����x���Z�p
		m_fA_Damage = 0.065f;

		// �_���[�W������Ԃɂ���
		m_State = STATE_NOT_DAMAGE;
	}
}

//=============================================================================
// ��ԊǗ�
//=============================================================================
void CBoss::StateUpdate(void)
{
	// �_���[�W���󂯂Ă�����
	if (m_State == STATE_NOT_DAMAGE)
	{
		// �J���[�̍X�V
		m_pDamage->SetColor(m_StateCol);

		// �ʒu���X�V
		m_pDamage->SetPos(m_pos);

		// ���l�̉��Z
		m_StateCol.a += m_fA_Damage;

		// ���l�������z������
		if (m_StateCol.a > 1.0f)
		{
			// ���Z�̐��l���}�C�i�X��
			m_fA_Damage = -0.004f;
		}
		else if (m_StateCol.a < 0.0f)
		{
			// FALSE���
			m_bDamage = false;

			// ��Ԃ�߂�
			m_State = STATE_NONE;
		}
	}
}

//=============================================================================
// ���C�t�̏�ԊǗ�
//=============================================================================
CBoss::LIFE_STATE CBoss::LifeState(int nLife)
{
	// ���C�t�u���b�N�̍X�V
	for (int nCntLife = 0; nCntLife < BOSS_LIFE_STOCK; nCntLife++)
	{
		// ���C�t����؂�̒l���z������
		if (m_fLife < LIFE_CNT)
		{
			// �c��̗�
			switch (nCntLife)
			{
				// HP�P�Q
			case 12:

				// �Q������
				if (m_LifeState == LIFE_RATE_0){ m_LifeState = LIFE_RATE_2; }
				break;

				// HP�V
			case 7:

				// �T������
				if (m_LifeState == LIFE_RATE_2) { m_LifeState = LIFE_RATE_5; }
				break;

				// HP�Q
			case 2:

				// �W������
				if (m_LifeState == LIFE_RATE_5) { m_LifeState = LIFE_RATE_8; }
				break;

			default:
				break;
			}

			// NULL�`�F�b�N
			if (m_pLife[nCntLife] != NULL)
			{
				// ���C�t�̃u���b�N�폜
				m_pLife[nCntLife]->Uninit(); 

				// NULL���
				m_pLife[nCntLife] = NULL;	  
			}

			// �R�A�̕���
			for (int nCnt = 0; nCnt < 3; nCnt++)
			{
				// �R�A�̕`��J�n
				m_pCore[nCnt]->SetUse(true);
			}
		}
	}

	return m_LifeState;
}

//=============================================================================
// �ړ�����
//=============================================================================
void CBoss::MoveBoss(void)
{
	// �J�E���g���Z
	m_fMoveTime += 0.5f;

	// ���C�t�̏�Ԃňړ��ύX
	switch (m_LifeState)
	{
		// �O������
	case LIFE_RATE_0:

		// Cos�g�̈ړ�
		m_pos.y = Move::CosWave(HEIGHT_HALF,100.0f, 65.5f, m_fMoveTime);

		// ���݂̈ʒu��ۑ�
		m_OldPos = m_pos;
		break;

		// �Q������
	case LIFE_RATE_2:

		// Cos�g�̈ړ�
		m_pos.y = Move::CosWave(m_OldPos.y,60.0f, 100.5f, m_fMoveTime);

		// Sin�g�̉��Z�ړ�
		m_pos.x = Move::SinWave(m_OldPos.x, 60.0f, 100.5f,m_fMoveTime);
		break;

		// �T������
	case LIFE_RATE_5:

		// �w��̈ʒu�܂ňړ�
		m_pos = Move::TargetPosMove(D3DXVECTOR3(SCREEN_WIDTH - 150.0f , HEIGHT_HALF + 100.0f, 0.0f), m_pos, 0.025f);
		break;

		// �W������
	case LIFE_RATE_8:

		// �w��̈ʒu�܂ňړ�
		m_pos = Move::TargetPosMove(D3DXVECTOR3(WIDTH_HALF + 300.0f, HEIGHT_HALF - 50.0f, 0.0f), m_pos, 0.0025f);
		break;

	default:
		break;
	}
	// �ʒu�̍X�V
	CScene2D::SetPos(m_pos);
}

//=============================================================================
// �G�̏���
//=============================================================================
void CBoss::SummonsEnemy(void)
{
	// �ʒu�̎擾
	m_pos = CScene2D::GetPos();		

	// ���Ԃ̎擾
	int nFrame = CGame::GetTime()->GetFrame();	

	// �̗͂̏�ԂœG�̏������@�ύX
	switch (m_LifeState)
	{
		// �O������
	case LIFE_RATE_0:
		if ((nFrame % 15) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE3, 1);
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE2, 10);
		}
		break;

		// �Q������
	case LIFE_RATE_2:
		if ((nFrame % 60) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE3, 1);
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE2, 25);
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE0, 1);
		}
		break;

		// �T������
	case LIFE_RATE_5:
		if ((nFrame % 20) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE0, 1);
		}
		if ((nFrame % 10) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE3, 1);
		}
		break;

		// �W������
	case LIFE_RATE_8:
		if ((nFrame % 7) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE0, 1);
		}
		if ((nFrame % 5) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE3, 1);
		}
		if ((nFrame % 30) == 0)
		{
			ENEMY::SetEnemy(m_pos, ENEMY_SIZE, ENEMY_TYPE0, MOVE2, 10);
		}
		if ((nFrame % 100) == 0)
		{
			if (m_pCore[0]->GetUse() == true)
			{
				ENEMY::SetEnemy(m_pCore[0]->GetPos(), ENEMY_SIZE, ENEMY_TYPE0, MOVE2, 10);
			}
			if (m_pCore[1]->GetUse() == true)
			{
				ENEMY::SetEnemy(m_pCore[1]->GetPos(), ENEMY_SIZE, ENEMY_TYPE0, MOVE2, 10);
			}
		}
		break;

	default:
		break;
	}
}
