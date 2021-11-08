//*****************************************************************************
//
// �{�X�G���� [boss.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _BOSS_H_
#define _BOSS_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "effect.h"
#include "mesh.h"
#include "core.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define BOSS_LIFE_STOCK		(BOSS_LIFE / 10)				// ���C�t�̃X�g�b�N


//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CBoss : public CEnemy
{
public:
	// �{�X�̏��
	typedef enum BOSS_STATE
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_NOT_DAMAGE,
		STATE_MAX
	}BOSS_STATE;

	// �{�X�̃��C�t�̏��
	typedef enum LIFE_STATE
	{
		LIFE_RATE_0 = 0,
		LIFE_RATE_2,
		LIFE_RATE_5,
		LIFE_RATE_8,
		LIFE_RATE_MAX
	}LIFE_STATE;

	CBoss();	  // �R���X�g���N�^
	~CBoss();	  // �f�X�g���N�^

	static CBoss *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size,const int nLife);  // �N���G�C�g

	HRESULT Init(void);	   // ������
	void Uninit(void);	   // �I��
	void Update(void);	   // �X�V
	void Draw(void);	   // �`��

	// Set�֐�
	void SetState(BOSS_STATE state)		{ m_State = state; }
	void SetAlive(bool bAlive)			{ m_bBoss_Alive = bAlive; }

	// Get�֐�
	CCore **GetCore(void)				{ return &m_pCore[0]; }
	BOSS_STATE GetState(void)			{ return m_State; }
	LIFE_STATE GetLifeState(void)		{ return m_LifeState; }
	float GetLife(void)					{ return m_fLife; }
	bool GetAlive(void)					{ return m_bBoss_Alive; }

private:
	void DamageBoss(void);
	LIFE_STATE LifeState(int nLife);
	void MoveBoss(void);
	void SummonsEnemy(void);
	void StateUpdate(void);

	CEffect				*m_pDamage;					 // �_���[�W���̃G�t�F�N�g
	CScene2D			*m_pLife[BOSS_LIFE_STOCK];	 // ���C�t�̃X�g�b�N
	CScene2D			*m_pShiled;					 // �V�[���h
	CCore				*m_pCore[3];				 // �R�A
	BOSS_STATE			m_State;					 // �{�X�̏��
	LIFE_STATE			m_LifeState;				 // HP�̏��
	D3DXVECTOR3			m_OldPos;					 // �ߋ��̈ʒu
	D3DXCOLOR			m_StateCol;					 // ��Ԃ̐F
	static bool			m_bBoss_Alive;				 // �{�X�̐����m�F
	bool				m_bDamage;					 // �_���[�W�t���O
	int					m_nDamageCnt;				 // �_���[�W�J�E���g
	float				m_fLife;					 // ���C�t
	float				m_fA_Damage;				 // �����x�̉��Z�p
	float				m_fMoveTime;				 // �ړ��p�̃J�E���g
};

#endif // !_BOSS_H_
