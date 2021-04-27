//##################################################################################################################################################################//
//																																									//
// �v���C���[���� [player.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "player.h"
#include "keyinput.h"
#include "camera.h"
#include "shadow.h"
#include "memory.h"
#include "effect.h"
#include "Dinput.h"
#include "light.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.5f)					// ���f���̃X�s�[�h
#define MAX_SIZE_MEMORY		(1000)					// �������̃T�C�Y
#define PI_TWICE			(D3DX_PI * 2.0f)	
#define SPEED_CONTROL		(0.08f)
#define NEXT_KEY			(g_Player.nKey_No + 1)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Player g_Player;	// �v���C���[�i���f���j�̍\����
MOTION_TYPE g_MotionType = MOTION_TYPE_NOMAL;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �v���g�^�C�v�錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void MovePlayerKey(void);
void MovePlayerPad(void);
void MotionPlayer(MOTION_TYPE type);
void RotControlPlayer(void);
void SetMotionPlayer(void);
void SetPlayerModel(void);
void GetVtxPlayer(void);

//==================================================================================================================================================================//
// ����������
//==================================================================================================================================================================//
void InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	SetPlayerModel();

	/* �v���C���[ */
	g_Player.pos = VECTOR_ZERO;
	g_Player.rot = VECTOR_ZERO;
	g_Player.move = VECTOR_ZERO;
	g_Player.rotDest = VECTOR_ZERO;
	g_Player.nNumShadow = 1;
	g_Player.nNumModel = MODEL_MAX;

	// �e�̐ݒ�
	g_Player.nNumShadow = SetShadow(g_Player.pos, 10.0f, 10.0f);

	/* ���[�V���� */
	g_Player.nKey_No = 0;
	g_Player.nCounterMotion = 0;
	g_Player.bLoopMotion = false;

	// ���[�V�����̐ݒ�
	SetMotionPlayer();

	// �t�@�C���̓ǂݍ���
	/* No.0 �� */
	D3DXLoadMeshFromX("data\\suzuki_model\\body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].NumMat, &g_Player.aModel[0].pMesh);
	
	/* No.1 �� */
	D3DXLoadMeshFromX("data\\suzuki_model\\hed.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].NumMat, &g_Player.aModel[1].pMesh);
	
	// �p�[�c�̒��_���W�擾
	GetVtxPlayer();
}

//==================================================================================================================================================================//
// �I������
//==================================================================================================================================================================//
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{// ���b�V���̔j��
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{// �}�e���A���̔j��
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//==================================================================================================================================================================//
// �X�V����
//==================================================================================================================================================================//
void UpdatePlayer(void)
{
	// �J�����̃|�C���^
	Camera *pCamera = GetCamera();

	// ���f���̈ړ�
	MovePlayerPad();   // �p�b�h

	MovePlayerKey();   // �L�[�{�[�h

	// ���f���̃��[�V����
	MotionPlayer(g_MotionType);

	// �ʒu�̍X�V
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// ��]�̐���
	RotControlPlayer();

	// �ړ��E��]�ʂ̌���
	g_Player.move.x += (0 - g_Player.move.x) * SPEED_CONTROL;
	g_Player.move.y += (0 - g_Player.move.y) * SPEED_CONTROL;
	g_Player.move.z += (0 - g_Player.move.z) * SPEED_CONTROL;

	// �e�̐ݒ�
	SetPositionShadow(g_Player.nNumShadow, g_Player.pos);
}

//==================================================================================================================================================================//
// �`�揈��
//==================================================================================================================================================================//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxShadow;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, nomal;
	D3DXPLANE plane;
	D3DLIGHT9 *pLight = &GetLight();

	VecLight = D3DXVECTOR4(pLight->Direction.x, -pLight->Direction.y, pLight->Direction.z, 0.0f);
	pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	nomal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	/* �v���C���[�i�����Ȃ����_�j�̐ݒ� */
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p
		D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// �e�p�[�c�̌���
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �e�p�[�c�̈ʒu
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{// �e�̃C���f�b�N�X��ݒ�
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{// �v���C���[�}�g���b�N�X��ݒ�
			mtxParent = g_Player.mtxWorld;
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
							&g_Player.aModel[nCntModel].mtxWorld,
							&mtxParent);


		// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_Player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f���̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}

		// �e�̕`��
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxShadow);
			D3DXPlaneFromPointNormal(&plane, &pos, &nomal);
			D3DXMatrixShadow(&mtxShadow, &VecLight, &plane);
			D3DXMatrixMultiply(&mtxShadow, &g_Player.aModel[nCntModel].mtxWorld, &mtxShadow);
			pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

			// ���f���̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================================================================================//
// ���f���̈ړ�(�L�[�{�[�h)
//==================================================================================================================================================================//
void MovePlayerKey(void)
{
	Camera *pCamera = GetCamera();

	/*���f������*/

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{// SPACE��������
		g_Player.move.x += (g_Player.move.x) * 2.3f;
		g_Player.move.z += (g_Player.move.z) * 2.3f;
	}

	// �O�ړ��E��ړ�
	if (GetKeyboardPresse(DIK_UP) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 4 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 4 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = 0.0f - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_DOWN) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0 / 4) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_RIGHT) == true)
	{// �E�ړ��E���ړ�
		g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 + pCamera->rot.y ;
	}
	else if (GetKeyboardPresse(DIK_LEFT) == true)
	{
		g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;
	}

	if (GetKeyboardPresse(DIK_LEFT) == true || GetKeyboardPresse(DIK_RIGHT) == true || GetKeyboardPresse(DIK_DOWN) == true || GetKeyboardPresse(DIK_UP) == true) g_MotionType = MOTION_TYPE_MOVE;
	else g_MotionType = MOTION_TYPE_NOMAL;
}

//==================================================================================================================================================================//
// ���f���̈ړ�(�p�b�h)
//==================================================================================================================================================================//
void MovePlayerPad(void)
{
	// �J�����̃|�C���^
	Camera *pCamera = GetCamera();

	if (GetKeypadTrigger(D_BUUTON_Y) == true)
	{// SPACE��������
		g_Player.move.x += (g_Player.move.x) * 2.3f;
		g_Player.move.z += (g_Player.move.z) * 2.3f;
	}

	// ��ړ��E���ړ�
	if (GetKeypadPresse(D_BUUTON_RT) == true)
	{
		g_Player.move.y += MODEL_SPEED;
	}
	if (GetKeypadPresse(D_BUUTON_LT) == true)
	{
		g_Player.move.y -= MODEL_SPEED;
	}

	DIJOYSTATE2 *pController = pGetPadCont();					// �R���g���[���[���̃|�C���^

	if (pController->lX != 0 || pController->lY != 0)
	{// �X�e�B�b�N���X������
	 // �X�e�B�b�N�̌X���Ă���ʒu
		float fAngle = atan2f((float)pController->lX, -(float)pController->lY);

		g_Player.move.x += sinf((D3DX_PI + fAngle) - pCamera->rot.y) * MODEL_SPEED;			// X���ړ��ʂ̌���
		g_Player.move.z += cosf((D3DX_PI + fAngle) - pCamera->rot.y) * MODEL_SPEED;			// Z���ړ��ʂ̌���

		g_Player.rotDest.y = fAngle - pCamera->rot.y;

		// ���[�V�������
		g_MotionType = MOTION_TYPE_MOVE;
	}
	else g_MotionType = MOTION_TYPE_NOMAL;
}

//==================================================================================================================================================================//
// ���[�V�����Ǘ�
//==================================================================================================================================================================//
void MotionPlayer(MOTION_TYPE type)
{
	if (type == MOTION_TYPE_NOMAL)
	{
		// ���̃L�[
		int NextKey;

		// ���݂̃L�[���L�[�̑����𒴂�����
		if ((g_Player.nKey_No + 1) > g_Player.aMotionInfo[type].nNumKey)
		{
			NextKey = 0;
		}
		else
		{
			NextKey = NEXT_KEY;
		}

		// ���[�V�����J�E���^�[�J�n
		g_Player.nCounterMotion++;

		if (g_Player.nCounterMotion > g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame)
		{// ���[�V�����J�E���^�[�����̃L�[�̃t���[�����傫���Ȃ�����

			g_Player.nCounterMotion = 0;	// �J�E���^�[������������
			g_Player.nKey_No++;				// �L�[������

			if (g_Player.nKey_No + 1 > g_Player.aMotionInfo[type].nNumKey && g_Player.aMotionInfo[type].bLoop == true)
			{// ���݂̃L�[�̃i���o�[�����̃��[�V�����̃L�[���𒴂����ꍇ
				g_Player.nKey_No = 0;	// �L�[�̏�����
			}
		}

		// ���[�V�����̍X�V
		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aModel[nCntModel].pos.x += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_X + (g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Pos_X - g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_X) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].pos.y += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Y + (g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Pos_Y - g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Y) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].pos.z += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Z + (g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Pos_Z - g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Z) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);

			g_Player.aModel[nCntModel].rot.x += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_X + (g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_X - g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Rot_X) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].rot.y += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Y + (g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Y - g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Rot_Y) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].rot.z += g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Z + (g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Z - g_Player.aMotionInfo[type].aKeyInfo[NextKey].aKey[nCntModel].Rot_Z) * (g_Player.nCounterMotion / g_Player.aMotionInfo[type].aKeyInfo[g_Player.nKey_No].nFrame);
		}
	}
}

