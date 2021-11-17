//*****************************************************************************
//																																								
// �J�������� [camera.cpp]																																		
// Author : SUZUKI FUUTA																																		
//																																								
//*****************************************************************************
//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "camera.h"
#include "keyinput.h"
#include "Dinput.h"
#include "player.h"
#include "fade.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
// �}�N��
//-----------------------------------------------------------------------------
#define CAMERA_POS_Y		(500.0f)										 // �J������Y���W
#define CAMERA_POS_Z		(500.0f)										 // �J������Z���W
#define INIT_CAMERA_POSV	(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))	 // �J�����̎��_�ʒu

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_posV = INIT_CAMERA_POSV;					// ���_(����)
	m_posR = ZeroVector3;						// �����_(����)
	m_posVDest = ZeroVector3;					// ���_(�ړI)
	m_posRDest = ZeroVector3;					// �����_(�ړI)
	m_moveX = ZeroVector3;						// �ړ���
	m_moveZ = ZeroVector3;						// �ړ���
	m_moveVY = ZeroVector3;						// �ړ���
	m_moveRY = ZeroVector3;						// �ړ���
	m_rot = ZeroVector3;						// �J�����̌���
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
void CCamera::Init(void)
{
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �J�����̍X�V
//=============================================================================
void CCamera::Update(void)
{
	//// ���_�̍X�V
	//m_posV.x += (m_posVDest.x - m_posV.x) * 0.04f;
	//m_posV.z += (m_posVDest.z - m_posV.z) * 0.04f;
	//m_posV.y += (m_posVDest.y - m_posV.y) * 0.04f;

	//// �����_�̍X�V
	//m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
	//m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;
	//m_posR.y += (m_posRDest.y - m_posR.y) * 0.08f;
}

//=============================================================================
// �J�����̐ݒu
//=============================================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							// ��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// �䗦
		50.0f,											// ��O����
		6000.0f);										// ���̋���

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
