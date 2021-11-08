//*****************************************************************************
//
// �G���� [enemy.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "game.h"
#include "enemy.h"
#include "normalenemy.h"
#include "boss.h"
#include "player.h"
#include "collision.h"
#include "mesh.h"
#include "particle.h"


//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define BOSS_DAMAGE					(CBoss::STATE_DAMAGE)
#define BOSS_NOT_DAMAGE				(CBoss::STATE_NOT_DAMAGE)
#define BOSS_NONE					(CBoss::STATE_NONE)
#define BOSS_GET_LIFE				(CGame::GetBoss()->GetLife())
#define ENEMY_ID					(m_paEnemy[nID])
#define ENEMY_CNT					(m_paEnemy[nCnt])

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(Priority type) : CScene2D(type)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init(m_pos, m_size);	// �|���S���̐���
	CScene2D::SetSize(m_size);		// �T�C�Y�̐ݒ�
	CScene2D::SetCol(m_col);		// �F�̐ݒ�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();	// �I������
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	if (this->CollisionPlayer() == true && CGame::GetPlayer()->GetState() != CPlayer::STATE_KNOCKUP)
	{// �v���C���[�Ƃ̓����蔻��
		switch (this->m_type)
		{
		case ENEMY_BLACK:
			CGame::GetPlayer()->SetCollEnemy(true);
			this->Release();
			break;

		case ENEMY_WHITE:
			this->Release();
			break;

		default:
			break;
		}
	}
	// �e�Ƃ̓����蔻��
	CollisionEnemy();
	CollisionField();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();	// �`�揈��
}

//=============================================================================
// ��ނ��Ƃ̓����蔻���̏���
//=============================================================================
void CEnemy::CollisionEnemy(void)
{
	if (this->GetBool() == true)
	{// �����蔻�肪TRUE��������
		
		CBoss *pBoss = CGame::GetBoss();	// �Q�[���V�[������擾

		// �G�̎��
		switch (this->m_type)
		{
		case ENEMY_TYPE0:

			this->DamegeLife(1);	// ���C�t����

			if (this->GetLife() == 0)
			{// ���C�t���[����������
				CScene2D::Uninit();
				Particle::SetParticle(m_pos, m_size, 10, Particle::TYPE_EXPLOSION, "data/TEXTURE/Crystal001.png");
			}
			break;

		case ENEMY_TYPE1:

			CScene2D::Uninit();
			Particle::SetParticle(m_pos, m_size, 10, Particle::TYPE_EXPLOSION, "data/TEXTURE/Crystal001.png");

			break;

		case ENEMY_TYPE2:

			if (pBoss->GetState() == BOSS_NONE)
			{// �G���ʏ�̏�Ԃ�������
				pBoss->SetState(BOSS_DAMAGE);
			}
			break;
		}
		this->SetBool(false);	// �t���O������
	}
}

//=============================================================================
// �v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CEnemy::CollisionPlayer(void)
{
	D3DXVECTOR3 pos = CGame::GetPlayer()->GetPos();
	D3DXVECTOR3 size = CGame::GetPlayer()->GetSize();

	return  Collision::CollisionCycle(m_pos, pos, size.x);
}

//=============================================================================
// �n�ʂƂ̓����蔻��
//=============================================================================
void CEnemy::CollisionField(void)
{
	CMesh* pMesh = CGame::GetMesh();

	// ���_���̎擾
	VERTEX_2D *pVtx = pMesh->GetVERTEX();

	// ��ӂ̒��S���W�ݒ�
	D3DXVECTOR3 posA = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);

	for (int nCnt = 0; nCnt < pMesh->GetVtxNum() / 2; nCnt++)
	{// ���b�V���|���S����ӂ̂ݎZ�o
		if (m_pos.x > pVtx[nCnt].pos.x && m_pos.x < pVtx[nCnt + 1].pos.x)
		{// ��̒��_�Ɠ_�̊O�ϔ���
			if (Collision::OutProduct(pVtx[nCnt].pos, pVtx[nCnt + 1].pos, posA))
			{// �_����_��艺�ɂ�����

				Uninit();
				Particle::SetParticle(m_pos, m_size, 10, Particle::TYPE_EXPLOSION, "data/TEXTURE/Crystal001.png");
				break;
			}
		}
	}
}