//==================================================================================================================================================================//
// �p�x����
//==================================================================================================================================================================//
void RotControlPlayer(void)
{
	// �ړI��]����
	if ((g_Player.rotDest.y - g_Player.rot.y) > D3DX_PI)
	{
		g_Player.rotDest.y -= PI_TWICE;
	}
	if ((g_Player.rotDest.y - g_Player.rot.y) < (-D3DX_PI))
	{
		g_Player.rotDest.y += PI_TWICE;
	}

	// �����Ă����
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	// ��]����
	if (g_Player.rot.y < (-D3DX_PI))
	{
		g_Player.rot.y += PI_TWICE;
	}
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= PI_TWICE;
	}
}

//==================================================================================================================================================================//
// ���[�V�����̐ݒ�
//==================================================================================================================================================================//
void SetMotionPlayer(void)
{
	/* ���[�V������� */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].nNumKey = 2;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].bLoop = true;

	/* �L�[��� */
	/* �j���[�g�����@�L�[�P */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].nFrame = 50;

	/* No.0 �� */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Pos_Y = 0.5f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[0].Rot_Z = 0.0f;

	/* No.1 �� */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Pos_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[0].aKey[1].Rot_Z = 0.0f;

	/* �j���[�g�����@�L�[�Q */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].nFrame = 50;

	/* No.0 �� */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Pos_Y = -0.5f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[0].Rot_Z = 0.0f;

	/* No.1 �� */
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Pos_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Pos_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Pos_Z = 0.0f;

	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Rot_X = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Rot_Y = 0.0f;
	g_Player.aMotionInfo[MOTION_TYPE_NOMAL].aKeyInfo[1].aKey[1].Rot_Z = 0.0f;
}

