//*****************************************************************************
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "player.h"
#include "keyinput.h"
#include "manager.h"
#include "collision.h"
#include "mesh.h"
#include "game.h"
#include "tutorial.h"
#include "move.h"
#include "bulletmesh.h"
#include "particle.h"
#include "time.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define PLAYER_MOVE					(5.0f)
#define PLAYER_JUNP					(20.0f)

#define BULLET_SIZE					(D3DXVECTOR3(20.0f, 20.0f, 0.0f))
#define BULLET_MOVE_RIGHT			(D3DXVECTOR3(10.0f, 0.0f, 0.0f))
#define BULLET_MOVE_LEFT			(D3DXVECTOR3(-10.0f, 0.0f, 0.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CScene2D(OBJ_PLAYER)
{
	this->m_col = WhiteColor;				// �F���
	this->m_posOld = ZeroVector3;			// �v���C���[�̉ߋ��̈ʒu
	this->m_fLife = PLAYER_LIFE;			// �̗�
	this->m_state = STATE_NONE;				// ���
	this->m_bUse = true;					// �g�p��
	this->m_nBullet = 10;					// �e�̃X�g�b�N
	this->m_pShield = NULL;					// �V�[���h
	this->m_nBulletTime = 0;				// �e�̕������Ԃ̃J�E���g
	this->m_bAlive = true;					// ������
	this->m_bFall = false;					// ����������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer * CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �v���C���[�̃|�C���^�ϐ�����
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL�`�F�b�N
		pPlayer = new CPlayer;			// �C���X�^���X����
		pPlayer->m_pos = pos;			// �ʒu�̐ݒ�
		pPlayer->m_size = size;			// �T�C�Y�̐ݒ�
		pPlayer->Init();				// ����������
	}
	// ����Ԃ�
	return pPlayer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// �����o�ϐ��̐ݒ�
	m_tex = D3DXVECTOR2(2, 0);
	m_number = D3DXVECTOR2(1, 0);
	m_nAnimeCnt = 1;
	m_nBulletCharge = 0;

	// �|���S���̐����E�e�N�X�`���̐ݒ�
	CScene2D::Init(m_pos, m_size);
	CScene2D::CreateTexture("data/TEXTURE/player0.png");
	CScene2D::SetTex(m_tex, m_number);

	// ���C�t�̐ݒ�
	for (int nCntLife = 0; nCntLife < PLAYER_LIFE_STOCK; nCntLife++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(50.0f, 190.0f - (10 * nCntLife), 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(10.0f,5.0f, 0.0f);
		m_pLife[nCntLife] = CScene2D::Create(pos, size);
		m_pLife[nCntLife]->CreateTexture("data/TEXTURE/lifeBlock.png");
	}

	// �E�F�|���̐ݒ�
	for (int nCntWeapon = 0; nCntWeapon < PLAYER_BULLET_STOCK; nCntWeapon++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(80.0f, 100.0f + (10 * nCntWeapon), 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(10.0f, 5.0f, 0.0f);
		m_pWeapon[nCntWeapon] = CScene2D::Create(pos, size);
		m_pWeapon[nCntWeapon]->CreateTexture("data/TEXTURE/BulletBlock.png");
	}

	// �V�[���h�̐ݒ�
	m_pShield = CEffect::Create(m_pos, m_size * 2);
	m_pShield->CreateTexture("data/TEXTURE/Shockwave.png");
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// �|���S���̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h���擾
	CKey *pKey = CManager::GetKey();

	if (m_state == STATE_NONE)
	{// �����Ȃ���Ԃ̎�
		PlayerAction();	// �A�N�V����
	}

	// ���C�t�̊Ǘ�
	PlayerLife();

	// �ړ��ʂ̉��Z
	m_move.y += 1.0f;

	// �ړ��ʂ̉��Z
	m_pos += m_move;

	// �ړ��ʂ̐���
	PlayerMoveControl();

	// �ʒu�̐���
	PosControl();	

	// �A�j���[�V����
	PlayerAnime();

	// ��ԊǗ�
	PlayerState();

	CScene2D::SetUse(m_bUse);	// ���݂��Ă���
	CScene2D::SetPos(m_pos);	// �ʒu�̐ݒ�i�X�V�j
	CScene2D::SetCol(m_col);	// �F�̐ݒ�i�X�V�j
	m_pShield->SetPos(m_pos);	// �V�[���h�̈ʒu�X�V
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �|���S���̕`��
	CScene2D::Draw();
}

//=============================================================================
// �v���C���[�̈ʒu����
//=============================================================================
void CPlayer::PosControl(void)
{
	// �n�ʂ̓����蔻��
	FieldControl();

	if (m_pos.x - m_size.x < 0)
	{// ����ʒ[���
		m_pos.x = 0 + m_size.x;				// ���̈ʒu�̖߂�
	}
	if (m_pos.x + m_size.x > SCREEN_WIDTH)
	{// �E��ʒ[���
		m_pos.x = SCREEN_WIDTH - m_size.x;	// ���̈ʒu�̖߂�
	}
}

//=============================================================================
// �v���C���[�̃A�N�V����
//=============================================================================
void CPlayer::PlayerAction(void)
{
	// �L�[�{�[�h���擾
	CKey *pKey = CManager::GetKey();

	// �e�����p�̃^�C��
	m_nBulletTime++;

	// �e�̕���
	if ((m_nBulletTime % 35) == 0)
	{// ��35�t���[��
		for (int nCntWeapon = PLAYER_BULLET_STOCK; nCntWeapon > 0; nCntWeapon--)
		{
			if (m_pWeapon[nCntWeapon - 1]->GetUse() != true)
			{// �o���b�g�̃X�g�b�N��
				m_nBullet += 1;
				m_pWeapon[nCntWeapon - 1]->SetUse(true);
				break;
			}
		}
	}

	// �ړ�
	PlayerMove();

	// �e�̔���
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_NUMPAD6) == true)
	{
		m_nBulletCharge++;
		if ((m_nBulletCharge % 20) == 0)
		{
			CBulletMesh::Create(m_pos, D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), true, OBJ_BULLET2);	// �o���b�g�̐���
			m_nBulletCharge = 0;																												// �v���C���[�̒e����
		}
	}
	else if (pKey->GetState(CKey::STATE_RELEASE, DIK_NUMPAD6) == true)
	{// �g���K�[�ENUM6 �������ꂽ�Ƃ�
		CBulletMesh::Create(m_pos, D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), false, OBJ_BULLET1);	// �o���b�g�̐���
		m_nBulletCharge = 0;
		m_bPresse = false;
	}

}

//=============================================================================
// �v���C���[�̈ړ�
//=============================================================================
void CPlayer::PlayerMove(void)
{
	// �L�[�{�[�h���擾
	CKey *pKey = CManager::GetKey();

	/* �v���C���[�̈ړ� */
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_D) == true)	
	{// �v���X�ED�������ꂽ�Ƃ�
		m_nAnimeCnt++;
		m_move.x += PLAYER_MOVE;	// �ړ��ʂ̍X�V
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_A) == true)	
	{// �v���X�EA�������ꂽ�Ƃ�
		m_nAnimeCnt++;
		m_move.x -= PLAYER_MOVE;	// �ړ��ʂ̍X�V
	}

	/* �v���C���[�̃W�����v */
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_W) == true)	
	{// �g���K�[�ESPACE�������ꂽ�Ƃ�
		if (m_bJunp == false)
		{// �W�����v�\�Ȃ��
			m_move.y -= PLAYER_JUNP;// �ړ��ʂ̍X�V
			m_bJunp = true;			// �W�����v��
		}
	}

	/* �v���C���[�̗������� */
	if (m_bJunp == true)
	{// �W�����v�����A�d�͂��v���X�̎�
		if (pKey->GetState(CKey::STATE_PRESSE, DIK_W) == true)	
		{// �v���X�ESPACE�������ꂽ�Ƃ�
			m_move.y -= 0.6f;	// �d�͂̌���
		}
	}
}

//=============================================================================
// �v���C���[�̈ړ��ʂ̃R���g���[��
//=============================================================================
void CPlayer::PlayerMoveControl(void)
{
	// �ړ��E��]�ʂ̌���
	m_move = Move::MoveControl(m_move, D3DXVECTOR3(1.0f, 0.02f, 0.0f));
}

//=============================================================================
// �t�B�[���h��̃v���C���[����
//=============================================================================
void CPlayer::FieldControl(void)
{
	// Mesh�̃|�C���^
	CMesh* pMesh = NULL;

	// ���b�V���|���S���̏��擾
	switch (CManager::GetMode())
	{
		// �`���[�g���A��
	case CManager::MODE_TUTORIAL:
		pMesh = CTutorial::GetMesh();
		break;
		// �Q�[��
	case CManager::MODE_GAME:
		pMesh = CGame::GetMesh();
		break;
	default:
		break;
	}

	// ���_���̎擾
	VERTEX_2D *pVtx = pMesh->GetVERTEX();


	// ��ӂ̒��S���W�ݒ�
	D3DXVECTOR3 posA = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, m_pos.z);

	// �O�ϓ����蔻��
	bool bOutPro = false;

	for (int nCnt = 0; nCnt < pMesh->GetVtxNum() / 2; nCnt++)
	{// ���b�V���|���S����ӂ̂ݎZ�o
		if (m_pos.x > pVtx[nCnt].pos.x && m_pos.x < pVtx[nCnt + 1].pos.x && m_bFall == false)
		{// ��̒��_�Ɠ_�̊O�ϔ���
			bOutPro = Collision::OutProduct(pVtx[nCnt].pos, pVtx[nCnt + 1].pos, posA);
		}
		if (bOutPro)
		{// �_����_��艺�ɂ�����
			m_posOld = Collision::WaveCollision(pVtx[nCnt].pos, pVtx[nCnt + 1].pos, posA);	// �߂������Z�o
			m_move.y = 0.0f;					// �d�̓[��
			m_pos.y = m_posOld.y - m_size.y;	// ��ʓ��܂ňړ�������
			if (m_bJunp == true)
			{
				m_bJunp = false;					// �W�����v�\
				Particle::SetParticle(D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f), m_size*0.4f, 50, Particle::TYPE_DOWN_FAN, "data/TEXTURE/Fog2001.png");
			}
			break;
		}
	}
	if (m_pos.y + m_size.y > pVtx[0].pos.y)
	{
		m_bFall = true;
		if (m_pos.x - m_size.x < WIDTH_HALF + 100)
		{
			m_pos.x = WIDTH_HALF + 100 + m_size.x;
		}
	}
}

