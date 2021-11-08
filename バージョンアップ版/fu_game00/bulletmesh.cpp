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

	if (pMBullet == NULL)
	{
		pMBullet = new CBulletMesh(nPriority);
		pMBullet->m_pos = pos;
		pMBullet->m_size = size;
		pMBullet->m_move = move;
		pMBullet->m_bWave = bWave;
		pMBullet->CreateTexture("data/TEXTURE/02.png");
		pMBullet->Init();
	}

	return pMBullet;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBulletMesh::Init(void)
{
	CMesh::Init(10, 0, m_pos, m_size);
	// ���_���̎擾
	VERTEX_2D *pVtx = this->GetVERTEX();
	m_AddSize = 50.0f;
	m_nFrameTime = 0;
	m_nVtxID = 0;
	m_fWaveTime++;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBulletMesh::Uninit(void)
{
	CMesh::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBulletMesh::Update(void)
{
	// ���_���̎擾
	VERTEX_2D *pVtx = this->GetVERTEX();

	m_fWaveTime += 0.8f;
	m_nFrameTime++;

	if ((m_nFrameTime % 1) == 0)
	{
		if (m_nVtxID < this->GetVtxNum() / 2)
		{
			m_nVtxID++;
		}	
	}

	for (int nCnt = this->GetVtxNum() / 2 - 1; nCnt > this->GetVtxNum() / 2 - 1 - m_nVtxID; nCnt--)
	{
		D3DXVECTOR3 pos = m_pos;
		pVtx[nCnt].pos.x += m_move.x;
		pVtx[nCnt + this->GetVtxNum() / 2].pos.x += m_move.x;
		if (m_bWave)
		{
			pVtx[nCnt].pos.y = Move::SinWave(pos.y, 40.0f, m_move.x, m_fWaveTime+(nCnt*2));
			pos.y += m_size.y;
			pVtx[nCnt+ this->GetVtxNum() / 2].pos.y = Move::SinWave(pos.y, 40.0f, m_move.x, m_fWaveTime+(nCnt*2));
		}
	}

	CollisionEnemy();

	if (CGame::GetBoss()->GetAlive() == true)
	{
		if (CollisionCore())
		{
			CollisionBoss();
		}
	}

	CMesh::Update();

	if (pVtx[0].pos.x > SCREEN_WIDTH)
	{
		CMesh::Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBulletMesh::Draw(void)
{
	CMesh::Draw();
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CBulletMesh::CollisionEnemy(void)
{
	D3DXVECTOR3 posEnemy;							// �G�̈ʒu
	D3DXVECTOR3 sizeEnemy;							// �G�̃T�C�Y

	VERTEX_2D *pVtx = this->GetVERTEX();			// ���_���̎擾

	CScene *pScene = CScene::GetScene(OBJ_ENEMY);

	m_Collision = false;	// �����蔻��͖���

	while (pScene != NULL)
	{
		CScene *pSceneNext = pScene->GetSceneNext();

		posEnemy = pScene->GetPos();
		sizeEnemy = pScene->GetSize();

		for (int nCnt = 0; nCnt < this->GetVtxNum(); nCnt+=2)
		{
			if (Collision::CollisionCycle(pVtx[nCnt].pos, posEnemy, sizeEnemy.x) == true)
			{/* �G�͈̔͂ɒe�����݂����� */
				pScene->SetBool(true);
				//Particle::SetParticle(pVtx[nCnt].pos, D3DXVECTOR3(15.0f, 15.0f, 0.0f), 5, Particle::TYPE_EXPLOSION, "data/TEXTURE/t0004.png");
				m_Collision = true;							// �����蔻��͗L
				break;
			}
		}
		pScene = pSceneNext;
	}

	return m_Collision;	// ���茋�ʂ�Ԃ�
}

bool CBulletMesh::CollisionBoss(void)
{
	D3DXVECTOR3 posBoss;							// �G�̈ʒu
	D3DXVECTOR3 sizeBoss;							// �G�̃T�C�Y

	VERTEX_2D *pVtx = this->GetVERTEX();			// ���_���̎擾


	CScene *pSceneBoss = CScene::GetScene(OBJ_BOSS);

	m_Collision = false;	// �����蔻��͖���

	while (pSceneBoss != NULL)
	{
		CScene *pSceneBNext = pSceneBoss->GetSceneNext();

		posBoss = pSceneBoss->GetPos();

		sizeBoss = pSceneBoss->GetSize();

		for (int nCnt = 0; nCnt < this->GetVtxNum(); nCnt+=2)
		{
			if (Collision::CollisionCycle(pVtx[nCnt].pos, posBoss, 7.5f) == true)
			{/* �G�͈̔͂ɒe�����݂����� */
				pSceneBoss->SetBool(true);
				//Particle::SetParticle(pVtx[nCnt].pos, D3DXVECTOR3(15.0f, 15.0f, 0.0f), 5, Particle::TYPE_EXPLOSION, "data/TEXTURE/t0004.png");
				m_Collision = true;							// �����蔻��͗L
				break;
			}
		}

		pSceneBoss = pSceneBNext;
	}

	return m_Collision;	// ���茋�ʂ�Ԃ�
}

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
				//Particle::SetParticle(pVtx[nCnt].pos, D3DXVECTOR3(15.0f, 15.0f, 0.0f), 5, Particle::TYPE_EXPLOSION, "data/TEXTURE/t0004.png");
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
