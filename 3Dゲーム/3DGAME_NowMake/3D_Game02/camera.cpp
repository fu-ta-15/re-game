//##################################################################################################################################################################//
//																																									//
// �J�������� [camera.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "camera.h"
#include "keyinput.h"
#include "Dinput.h"
#include "player.h"
#include "fade.h"
#include "renderer.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define CAMERA_POS_Y					(200.0f)
#define CAMERA_POS_Z					(500.0f)
#define CAMERA_DISTANCE_V				(600.0f)
#define INIT_CAMERA_POSV				(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))
#define CAMERA_PAD_SPEED				(0.02f)	


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Camera g_camera;	//�J�����̏��


void PadMoveCamera(void);
void KeyMoveCamera(void);
void CameraControl(MODE Mode);

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
void InitCamera(void)
{
	g_camera.posV		= INIT_CAMERA_POSV;					// ���_(����)
	g_camera.posR		= VECTOR_ZERO;						// �����_(����)
	g_camera.posVDest	= VECTOR_ZERO;						// ���_(�ړI)
	g_camera.posRDest	= VECTOR_ZERO;						// �����_(�ړI)
	g_camera.moveX		= VECTOR_ZERO;						// �ړ���
	g_camera.moveZ		= VECTOR_ZERO;						// �ړ���
	g_camera.moveVY		= VECTOR_ZERO;						// �ړ���
	g_camera.moveRY		= VECTOR_ZERO;						// �ړ���
	g_camera.rot		= VECTOR_ZERO;						// �J�����̌���
	g_camera.vecU		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitCamera(void)
{



}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateCamera(void)
{
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:	// �Q�[�����[�h

		// �J�����̈ړ�
		PadMoveCamera();
		// �J�����̐���
		CameraControl(Mode);
	default:
		break;
	}

}

//=====================================================================================================================================================================//
// �J�����̈ړ�
//=====================================================================================================================================================================//
void PadMoveCamera(void)
{
	// �R���g���[���[���̃|�C���^
	DIJOYSTATE2 *pController = pGetPadCont();					

	// �J�����̈ړ�
	if (pController->lZ > 0) g_camera.rot.y += CAMERA_PAD_SPEED;
	if (pController->lZ < 0) g_camera.rot.y -= CAMERA_PAD_SPEED;

	if (pController->lRz > 0) g_camera.rot.z -= CAMERA_PAD_SPEED;
	if (pController->lRz < 0) g_camera.rot.z += CAMERA_PAD_SPEED;


	/*���_�̑���*/
	// �E����E������
	if (GetKeypadPresse(D_BUUTON_RB) == true)
	{
		g_camera.rot.y -= CAMERA_PAD_SPEED;
	}
	if (GetKeypadPresse(D_BUUTON_LB) == true)
	{
		g_camera.rot.y += CAMERA_PAD_SPEED;
	}

	// �J�����̏㉺�̐���
	if (g_camera.rot.z > D3DX_PI / 2.0f)		g_camera.rot.z = D3DX_PI / 2.0f;
	else if (g_camera.rot.z < -D3DX_PI / 2.0f)	g_camera.rot.z = -D3DX_PI / 2.1f;

	if (g_camera.rot.z > -0.05f) g_camera.rot.z = -0.05f;	// ���ɓ˂������Ȃ��悤�ɂ���

	//D3DXPI���������̑Ώ�
	// �ȏ�
	if (g_camera.rot.x > D3DX_PI)	g_camera.rot.x -= D3DX_PI * 2.0f;
	if (g_camera.rot.y > D3DX_PI)	g_camera.rot.y -= D3DX_PI * 2.0f;
	if (g_camera.rot.z > D3DX_PI)	g_camera.rot.z -= D3DX_PI * 2.0f;
	// �ȉ�
	if (g_camera.rot.x < -D3DX_PI)	g_camera.rot.x += D3DX_PI * 2.0f;
	if (g_camera.rot.y < -D3DX_PI)	g_camera.rot.y += D3DX_PI * 2.0f;
	if (g_camera.rot.z < -D3DX_PI)	g_camera.rot.z += D3DX_PI * 2.0f;
}

void KeyMoveCamera(void)
{
}

void CameraControl(MODE Mode)
{
	Player *pPlayer = GetPlayer();

	switch (Mode)
	{
	case MODE_GAME:

		// ���_�̐���
		g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y + D3DX_PI) * CAMERA_DISTANCE_V;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y - D3DX_PI) * CAMERA_DISTANCE_V;
		g_camera.posVDest.y = pPlayer->pos.y - cosf(g_camera.rot.z - D3DX_PI) * CAMERA_POS_Y;

		//// �����_�̐���
		g_camera.posRDest.x = pPlayer->pos.x;
		g_camera.posRDest.z = pPlayer->pos.z;
		g_camera.posRDest.y = pPlayer->pos.y;
		break;

	default:
		break;
	}

	// ���_�̍X�V
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.04f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.04f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.04f;

	// �����_�̍X�V
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.08f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.08f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.08f;
}


//=====================================================================================================================================================================//
// �ݒ菈��
//=====================================================================================================================================================================//
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),							// ��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// �䗦
		50.0f,											// ��O����
		6000.0f);										// ���̋���

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}


Camera *GetCamera(void)
{
	return &g_camera;
}
