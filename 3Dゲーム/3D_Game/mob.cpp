//##################################################################################################################################################################//
//																																									//
// ���f������ [model.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "keyinput.h"
#include "effect.h"
#include "mob.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.3f)		// ���f���̃X�s�[�h
#define MAX_SIZE_MEMORY		(4000)		// �������̃T�C�Y
#define MOB_SIZE			(10)



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Moblayer g_Mob;							// �v���C���[�i���f���j�̍\����


//==================================================================================================================================================================//
// ����������
//==================================================================================================================================================================//
void InitMob(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Moblayer *pMoblayer = &g_Mob;

	/* ���f�� */
		/* No.0 �� */
	pMoblayer->aModel[0].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
	pMoblayer->aModel[0].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->aModel[0].pMesh = NULL;
	pMoblayer->aModel[0].pBuffMat = NULL;
	pMoblayer->aModel[0].pTexture = NULL;
	pMoblayer->aModel[0].nIdxModelParent = -1;

		/* �v���C���[ */
	pMoblayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->bUse = true;
	pMoblayer->nNumShadow = 1;
	pMoblayer->nNumModel = 1;
	pMoblayer->nCuntDown = 120;
	pMoblayer->nCuntUp = 0;
	pMoblayer->nlife = 3;


	// �t�@�C���̓ǂݍ���
	/* No.0 �� */
	D3DXLoadMeshFromX("data\\MODEL\\rock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pMoblayer->aModel[0].pBuffMat, NULL, &pMoblayer->aModel[0].NumMat, &pMoblayer->aModel[0].pMesh);

	pMoblayer->aModel[0].pMat = (D3DXMATERIAL*)pMoblayer->aModel[0].pBuffMat->GetBufferPointer();
	
	for (int nCntMat = 0; nCntMat < (int)pMoblayer->aModel[0].NumMat; nCntMat++)
	{
		if (pMoblayer->aModel[0].pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMoblayer->aModel[0].pMat[nCntMat].pTextureFilename, &pMoblayer->aModel[0].pTexture);
		}
	}

	//g_Mob.nNumShadow = SetShadow(g_Mob.pos, 10.0f, 10.0f);

		/* ���f���̒��_��񔲂��o�� */
		int nNumVtx;													// ���_��
		DWORD sizeFVF;													// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^
		float MinModel_X = 0.0f, MinModel_Z = 0.0f, MinMob_Y = 0.0f;	// �ŏ��l�ۊǗp
		float MaxModel_X = 0.0f, MaxModel_Z = 0.0f, MaxMob_Y = 0.0f;	// �ő�l�ۊǗp

		// ���_�����擾
		nNumVtx = g_Mob.aModel[0].pMesh->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Mob.aModel[0].pMesh->GetFVF());
		// ���_�o�b�t�@�����b�N
		g_Mob.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��
			// �ő�l�E�ŏ��l�̑������
			if (Vtx.x < MinModel_X)
			{/* �ŏ��l */
				MinModel_X = Vtx.x;
				g_Mob.aModel[0].g_VtxMinModel.x = MinModel_X;
			}
			if (Vtx.y < MinMob_Y)
			{
				MinMob_Y = Vtx.y;
				g_Mob.aModel[0].g_VtxMinModel.y = MinMob_Y;
			}
			if (Vtx.z < MinModel_Z)
			{
				MinModel_Z = Vtx.z;
				g_Mob.aModel[0].g_VtxMinModel.z = MinModel_Z;
			}
			if (Vtx.x > MaxModel_X)
			{/* �ő�l */
				MaxModel_X = Vtx.x;
				g_Mob.aModel[0].g_VtxMaxModel.x = MaxModel_X;
			}
			if (Vtx.y > MaxMob_Y)
			{
				MaxMob_Y = Vtx.y;
				g_Mob.aModel[0].g_VtxMinModel.y = MaxMob_Y;
			}
			if (Vtx.z > MaxModel_Z)
			{
				MaxModel_Z = Vtx.z;
				g_Mob.aModel[0].g_VtxMaxModel.z = MaxModel_Z;
			}
			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@�̃A�����b�N
		g_Mob.aModel[0].pMesh->UnlockVertexBuffer();
}

//==================================================================================================================================================================//
// �I������
//==================================================================================================================================================================//
void UninitMob(void)
{
		for (int nCntModel = 0; nCntModel < 1; nCntModel++)
		{
			if (g_Mob.aModel[nCntModel].pMesh != NULL)
			{// ���b�V���̔j��
				g_Mob.aModel[nCntModel].pMesh->Release();
				g_Mob.aModel[nCntModel].pMesh = NULL;
			}
			if (g_Mob.aModel[nCntModel].pBuffMat != NULL)
			{// �}�e���A���̔j��
				g_Mob.aModel[nCntModel].pBuffMat->Release();
				g_Mob.aModel[nCntModel].pBuffMat = NULL;
			}
			if (g_Mob.aModel[nCntModel].pTexture != NULL)
			{
				g_Mob.aModel[nCntModel].pTexture->Release();
				g_Mob.aModel[nCntModel].pTexture = NULL;
			}
		}
}

