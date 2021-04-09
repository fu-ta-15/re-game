//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	camera.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define CAMERA_VIEW_RANGE (1000000.0f)
#define CAMERA_DISTANCE_FROM_PLAYER (5.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_STAND (75.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_AIM (25.0f)
#define PLAYER_HEAD_HEIGHT (37.0f)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CCamera
{
public:
    CCamera();
    ~CCamera();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void SetCamera(void);
    D3DXVECTOR3 GetRot(void);
    void SetRot(D3DXVECTOR3 rot);
    D3DXVECTOR3 GetPosR(void);

private:
    D3DXVECTOR3 m_posV;            //�J�����̍��W
    D3DXVECTOR3 m_posR;            //�����_�̍��W
    D3DXVECTOR3 m_vecU;            //�J�����̏����
    D3DXMATRIX m_mtxProjection;    //�v���W�F�N�V�����}�g���b�N�X
    D3DXMATRIX m_mtxView;          //�r���[�}�g���b�N�X
    D3DXVECTOR3 m_rot;
	float m_fDistance;
};

#endif
