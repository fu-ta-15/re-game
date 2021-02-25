//##################################################################################################################################################################//
//																																									//
// ���f������ [model.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "model.h"
#include "keyinput.h"
#include "camera.h"
#include "shadow.h"
#include "memory.h"
#include "effect.h"
#include "Dinput.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.5f)		// ���f���̃X�s�[�h
#define MAX_SIZE_MEMORY		(4000)		// �������̃T�C�Y


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Player g_Player;							// �v���C���[�i���f���j�̍\����


//==================================================================================================================================================================//
// ����������
//==================================================================================================================================================================//
void InitModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	/* ���f�� */

	/* No.0 �� */
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].pMesh = NULL;
	g_Player.aModel[0].pBuffMat = NULL;
	g_Player.aModel[0].nIdxModelParent = -1;

	/* No.1 �� */
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].pMesh = NULL;
	g_Player.aModel[1].pBuffMat = NULL;
	g_Player.aModel[1].nIdxModelParent = 0;

	/* �v���C���[ */
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nNumShadow = 1;
	g_Player.nNumModel = 2;

	/* ���[�V���� */
	g_Player.nNumMotion = 2;
	g_Player.nNumKey = 2;
	g_Player.nKey_No = 0;
	g_Player.nCounterMotion = 0;
	g_Player.bLoopMotion = false;
	/* ���[�V������� */
	g_Player.aMotionInfo[0].nNumKey = 2;
	g_Player.aMotionInfo[0].bLoop = false;
	/* �L�[��� */
	/* �j���[�g�����@�L�[�P */
	g_Player.aMotionInfo[0].aKeyInfo[0].nFrame = 50;
	/* No.0 �� */
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_Y = 0.5f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_Z = 0.0f;

	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_Y = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_Z = 0.0f;
	/* No.1 �� */
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_Y = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_Z = 0.0f;

	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_Y = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_Z = 0.0f;

	/* �j���[�g�����@�L�[�Q */
	g_Player.aMotionInfo[0].aKeyInfo[1].nFrame = 50;
	/* No.0 �� */
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_Y = -0.5f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_Z = 0.0f;

	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_Y = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_Z = 0.0f;
	/* No.1 �� */
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_Y = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_Z = 0.0f;

	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_X = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_Y = 0.0f;
	g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_Z = 0.0f;

	// �t�@�C���̓ǂݍ���
	/* No.0 �� */
	D3DXLoadMeshFromX("data\\suzuki_model\\body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].NumMat, &g_Player.aModel[0].pMesh);
	/* No.1 �� */
	D3DXLoadMeshFromX("data\\suzuki_model\\hed.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].NumMat, &g_Player.aModel[1].pMesh);
	// �e�̐ݒ�
	g_Player.nNumShadow = SetShadow(g_Player.pos, 10.0f, 10.0f);

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
// �I������
//==================================================================================================================================================================//
void UninitModel(void)
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
void UpdateModel(void)
{
	// �J�����̃|�C���^
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeypadTrigger(D_BUUTON_Y) == true)
	{// SPACE��������
		g_Player.move.x += (g_Player.move.x) * 2.3f;
		g_Player.move.z += (g_Player.move.z) * 2.3f;
	}

	// ���f���̈ړ�
	MoveModel();

	// ���f���̃��[�V����
	MotionModel();

	// �ʒu�̍X�V
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// �ړI��]����
	if ((g_Player.rotDest.y - g_Player.rot.y) > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if ((g_Player.rotDest.y - g_Player.rot.y) < (-D3DX_PI))
	{
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}

	// �����Ă����
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	// ��]����
	if (g_Player.rot.y < (-D3DX_PI))
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}

	// �ړ��E��]�ʂ̌���
	g_Player.move.x += (0 - g_Player.move.x) * 0.08f;
	g_Player.move.y += (0 - g_Player.move.y) * 0.15f;
	g_Player.move.z += (0 - g_Player.move.z) * 0.08f;

	// �e�̐ݒ�
	SetPositionShadow(g_Player.nNumShadow, g_Player.pos);
}

//==================================================================================================================================================================//
// �`�揈��
//==================================================================================================================================================================//
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

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
			// �e���f���p�[�c�̕`��
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���f���̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================================================================================//
// ���f���̈ړ�
//==================================================================================================================================================================//
void MoveModel(void)
{
	Camera *pCamera = GetCamera();
	bool *pPad = GetPadPlress();


	/*���f������*/
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
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
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
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_RIGHT) == true)
	{// �E�ړ��E���ړ�
		g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 + pCamera->rot.y ;
	}
	else if (GetKeyboardPresse(DIK_LEFT) == true)
	{
		g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;
	}

	// ��ړ��E���ړ�
	if (GetKeyboardPresse(DIK_O) == true || GetKeypadPresse(D_BUUTON_RT) == true)
	{
		g_Player.move.y += 0.06f;
	}
	if (GetKeyboardPresse(DIK_L) == true || GetKeypadPresse(D_BUUTON_LT) == true)
	{
		g_Player.move.y -= 0.06f;
	}

	DIJOYSTATE2 *pController = pGetPadCont();					// �R���g���[���[���̃|�C���^

	if (pController->lX != 0 || pController->lY != 0)
	{// �X�e�B�b�N���X������
		// �X�e�B�b�N�̌X���Ă���ʒu
		float fAngle = atan2f((float)pController->lX, -(float)pController->lY);

		g_Player.move.x += sinf((D3DX_PI + fAngle) - pCamera->rot.y) * 0.5f;			// X���ړ��ʂ̌���
		g_Player.move.z += cosf((D3DX_PI + fAngle) - pCamera->rot.y) * 0.5f;			// Z���ړ��ʂ̌���

		g_Player.rotDest.y = fAngle - pCamera->rot.y;
	}

}

