//*****************************************************************************
//
// �o���b�g���� [bullet.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _BULLET_H_
#define	_BULLET_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "scene2D.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CBullet : public CScene2D		
{
public:

	CBullet(Priority nPriority);
	~CBullet();	  

	// create�֐�
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 move, Priority nPriority);

	// �����o�֐�
	HRESULT Init(void);		
	void Uninit(void);		
	void Update(void);		
	void Draw(void);		

	// BOOL�֐�
	bool CollisionBullet(void);	

	// Set�֐�


private:

	D3DXVECTOR3			m_pos;			// �ʒu
	D3DXVECTOR3			m_size;			// �T�C�Y
	D3DXVECTOR3			m_move;			// �ړ���

	int					m_BulletStock;
	bool				m_bUse;			// �g�p���Ă��邩
	bool				m_Collision;	// �����蔻��
	bool				m_ColiPlayer;
};
#endif // !_BULLET_H_
