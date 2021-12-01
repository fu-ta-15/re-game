//*****************************************************************************
//
// �o���b�g���b�V���|���S������ [bulletmesh.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "bulletmesh.h"
#include "manager.h"
#include "game.h"
#include "move.h"
#include "player.h"
#include "collision.h"
#include "particle.h"
#include "core.h"
#include "boss.h"
#include "tutorial.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletMesh::CBulletMesh(Priority nPriority) : CMesh(nPriority)
{
	// �����o�ϐ��̏�����
	m_nFrameTime = 0;
	m_nVtxID = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletMesh::~CBulletMesh()
{

}

//=============================================================================
// Mesh�̃o���b�g����
//=============================================================================
CBulletMesh * CBulletMesh::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 move ,bool bWave, Priority nPriority)
{
	CBulletMesh *pMBullet = NULL;

	// NULL�`�F�b�N
	if (pMBullet == NULL)
	{
		pMBullet = new CBulletMesh(nPriority);			// �C���X�^���X����
		pMBullet->m_pos = pos;							// �ʒu
		pMBullet->m_size = size;						// �T�C�Y
		pMBullet->m_move = move;						// �ړ���
		pMBullet->m_bWave = bWave;						// �g�̕\���ɂ��邩
		pMBullet->CreateTexture("data/TEXTURE/02.png");	// �e�N�X�`���̐ݒ�
		pMBullet->Init();
	}

	return pMBullet;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBulletMesh::Init(void)
{
	// ������
	CMesh::Init(10, 0, m_pos, m_size);

	// ���_���̎擾
	VERTEX_2D *pVtx = this->GetVERTEX();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBulletMesh::Uninit(void)
{
	// �I������
	CMesh::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBulletMesh::Update(void)
{
	// ���_���̎擾
	VERTEX_2D *pVtx = this->GetVERTEX();

	// �J�E���g�A�b�v
	m_fWaveTime += 0.8f;
	m_nFrameTime++;

	// �t���[�����Ƃɉ��Z
	if ((m_nFrameTime % 1) == 0)
	{
		// �w��̒��_ID�����̍ő�ID�ȉ���������
		if (m_nVtxID < this->GetVtxNum() / 2)
		{
			// �J�E���g�A�b�v
			m_nVtxID++;
		}	
	}

	// �ő�l����̌v�Z
	for (int nCnt = this->GetVtxNum() / 2 - 1; nCnt > this->GetVtxNum() / 2 - 1 - m_nVtxID; nCnt--)
	{
		// �ʒu�̕ۑ�
		D3DXVECTOR3 pos = m_pos;

		// �e���_�Ɉړ��ʂ����Z�i���j
		pVtx[nCnt].pos.x += m_move.x;

		// �e���_�Ɉړ��ʂ����Z�i����j
		pVtx[nCnt + this->GetVtxNum() / 2].pos.x += m_move.x;

		// �g�̕\������ꍇ
		if (m_bWave)
		{
			// ���ɃT�C���J�[�u�̌v�Z���
			pVtx[nCnt].pos.y = Move::SinWave(pos.y, 40.0f, m_move.x, m_fWaveTime+(nCnt*2));

			// ����Ɉړ�
			pos.y += m_size.y;

			// ����ɃT�C���J�[�u�̌v�Z���
			pVtx[nCnt+ this->GetVtxNum() / 2].pos.y = Move::SinWave(pos.y, 40.0f, m_move.x, m_fWaveTime+(nCnt*2));
		}
	}

	// �G�Ƃ̓����蔻��
	CollisionEnemy();

	// �{�X�������Ă�����
	if (CGame::GetBoss()->GetAlive() == true)
	{
		if (CollisionCore())
		{
			// �{�X�Ƃ̓����蔻��
			CollisionBoss();
		}
	}

	// �X�V����
	CMesh::Update();

	// ��ʒ[�܂ōs������
	if (pVtx[0].pos.x > SCREEN_WIDTH)
	{
		// �I������
		CMesh::Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBulletMesh::Draw(void)
{
	// �`�揈��
	CMesh::Draw();
}

//=============================================================================
// �G�Ƃ̓����蔻��
//=============================================================================
bool CBulletMesh::CollisionEnemy(void)
{
	D3DXVECTOR3 posEnemy;		// �G�̈ʒu
	D3DXVECTOR3 sizeEnemy;		// �G�̃T�C�Y

	// ���_���̎擾
	VERTEX_2D *pVtx = this->GetVERTEX();			

	// �V�[���̎擾
	CScene *pScene = CScene::GetScene(OBJ_ENEMY);

	// �����蔻��͖���
	m_Collision = false;	

	// NULL�`�F�b�N
	while (pScene != NULL)
	{
		// ���擾
		CScene *pSceneNext = pScene->GetSceneNext();

		// �ʒu�ƃT�C�Y�̎擾
		posEnemy = pScene->GetPos();
		sizeEnemy = pScene->GetSize();

		for (int nCnt = 0; nCnt < this->GetVtxNum(); nCnt+=2)
		{
			if (Collision::CollisionCycle(pVtx[nCnt].pos, posEnemy, sizeEnemy.x) == true)
			{/* �G�͈̔͂ɒe�����݂����� */

				// �����蔻��͗L
				pScene->SetBool(true);
				m_Collision = true;							
				break;
			}
		}

		// ���̏����擾
		pScene = pSceneNext;
	}

	// ���茋�ʂ�Ԃ�
	return m_Collision;	
}

//=============================================================================
// �{�X�Ƃ̓����蔻��
//=============================================================================
bool CBulletMesh::CollisionBoss(void)
{
	D3DXVECTOR3 posBoss;	// �G�̈ʒu
	D3DXVECTOR3 sizeBoss;	// �G�̃T�C�Y

	// ���_���̎擾
	VERTEX_2D *pVtx = this->GetVERTEX();			

	// �V�[���̏��擾
	CScene *pSceneBoss = CScene::GetScene(OBJ_BOSS);

	// �����蔻��͖���
	m_Collision = false;	

	// NULL�`�F�b�N
	while (pSceneBoss != NULL)
	{
		// �V�[���̏��擾
		CScene *pSceneBNext = pSceneBoss->GetSceneNext();

		// �ʒu�ƃT�C�Y�擾
		posBoss = pSceneBoss->GetPos();
		sizeBoss = pSceneBoss->GetSize();

		for (int nCnt = 0; nCnt < this->GetVtxNum(); nCnt+=2)
		{
			if (Collision::CollisionCycle(pVtx[nCnt].pos, posBoss, 7.5f) == true)
			{/* �G�͈̔͂ɒe�����݂����� */

				// �����蔻��L�ɂ���
				pSceneBoss->SetBool(true);
				m_Collision = true;							
				break;
			}
		}

		// ���̃V�[���擾
		pSceneBoss = pSceneBNext;
	}

	// ���茋�ʂ�Ԃ�
	return m_Collision;	
}

//=============================================================================
// �R�A�Ƃ̓����蔻��
//=============================================================================

bool CBulletMesh::CollisionCore(void)
{
	CCore **pCore = NULL;
	// ���b�V���|���S���̏��擾
	switch (CManager::GetMode())
	{
	case CManager::MODE_TUTORIAL:
		pCore = CTutorial::GetBoss()->GetCore();
		break;

	case CManager::MODE_GAME:
		// �{�X�̏��
		pCore = CGame::GetBoss()->GetCore();
		break;

	default:
		break;
	}

	VERTEX_2D *pVtx = this->GetVERTEX();			// ���_���̎擾
	m_Collision = false;	// �����蔻��͖���

	for (int nCntCore = 0; nCntCore < 3; nCntCore++)
	{
		for (int nCnt = 0; nCnt < this->GetVtxNum(); nCnt+=2)
		{
			if (Collision::CollisionCycle(pVtx[nCnt].pos, pCore[nCntCore]->GetPos(), pCore[nCntCore]->GetSize().x) == true
				&& pCore[nCntCore]->GetUse() == true)
			{
				pCore[nCntCore]->SetUse(false);
				m_Collision = true;							// �����蔻��͗L
				break;
			}
		}
	}

	bool bColBoss = false;

	if (pCore[0]->GetUse() == false && pCore[1]->GetUse() == false && pCore[2]->GetUse() == false)
	{
		bColBoss = true;
	}

	return bColBoss;
}
