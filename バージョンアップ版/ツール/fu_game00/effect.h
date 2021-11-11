//*****************************************************************************
//
// �G�t�F�N�g���� [effect.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _EFFECT_H_
#define _EFFECT_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "manager.h"
#include "scene2D.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CEffect : public CScene2D
{
public:

	CEffect();		 // �R���X�g���N�^
	~CEffect();		 // �f�X�g���N�^

	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	  // �G�t�F�N�g�|���S���̃N���G�C�g

	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size	  // �p�[�e�B�N���p�N���G�C�g
							,D3DXVECTOR3 move, LPDIRECT3DTEXTURE9 ptex);

	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��

	void CollisionField(void);	 // �����蔻��

	// Set�֐�
	void SetColor(D3DXCOLOR col)	{ m_col = col; }
	void SetMove(D3DXVECTOR3 move)	{ m_move = move; }
	void SetUse(bool bUse)			{ m_bUse = bUse; }
	void SetPos(D3DXVECTOR3 pos)	{ m_pos = pos; }

	// Get�֐�
	D3DXCOLOR GetColor(void)		{ return m_col; }
	D3DXVECTOR3 GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 GetMove(void)		{ return m_move; }
	bool GetUse(void)				{ return m_bUse; }

private:
	D3DXVECTOR3					m_pos;		   // �ʒu
	D3DXVECTOR3					m_size;		   // �T�C�Y
	D3DXVECTOR3					m_move;		   // �ړ���
	D3DXCOLOR					m_col;		   // �F
	bool						m_bUse;		   // �g�p���Ă��邩�ǂ���
	bool						m_bMove;	   // �Œ�E���R
};
#endif // !_EFFECT_H_