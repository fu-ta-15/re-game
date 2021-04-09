//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	camera.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "camera.h"

#include "main.h"
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "field.h"
#include "train.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCamera::CCamera()
{
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCamera::~CCamera()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CCamera::Init(void)
{
    //�J�����̏���(�ʒu�E���ӓ_�E�����)�ݒ�
    m_posV = D3DXVECTOR3(-350.0f, 1000.0f, 200.0f);
    m_posR = D3DXVECTOR3(400.0f, 0.0f, 0.0f);
    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //�J�����̌����ݒ�
    m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
    //�J�����̃v���C���[����̋����ݒ�
    //���_-���ӓ_�̋����̌v�Z
    m_fDistance = (float)sqrt(pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::Uninit(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::Update(void)
{
	D3DXVECTOR3 pos;
	CTrain *pTrain = CGame::GetField()->GetTrain();
	
	pos = pTrain->GetPos();

	m_posR = pos + D3DXVECTOR3(0.0f, 0.0f, 250.0f);
	m_posR.x = 400.0f;
	m_posV = pos + D3DXVECTOR3(0.0f, 1000.0f, 325.0f);
	m_posV.x = -350.0f;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�J�����ɂ��`��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::SetCamera(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    //�f�o�C�X�ւ̃|�C���^
    //�r���[�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxView);
    //�r���[�}�g���b�N�X�̍쐬
    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    //�r���[�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
    //�v���W�F�N�V�����}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxProjection);
    //�v���W�F�N�V�����}�g���b�N�X�̍쐬
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
    //�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CCamera::GetRot(void)
{
    return m_rot;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
    //�����_���������̒����ɕ␳���ďo��
    D3DXVECTOR3 vec;
    D3DXVec3Normalize(&vec, &(m_posR - m_posV));
    vec = vec * m_fDistance + m_posV;
    return vec;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::SetRot(D3DXVECTOR3 rot)
{
    m_rot = rot;
}