//==================================================================================================================================================================//
// ���f���p�[�c�̈ʒu�ݒ�
//==================================================================================================================================================================//
void SetPlayerModel(void)
{
	/* ���f�� */
	/* No.0 �� */
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].pMesh = NULL;
	g_Player.aModel[0].NumMat = NULL;
	g_Player.aModel[0].pBuffMat = NULL;
	g_Player.aModel[0].nIdxModelParent = -1;

	/* No.1 �� */
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].pMesh = NULL;
	g_Player.aModel[1].NumMat = NULL;
	g_Player.aModel[1].pBuffMat = NULL;
	g_Player.aModel[1].nIdxModelParent = 0;
}

//==================================================================================================================================================================//
// ���f���̒��_���W�̎擾
//==================================================================================================================================================================//
void GetVtxPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{

		/* ���f���̒��_��񔲂��o�� */
		int nNumVtx;								// ���_��
		DWORD sizeFVF;								// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;								// ���_�o�b�t�@�ւ̃|�C���^
		float MinModel_X = 0.0f, MinModel_Z = 0.0f, MinModel_Y = 0.0f;	// �ŏ��l�ۊǗp
		float MaxModel_X = 0.0f, MaxModel_Z = 0.0f, MaxModel_Y = 0.0f;	// �ő�l�ۊǗp

																		// ���_�����擾
		nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());
		// ���_�o�b�t�@�����b�N
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

			/* �ŏ��l */
			if (Vtx.x < MinModel_X)
			{// X���W
				MinModel_X = Vtx.x;
				g_Player.aModel[nCntModel].g_VtxMinModel.x = MinModel_X;
			}
			if (Vtx.y < MinModel_Y)
			{// Y���W
				MinModel_Y = Vtx.y;
				g_Player.aModel[nCntModel].g_VtxMinModel.y = MinModel_Y;
			}
			if (Vtx.z < MinModel_Z)
			{// Z���W
				MinModel_Z = Vtx.z;
				g_Player.aModel[nCntModel].g_VtxMinModel.z = MinModel_Z;
			}

			/* �ő�l */
			if (Vtx.x > MaxModel_X)
			{// X���W
				MaxModel_X = Vtx.x;
				g_Player.aModel[nCntModel].g_VtxMaxModel.x = MaxModel_X;
			}
			if (Vtx.y > MaxModel_Y)
			{// Y���W
				MaxModel_Y = Vtx.y;
				g_Player.aModel[nCntModel].g_VtxMaxModel.y = MaxModel_Y;
			}
			if (Vtx.z > MaxModel_Z)
			{// Z���W
				MaxModel_Z = Vtx.z;
				g_Player.aModel[nCntModel].g_VtxMaxModel.z = MaxModel_Z;
			}
			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@�̃A�����b�N
		g_Player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

}

//==================================================================================================================================================================//
// �v���C���[�̏��
//==================================================================================================================================================================//
Player * GetPlayer(void)
{
	return &g_Player;
}