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
#include "fade.h"
#include "collision.h"
#include "shadow.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(2.3f)		// ���f���̃X�s�[�h
#define MAX_SIZE_MEMORY		(4000)		// �������̃T�C�Y
#define MOB_SIZE			(10)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Rock g_Mob[MOB_MAX];							// �v���C���[�i���f���j�̍\����
Rock *g_pMob;									// �v���C���[�i���f���j�̍\����


//=====================================================================================================================================================================//
// �v���g�^�C�v�錾
//=====================================================================================================================================================================//
void SummonMob(void);
void SetMob(void);
void FileLoadMob(void);


//==================================================================================================================================================================//
// ����������
//==================================================================================================================================================================//
void InitMob(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Rock *pMoblayer = &g_Mob[0];

	/* ���f�� */
	for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
	{
		/* No.0 �� */
		pMoblayer->pos = D3DXVECTOR3(0.0f + (nNumCnt * 50) , 100.0f, 0.0f);
		pMoblayer->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->pMesh = NULL;
		pMoblayer->pBuffMat = NULL;
		pMoblayer->pTexture = NULL;
		pMoblayer->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->bUse = false;
		pMoblayer->nNumShadow = 1;
		pMoblayer->nNumModel = 1;
		pMoblayer->nCuntDown = 15;
		pMoblayer->nCuntUp = 0;
		pMoblayer->nlife = 3;

		// �t�@�C���̓ǂݍ���
		/* No.0 �� */
		D3DXLoadMeshFromX("data\\MODEL\\rock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pMoblayer->pBuffMat, NULL, &pMoblayer->NumMat, &pMoblayer->pMesh);

		pMoblayer->pMat = (D3DXMATERIAL*)pMoblayer->pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pMoblayer->NumMat; nCntMat++)
		{
			if (pMoblayer->pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, pMoblayer->pMat[nCntMat].pTextureFilename, &pMoblayer->pTexture);
			}
		}

		/* ���f���̒��_��񔲂��o�� */
		int nNumVtx;													// ���_��
		DWORD sizeFVF;													// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^
		float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;		// �ŏ��l�ۊǗp
		float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;		// �ő�l�ۊǗp

		// ���_�����擾
		nNumVtx = pMoblayer->pMesh->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(pMoblayer->pMesh->GetFVF());
		// ���_�o�b�t�@�����b�N
		pMoblayer->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��
														// �ő�l�E�ŏ��l�̑������
			if (Vtx.x < MinMob_X)
			{/* �ŏ��l */
				MinMob_X = Vtx.x;
				pMoblayer->g_VtxMinMob.x = MinMob_X;
			}
			if (Vtx.y < MinMob_Y)
			{
				MinMob_Y = Vtx.y;
				pMoblayer->g_VtxMinMob.y = MinMob_Y;
			}
			if (Vtx.z < MinMob_Z)
			{
				MinMob_Z = Vtx.z;
				pMoblayer->g_VtxMinMob.z = MinMob_Z;
			}

			if (Vtx.x > MaxMob_X)
			{/* �ő�l */
				MaxMob_X = Vtx.x;
				pMoblayer->g_VtxMaxMob.x = MaxMob_X;
			}
			if (Vtx.y > MaxMob_Y)
			{
				MaxMob_Y = Vtx.y;
				pMoblayer->g_VtxMinMob.y = MaxMob_Y;
			}
			if (Vtx.z > MaxMob_Z)
			{
				MaxMob_Z = Vtx.z;
				pMoblayer->g_VtxMaxMob.z = MaxMob_Z;
			}
			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@�̃A�����b�N
		pMoblayer->pMesh->UnlockVertexBuffer();
	}
}

//==================================================================================================================================================================//
// �I������
//==================================================================================================================================================================//
void UninitMob(void)
{
	Rock *pMoblayer = &g_Mob[0];
	for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
	{
			if (pMoblayer->pMesh != NULL)
			{// ���b�V���̔j��
				pMoblayer->pMesh->Release();
				pMoblayer->pMesh = NULL;
			}
			if (pMoblayer->pBuffMat != NULL)
			{// �}�e���A���̔j��
				pMoblayer->pBuffMat->Release();
				pMoblayer->pBuffMat = NULL;
			}
			if (pMoblayer->pTexture != NULL)
			{
				pMoblayer->pTexture->Release();
				pMoblayer->pTexture = NULL;
			}
	}
}

//==================================================================================================================================================================//
// �X�V����
//==================================================================================================================================================================//
void UpdateMob(void)
{
	Rock *pMoblayer = &g_Mob[0];


	SummonMob();
	for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
	{
		if (pMoblayer->bUse == true)
		{
			pMoblayer->oldpos = pMoblayer->pos;

			// �ʒu�̍X�V
			pMoblayer->pos.z += pMoblayer->move.z;
			pMoblayer->pos.x += pMoblayer->move.x;
			pMoblayer->pos.y += pMoblayer->move.y;

		}
	}
}

//==================================================================================================================================================================//
// �`�揈��
//==================================================================================================================================================================//
void DrawMob(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	Rock *pMoblayer = &g_Mob[0];

		D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

		for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
		{
			if (pMoblayer->bUse == true)
			{
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

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)pMoblayer->pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)pMoblayer->NumMat; nCntMat++)
				{
					// �e���f���p�[�c�̕`��
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, pMoblayer->pTexture);
					// ���f���̕`��
					pMoblayer->pMesh->DrawSubset(nCntMat);
				}
				// �ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
}


//==================================================================================================================================================================//
// ���u�̏���
//==================================================================================================================================================================//
void SummonMob(void)
{
	Rock *pMoblayer = &g_Mob[0];


	for (int nCntMob = 0; nCntMob < MOB_MAX; nCntMob++,pMoblayer++)
	{

		if (pMoblayer->bUse == false)
		{
			pMoblayer->nCuntUp++;	// �J�E���g�X�^�[�g

			if ((pMoblayer->nCuntUp % (20 * nCntMob + 1)) == 0)
			{
				pMoblayer->nCuntDown--;
				if (pMoblayer->nCuntDown == 0)
				{
					// �ړ��̐ݒ�
					float fAngle = (float)((rand() % 628) - 628) / 100.f;
					pMoblayer->move.z = cosf(fAngle + D3DX_PI) * 5.0f;
					pMoblayer->move.x = sinf(fAngle - D3DX_PI) * 5.0f;
					pMoblayer->bUse = true;
					break;

				}
			}
		}
	}
}

//==================================================================================================================================================================//
// ���u�̐ݒu
//==================================================================================================================================================================//
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
Rock *GetRock(void)
{
	return &g_Mob[0];
}