//=============================================================================
// �v���C���[�̃A�j���[�W����
//=============================================================================
void CPlayer::PlayerAnime(void)
{
	if ((m_nAnimeCnt % 5) == 0)
	{// �J�E���g���P�O���܂�P�̎�
		m_number.x += 1;	// �e�N�X�`�����W���Z
		m_nAnimeCnt = 0;
		if (((int)m_number.x % 2) == 0)
		{// �e�N�X�`�����W���߂��Ă�����
			m_number.x = 0.0f;	// �����l�ɖ߂�
		}
		// �e�N�X�`�����W�̔��f
		CScene2D::SetTex(m_tex, m_number);
	}
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::PlayerState(void)
{
	// �ʏ��Ԃ̏ꍇ
	if (m_state == STATE_NONE)
	{
		m_col = WhiteColor;	// �F��߂�
		m_bDamage = false;	// �_���[�W����OFF
	}

	// �V�[���h������ꍇ
	if (m_pShield->GetUse() == true && m_bCollEnemy == true)
	{
		m_pShield->SetUse(false);	// �V�[���h�폜
		m_bCollEnemy = false;		// �����蔻������Ƃɖ߂�
	}

	// �V�[���h���Ȃ������灕���G�ɓ���������
	if (m_pShield->GetUse() == false && m_bCollEnemy == true)
	{
		m_state = STATE_KNOCKUP;					// �m�b�N�A�b�v���
		m_bDamage = true;							// �_���[�W����ON
		m_KnockUpPos.x = 0.0f;						// �m�b�N�A�b�v�̈ʒu
		m_KnockUpPos.y = m_pos.y + 40.0f;			// �m�b�N�A�b�v�̈ʒu
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	// �_���[�W�̐F�ɕύX
		m_bCollEnemy = false;						// �����蔻������Ƃɖ߂�
	}

	// �m�b�N�A�b�v��Ԃ̎�
	if (m_state == STATE_KNOCKUP)
	{
		DamagePlayer();	// �m�b�N�A�b�v��Ԃ̏���
	}
}

//=============================================================================
// �v���C���[���g�Ƀ_���[�W���󂯂�����
//=============================================================================
void CPlayer::DamagePlayer(void)
{
	// �J�E���g�A�b�v
	m_nDamageCnt++;	
	
	// �ړI�̏ꏊ�փm�b�N�A�b�v
	m_pos.x = Move::TargetPosMove(D3DXVECTOR3(m_KnockUpPos.x, 0.0f, 0.0f), m_pos, 0.035f).x;
	m_pos.y = Move::TargetPosMove(D3DXVECTOR3(0.0f, m_KnockUpPos.y, 0.0f), m_pos, 0.015f).y;

	// �J�E���g�����܂ŗ�����
	if ((m_nDamageCnt % 15) == 0)
	{
		m_fLife -= (m_fLife * 0.056f + 1.2f);	// ���C�t�̌���
		m_state = STATE_NONE;					// ��Ԃ�߂�
		m_nDamageCnt = 0;						// �J�E���g������������
	}
}

//=============================================================================
// ���C�t�Ǘ�
//=============================================================================
void CPlayer::PlayerLife(void)
{
	for (int nCntLife = 0; nCntLife < PLAYER_LIFE_STOCK; nCntLife++)
	{
		// ���C�t�����̒l�𒴂�����
		if (m_fLife < nCntLife * 10)
		{
			// ���C�t���폜
			if (m_pLife[nCntLife] != NULL)
			{
				m_pLife[nCntLife]->Release();
				m_pLife[nCntLife] = NULL;
				break;
			}
		}
	}

	// ���C�t���[���ɂȂ�����
	if (m_fLife < 0)
	{
		m_bAlive = false;
		m_bUse = false;
	}
}

//=============================================================================
// �o���b�g�̊Ǘ�
//=============================================================================
void CPlayer::PlayerBullet(int nBullet)
{
	for (int nCnt = 0; nCnt < nBullet; nCnt++)
	{
		for (int nCntWeapon = 0; nCntWeapon < PLAYER_BULLET_STOCK; nCntWeapon++)
		{
			// �g�p�������̃|���S�����c���Ă�����
			if (m_pWeapon[nCntWeapon]->GetUse() != false)
			{
				m_nBullet -= 1;							// �X�g�b�N�̌��炷
				m_pWeapon[nCntWeapon]->SetUse(false);	// ���̃|���S�����g�p���Ă��Ȃ���Ԃɂ���
				break;
			}
		}
	}
}
