//*****************************************************************************
//
// �o���b�g���b�V���|���S������ [bulletmesh.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _BULLETMESH_H_
#define	_BULLETMESH_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "mesh.h"


//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CBulletMesh : public CMesh		// �|���S��2D���p��
{
public:

	CBulletMesh(Priority nPriority);
	~CBulletMesh();	   

	// create�֐�
	static CBulletMesh *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 move, bool bWave, Priority nPriority);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool CollisionEnemy(void);
	bool CollisionBoss(void);
	bool CollisionCore(void);

	// Set�֐�


private:

	D3DXVECTOR3			m_pos;			// �ʒu
	D3DXVECTOR3			m_size;			// �T�C�Y
	D3DXVECTOR3			m_move;			// �ړ���

	int					m_nFrameTime;
	int					m_nVtxID;
	float				m_AddSize;
	float				m_fWaveTime;
	bool				m_bUse;			// �g�p���Ă��邩
	bool				m_Collision;	// �����蔻��
	bool				m_ColiPlayer;
	bool				m_bWave;
};
#endif // !_BULLET_H_