//==================================================================================================================================================================//
// ���[�V�����Ǘ�
//==================================================================================================================================================================//
void MotionModel(void)
{
		// ���̃L�[
		int NextKey;

		// ���݂̃L�[���L�[�̑����𒴂�����
		if ((g_Player.nKey_No + 1) > g_Player.aMotionInfo[0].nNumKey)
		{
			NextKey = 0;
		}
		else
		{
			NextKey = g_Player.nKey_No + 1;
		}

		// ���[�V�����J�E���^�[�J�n
		g_Player.nCounterMotion++;

		if (g_Player.nCounterMotion > g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame)
		{
			g_Player.nCounterMotion = 0;
			g_Player.nKey_No++;
			if (g_Player.nKey_No > g_Player.aMotionInfo[0].nNumKey)
			{
				g_Player.nKey_No = 0;
			}
		}

		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aModel[nCntModel].pos.x += g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_X + (g_Player.aMotionInfo[0].aKeyInfo[NextKey].aKey[nCntModel].Pos_X - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_X) * (g_Player.nCounterMotion / g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].pos.y += g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Y + (g_Player.aMotionInfo[0].aKeyInfo[NextKey].aKey[nCntModel].Pos_Y - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Y) * (g_Player.nCounterMotion / g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].pos.z += g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Z + (g_Player.aMotionInfo[0].aKeyInfo[NextKey].aKey[nCntModel].Pos_Z - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Pos_Z) * (g_Player.nCounterMotion / g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);

			g_Player.aModel[nCntModel].rot.x += g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_X + (g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_X - g_Player.aMotionInfo[0].aKeyInfo[NextKey].aKey[nCntModel].Rot_X) * (g_Player.nCounterMotion / g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].rot.y += g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Y + (g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Y - g_Player.aMotionInfo[0].aKeyInfo[NextKey].aKey[nCntModel].Rot_Y) * (g_Player.nCounterMotion / g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
			g_Player.aModel[nCntModel].rot.z += g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Z + (g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nCntModel].Rot_Z - g_Player.aMotionInfo[0].aKeyInfo[NextKey].aKey[nCntModel].Rot_Z) * (g_Player.nCounterMotion / g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
		}
	
}


//==================================================================================================================================================================//
// �e�L�X�g�̓ǂݍ���
//==================================================================================================================================================================//
void FileLoad(void)
{
	// ������̃|�C���g
	char *str;
	// ������̒���
	int length = 1000;

	// �������m��
	str = (char*)malloc(sizeof(char) * length);

	memset(str, 0, sizeof(char) * 1000);

	if (!str)
	{// �������m�ۂɎ��s
		printf("%s", "\n�������m�ۂɎ��s");
		exit(0);
	}


}



//==================================================================================================================================================================//
// �v���C���[�̏��
//==================================================================================================================================================================//
Player * GetPlayer(void)
{
	return &g_Player;
}