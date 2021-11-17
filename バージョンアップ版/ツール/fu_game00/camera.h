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

	void SetPosV(const D3DXVECTOR3& posV);
	void SetPosR(const D3DXVECTOR3& posR);
	void SetRot(const D3DXVECTOR3& rot);

	D3DXVECTOR3 GetPosV() { return m_posV; }
	D3DXVECTOR3 GetPosR() { return m_posR; }
	D3DXVECTOR3 GetRot() { return m_rot; }

private:
	D3DXVECTOR3 m_posV;			// ���_(����)
	D3DXVECTOR3 m_posR;			// �����_(����)
	D3DXVECTOR3 m_rot;			// �J�����̌���
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXMATRIX	m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			// �r���[�}�g���b�N�X
	float		m_fPosSpeed;

};


#endif // !_CAMERA_H_
