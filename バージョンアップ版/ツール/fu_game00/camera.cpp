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
#define CAMERA_POS_Y		(100.0f)										 // �J������Y���W
#define CAMERA_POS_Z		(-200.0f)										 // �J������Z���W
#define INIT_CAMERA_POSV	(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))	 // �J�����̎��_�ʒu

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_posV = INIT_CAMERA_POSV;					// ���_(����)
	m_posR = ZeroVector3;						// �����_(����)
	m_rot = ZeroVector3;						// �J�����̌���
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
	m_fPosSpeed = 1.5f;
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

	// �L�[���̓N���X�̃|�C���^
	CKey *pKey = CManager::GetKey();

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_Z))
	{
		m_rot.y -= 0.005f;

		if (m_rot.y < -D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}

		// �����_�̍X�V
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_C))
	{
		m_rot.y += 0.005f;

		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}

		// �����_�̍X�V
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_Q))
	{
		m_rot.y -= 0.05f;						// ��]��

		if (m_rot.y < -D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}

		// ���_�̍X�V
		m_posV.x = m_posR.x - sinf(m_rot.y) * 200;
		m_posV.z = m_posR.z - cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_E))
	{
		m_rot.y += 0.05f;						// ��]��

		if (m_rot.y > D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		// ���_�̍X�V
		m_posV.x = m_posR.x - sinf(m_rot.y) * 200;
		m_posV.z = m_posR.z - cosf(m_rot.y) * 200;
	}

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_T))
	{
		// �����_�̏�ړ�
		m_posR.y += m_fPosSpeed;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_B))
	{
		// �����_�̉��ړ�
		m_posR.y -= m_fPosSpeed;
	}

	if (pKey->GetState(CKey::STATE_PRESSE, DIK_W))
	{
		// ���_�̑O�ړ�
		m_posV.x += m_fPosSpeed * sinf(m_rot.y);
		m_posV.z += m_fPosSpeed * cosf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_S))
	{
		// ���_�̌��ړ�
		m_posV.x -= m_fPosSpeed * sinf(m_rot.y);
		m_posV.z -= m_fPosSpeed * cosf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_A))
	{
		// ���_�̍��ړ�
		m_posV.x -= m_fPosSpeed * cosf(m_rot.y);
		m_posV.z += m_fPosSpeed * sinf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_D))
	{
		// ���_�̉E�ړ�
		m_posV.x += m_fPosSpeed * cosf(m_rot.y);
		m_posV.z -= m_fPosSpeed * sinf(m_rot.y);
		m_posR.x = m_posV.x + sinf(m_rot.y) * 200;
		m_posR.z = m_posV.z + cosf(m_rot.y) * 200;
	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_Y))
	{
		// ���_�̏�ړ�
		m_posV.y += m_fPosSpeed;

	}
	if (pKey->GetState(CKey::STATE_PRESSE, DIK_N))
	{
		// ���_�̉��ړ�
		m_posV.y -= m_fPosSpeed;
	}
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

void CCamera::SetPosV(const D3DXVECTOR3 & posV)
{
	m_posV = posV;

}

void CCamera::SetPosR(const D3DXVECTOR3 & posR)
{
}

void CCamera::SetRot(const D3DXVECTOR3 & rot)
{
}