//==================================================================================================================================================================//
// �X�V����
//==================================================================================================================================================================//
void UpdateMob(void)
{
	// �e�̐ݒ�
	//SetPositionShadow(g_Mob.nNumShadow, g_Mob.pos);

	Moblayer *pMoblayer = &g_Mob;
	if (g_Mob.bUse == true)
	{

		pMoblayer->aModel[0].oldpos = pMoblayer->aModel[0].pos;

		// �ʒu�̍X�V
		pMoblayer->aModel[0].move.y -= 1.3f;
		pMoblayer->aModel[0].pos.z += pMoblayer->aModel[0].move.z;
		pMoblayer->aModel[0].pos.x += pMoblayer->aModel[0].move.x;
		pMoblayer->aModel[0].pos.y += pMoblayer->aModel[0].move.y;

		// �ړ��ʂ̌���
		pMoblayer->aModel[0].move.z += (0.0f - pMoblayer->aModel[0].move.z) * 0.4f;
		pMoblayer->aModel[0].move.x += (0.0f - pMoblayer->aModel[0].move.x) * 0.4f;
		pMoblayer->aModel[0].move.y += (0.0f - pMoblayer->aModel[0].move.y) * 0.013f;


		if (g_Mob.aModel[0].oldpos.y < 0 + g_Mob.aModel[0].g_VtxMinModel.y)
		{
			pMoblayer->aModel[0].pos.y = 0 + g_Mob.aModel[0].g_VtxMinModel.y;
			pMoblayer->aModel[0].move.y += 20.0f;
		}
	}
}

//==================================================================================================================================================================//
// �`�揈��
//==================================================================================================================================================================//
void DrawMob(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	Moblayer *pMoblayer = &g_Mob;

		D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

			D3DXMatrixIdentity(&pMoblayer->mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pMoblayer->rot.y, pMoblayer->rot.x, pMoblayer->rot.z);
			D3DXMatrixMultiply(&pMoblayer->mtxWorld, &pMoblayer->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pMoblayer->pos.x, pMoblayer->pos.y, pMoblayer->pos.z);
			D3DXMatrixMultiply(&pMoblayer->mtxWorld, &pMoblayer->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pMoblayer->mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_Mob.nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p
				D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

														// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&pMoblayer->aModel[nCntModel].mtxWorld);

				// �e�p�[�c�̌���
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, pMoblayer->aModel[nCntModel].rot.y, pMoblayer->aModel[nCntModel].rot.x, pMoblayer->aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&pMoblayer->aModel[nCntModel].mtxWorld, &pMoblayer->aModel[nCntModel].mtxWorld, &mtxRotModel);

				// �e�p�[�c�̈ʒu
				D3DXMatrixTranslation(&mtxTransModel, pMoblayer->aModel[nCntModel].pos.x, pMoblayer->aModel[nCntModel].pos.y, pMoblayer->aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&pMoblayer->aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxTransModel);

				// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
				if (pMoblayer->aModel[nCntModel].nIdxModelParent != -1)
				{// �e�̃C���f�b�N�X��ݒ�
					mtxParent = pMoblayer->aModel[pMoblayer->aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{// �v���C���[�}�g���b�N�X��ݒ�
					mtxParent = pMoblayer->mtxWorld;
				}

				// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&pMoblayer->aModel[nCntModel].mtxWorld,
					&pMoblayer->aModel[nCntModel].mtxWorld,
					&mtxParent);
				// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD,
					&pMoblayer->aModel[nCntModel].mtxWorld);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)pMoblayer->aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)pMoblayer->aModel[nCntModel].NumMat; nCntMat++)
				{
					// �e���f���p�[�c�̕`��
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, pMoblayer->aModel[0].pTexture);
					// ���f���̕`��
					pMoblayer->aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}
		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
}

void SetMob(void)
{



}


//==================================================================================================================================================================//
// �e�L�X�g�̓ǂݍ���
//==================================================================================================================================================================//
void FileLoadMob(void)
{
	// ������̃|�C���g
	char *str;
	// ������̒���
	int length = 1000;
	// �t�@�C��
	FILE *fMob;
	char *fName = "Mobs.txt";

	// �������m��
	str = (char*)malloc(sizeof(char) * length);

	memset(str, 0, sizeof(char) * length);

	if (!str)
	{// �������m�ۂɎ��s
		printf("%s", "\n�������m�ۂɎ��s");
		exit(0);
	}

	fMob = fopen(fName, "r");
	if (fMob == NULL)
	{
		printf("%s�t�@�C�����J���܂���ł���", fName);
	}
	else
	{
		while (fgets(str, length, fMob) != NULL);
	}
	fclose(fMob);
	free(str);
}



//==================================================================================================================================================================//
// �v���C���[�̏��
//==================================================================================================================================================================//
Moblayer *GetMoblayer(void)
{
	return &g_Mob;
}