//*****************************************************************************
//
// �o���b�g���� [bullet.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "bullet.h"
#include "game.h"
#include "collision.h"
#include "enemy.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define BULLET_TEXTURE		("data/TEXTURE/Spark002.png")

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(Priority nPriority) : CScene2D(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �o���b�g�̐���
//=============================================================================
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 move, Priority nPriority)
{
	/* �o���b�g�̗v�f��ݒ� */
	CBullet* pBullet = new CBullet(nPriority);		// �C���X�^���X����

	pBullet->m_pos = pos;					// �ʒu��ݒ�
	pBullet->m_size = size;					// �T�C�Y��ݒ�
	pBullet->m_move = move;					// �ړ��ʂ�ݒ�
	pBullet->CreateTexture(BULLET_TEXTURE);	// �e�N�X�`��
	pBullet->m_Collision = false;			// �����蔻��
	pBullet->m_bUse = true;					// �����m�F
	pBullet->Init();						// ������

	return pBullet;						// �o���b�g����Ԃ�
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init(m_pos,m_size);	// �|���S���̏���������

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();		// �|���S���̏I������
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	// ��ʂɑ��݂��Ă��邩���Ȃ���
	if (m_bUse == true)
	{// ���Ă���ꍇ
		
		CScene2D::Update();				// �|���S���̍X�V����
		
		m_pos.x += m_move.x;			// �ʒu�Ɉړ��ʂ����Z

		CScene2D::SetPos(m_pos);		// �ʒu�̍X�V

		if (CollisionBullet())
		{// ���������ꍇ 
			m_bUse = false;				// ���݂�����
			CScene2D::Uninit();		// �|���S���̏I������
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	if (m_bUse == true)
	{// ���Ă���ꍇ
		CScene2D::Draw();	// �|���S���̕`��
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CBullet::CollisionBullet(void)
{
	D3DXVECTOR3 posEnemy;							// �G�̈ʒu
	D3DXVECTOR3 sizeEnemy;							// �G�̃T�C�Y
	D3DXVECTOR3 posBoss;							// �G�̈ʒu
	D3DXVECTOR3 sizeBoss;							// �G�̃T�C�Y

	CScene *pScene = CScene::GetScene(OBJ_ENEMY);
	CScene *pSceneBoss = CScene::GetScene(OBJ_BOSS);

	m_Collision = false;	// �����蔻��͖���
	while (pScene != NULL) 
	{
		CScene *pSceneNext = pScene->GetSceneNext();

		posEnemy = pScene->GetPos();

		sizeEnemy = pScene->GetSize();

		if (Collision::CollisionCycle(m_pos, posEnemy, sizeEnemy.x) == true)
		{/* �G�͈̔͂ɒe�����݂����� */
			pScene->SetBool(true);
			m_Collision = true;							// �����蔻��͗L
			break;
		}

		pScene = pSceneNext;

	}

	while (pSceneBoss != NULL)
	{
		CScene *pSceneBNext = pSceneBoss->GetSceneNext();

		posBoss = pSceneBoss->GetPos();

		sizeBoss = pSceneBoss->GetSize();

		if (Collision::CollisionCycle(m_pos, posBoss, sizeBoss.x) == true)
		{/* �G�͈̔͂ɒe�����݂����� */
			pSceneBoss->SetBool(true);
			m_Collision = true;							// �����蔻��͗L
			break;
		}

		pSceneBoss = pSceneBNext;
	} 

	if (m_pos.x - m_size.x > SCREEN_WIDTH || m_pos.x + m_size.x < 0.0f)
	{// ��ʊO����
		m_Collision = true;				// ���݂�����
	}

	return m_Collision;	// ���茋�ʂ�Ԃ�
}

