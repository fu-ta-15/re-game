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
#include "model.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define CAMERA_POS_Y					(200.0f)
#define CAMERA_POS_Z					(-500.0f)
#define CAMERA_DISTANCE_V				(500.0f)
#define CAMERA_DISTANCE_R				(30.0f)
#define INIT_CAMERA_POSV				(D3DXVECTOR3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z))


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Camera g_camera;	//�J�����̏��

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
void InitCamera(void)
{
	g_camera.posV = INIT_CAMERA_POSV;					// ���_(����)
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_(����)
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_(�ړI)
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_(�ړI)
	g_camera.moveX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_camera.moveZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_camera.moveVY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_camera.moveRY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̌���
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
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
	Player *pPlayer = GetPlayer();

	MoveCamera();

	/*���_�̑���*/
	// �E����E������
	if (GetKeyboardPresse(DIK_Q) == true || GetKeypadPresse(D_BUUTON_LB) == true)
	{
		g_camera.rot.y -= 0.03f;
		if (g_camera.rot.y < (-D3DX_PI))
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPresse(DIK_E) == true || GetKeypadPresse(D_BUUTON_RB) == true)
	{
		g_camera.rot.y += 0.03f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI*2.0f;
		}
	}
	// ��ړ��E���ړ�
	if (GetKeyboardPresse(DIK_Y) == true)
	{
		g_camera.moveVY.y += 1.0f;
	}
	if (GetKeyboardPresse(DIK_N) == true)
	{
		g_camera.moveVY.y -= 1.0f;
	}
	/*�����_�̑���*/
	// ��ړ��E���ړ�
	if (GetKeyboardPresse(DIK_T) == true)
	{
		g_camera.moveRY.y += 1.0f;
	}
	if (GetKeyboardPresse(DIK_B) == true)
	{
		g_camera.moveRY.y -= 1.0f;
	}

	// ���_�̐���
	g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y + D3DX_PI) * CAMERA_DISTANCE_V;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y - D3DX_PI) * CAMERA_DISTANCE_V;
	g_camera.posVDest.y = pPlayer->pos.y + CAMERA_POS_Y + g_camera.moveVY.y;

	//// �����_�̐���
	g_camera.posRDest.x = pPlayer->pos.x;
	g_camera.posRDest.z = pPlayer->pos.z;
	g_camera.posRDest.y = pPlayer->pos.y;

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
// �J�����̈ړ�
//=====================================================================================================================================================================//
void MoveCamera(void)
{
	/*�J�����̈ړ�*/
	// �O�ړ��E��ړ�
	if (GetKeyboardPresse(DIK_W) == true)
	{
		if (GetKeyboardPresse(DIK_A) == true)
		{
			g_camera.moveX.x -= sinf(g_camera.rot.y + D3DX_PI * 1 / 4);
			g_camera.moveZ.z += cosf(g_camera.rot.y + D3DX_PI * 1 / 4);
		}
		else if (GetKeyboardPresse(DIK_D) == true)
		{
			g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI * 3 / 4);
			g_camera.moveZ.z -= cosf(g_camera.rot.y + D3DX_PI * 3 / 4);
		}
		else
		{
			g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI);
			g_camera.moveZ.z -= cosf(g_camera.rot.y - D3DX_PI);
		}
	}
	else if (GetKeyboardPresse(DIK_S) == true)
	{
		if (GetKeyboardPresse(DIK_D) == true)
		{
			g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI * 1 / 4);
			g_camera.moveZ.z -= cosf(g_camera.rot.y + D3DX_PI * 1 / 4);
		}
		else if (GetKeyboardPresse(DIK_A) == true)
		{
			g_camera.moveX.x -= sinf(g_camera.rot.y + D3DX_PI * 3 / 4);
			g_camera.moveZ.z += cosf(g_camera.rot.y + D3DX_PI * 3 / 4);
		}
		else
		{
			g_camera.moveX.x -= (sinf(g_camera.rot.y + D3DX_PI));
			g_camera.moveZ.z += (cosf(g_camera.rot.y - D3DX_PI));
		}
	}
	else if (GetKeyboardPresse(DIK_A) == true)
	{// ���ړ��E�E�ړ�
		g_camera.moveX.x -= sinf(g_camera.rot.y + D3DX_PI / 2);
		g_camera.moveZ.z += cosf(g_camera.rot.y + D3DX_PI / 2);
	}
	else if (GetKeyboardPresse(DIK_D) == true)
	{
		g_camera.moveX.x += sinf(g_camera.rot.y + D3DX_PI / 2);
		g_camera.moveZ.z -= cosf(g_camera.rot.y + D3DX_PI / 2);
	}

	/*�����_�̑���*/
	//// �E����E������
	//if (GetKeyboardPresse(DIK_Q) == true)
	//{
	//	g_camera.rot.y += 0.02f;
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI*2.0f;
	//	}
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y + D3DX_PI) * 150.0f;
	//	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y - D3DX_PI) * 150.0f;
	//}
	//if (GetKeyboardPresse(DIK_E) == true)
	//{
	//	g_camera.rot.y -= 0.02f;
	//	if (g_camera.rot.y < (-D3DX_PI))
	//	{
	//		g_camera.rot.y += D3DX_PI*2.0f;
	//	}
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y + D3DX_PI) * 150.0f;
	//	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y - D3DX_PI) * 150.0f;
	//}

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
		3000.0f);										// ���̋���

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
