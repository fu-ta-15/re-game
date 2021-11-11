//*****************************************************************************
//
// �J�����w�b�_�t�@�C�� [camera.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"


class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

private:
	D3DXVECTOR3 m_posV;			// ���_(����)
	D3DXVECTOR3 m_posR;			// �����_(����)
	D3DXVECTOR3 m_posVDest;		// ���_(�ړI)
	D3DXVECTOR3 m_posRDest;		// �����_(�ړI)
	D3DXVECTOR3 m_moveX;			// �ړ���
	D3DXVECTOR3 m_moveZ;			// �ړ���
	D3DXVECTOR3 m_moveVY;			// �ړ���
	D3DXVECTOR3 m_moveRY;			// �ړ���
	D3DXVECTOR3 m_rot;			// �J�����̌���
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXMATRIX	m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			// �r���[�}�g���b�N�X
};


#endif // !_CAMERA_H_
