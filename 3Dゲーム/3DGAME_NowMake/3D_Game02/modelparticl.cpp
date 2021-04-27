//##################################################################################################################################################################//
//																																									//
// ���f���p�[�e�B�N������ [modelparticl.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "keyinput.h"
#include "collision.h"
#include "shadow.h"
#include "modelparticl.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(2.3f)		// ���f���̃X�s�[�h
#define MAX_SIZE_MEMORY		(4000)		// �������̃T�C�Y
#define MOB_SIZE			(10)
#define MPT_MAX				(500)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
ModelParticl g_MPT[MPT_MAX];							// �v���C���[�i���f���j�̍\����

LPD3DXMESH g_pMeshMPT;				// ���b�V���ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatMPT;			// �}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMPT;	// �e�N�X�`���ւ̃|�C���^
D3DXMATERIAL *g_pMatMPT;				// �}�e���A���̃|�C���^
DWORD g_NumMatMPT;					// �}�e���A���̐�




//==================================================================================================================================================================//
// ����������
//==================================================================================================================================================================//
void InitModelP(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ModelParticl *pMPT = &g_MPT[0];

	/* ���f�� */
	for (int nNumCnt = 0; nNumCnt < MPT_MAX; nNumCnt++, pMPT++)
	{
		/* No.0 �� */
		pMPT->pos = D3DXVECTOR3(0.0f + (nNumCnt * 50), 100.0f, 0.0f);
		pMPT->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->bUse = false;
		pMPT->nNumShadow = 1;
		pMPT->nNumModel = 1;
		pMPT->nCuntDown = 15;
		pMPT->nCuntUp = 0;
		pMPT->nlife = 3;
	}
	// �t�@�C���̓ǂݍ���
	/* No.0 �������� */
	D3DXLoadMeshFromX("data\\MODEL\\rockmini.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatMPT, NULL, &g_NumMatMPT, &g_pMeshMPT);

	g_pMatMPT = (D3DXMATERIAL*)g_pBuffMatMPT->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_NumMatMPT; nCntMat++)
	{
		if (g_pMatMPT->pTextureFilename != NULL)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, g_pMatMPT->pTextureFilename, &g_pTextureMPT);
		}
	}

	//g_Mob.nNumShadow = SetShadow(g_Mob.pos, 10.0f, 10.0f);

	/* ���f���̒��_��񔲂��o�� */
	int nNumVtx;													// ���_��
	DWORD sizeFVF;													// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^
	float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;	// �ŏ��l�ۊǗp
	float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;	// �ő�l�ۊǗp

																// ���_�����擾
	nNumVtx = g_pMeshMPT->GetNumVertices();
	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshMPT->GetFVF());
	// ���_�o�b�t�@�����b�N
	g_pMeshMPT->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��
													// �ő�l�E�ŏ��l�̑������
		if (Vtx.x < MinMob_X)
		{/* �ŏ��l */
			MinMob_X = Vtx.x;
			pMPT->g_VtxMinMob.x = MinMob_X;
		}
		if (Vtx.y < MinMob_Y)
		{
			MinMob_Y = Vtx.y;
			pMPT->g_VtxMinMob.y = MinMob_Y;
		}
		if (Vtx.z < MinMob_Z)
		{
			MinMob_Z = Vtx.z;
			pMPT->g_VtxMinMob.z = MinMob_Z;
		}

		if (Vtx.x > MaxMob_X)
		{/* �ő�l */
			MaxMob_X = Vtx.x;
			pMPT->g_VtxMaxMob.x = MaxMob_X;
		}
		if (Vtx.y > MaxMob_Y)
		{
			MaxMob_Y = Vtx.y;
			pMPT->g_VtxMinMob.y = MaxMob_Y;
		}
		if (Vtx.z > MaxMob_Z)
		{
			MaxMob_Z = Vtx.z;
			pMPT->g_VtxMaxMob.z = MaxMob_Z;
		}
		pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pMeshMPT->UnlockVertexBuffer();
}

//==================================================================================================================================================================//
// �I������
//==================================================================================================================================================================//
void UninitModelP(void)
{
	if (g_pMeshMPT != NULL)
	{// ���b�V���̔j��
		g_pMeshMPT->Release();
		g_pMeshMPT = NULL;
	}
	if (g_pBuffMatMPT != NULL)
	{// �}�e���A���̔j��
		g_pBuffMatMPT->Release();
		g_pBuffMatMPT = NULL;
	}
	if (g_pTextureMPT != NULL)
	{
		g_pTextureMPT->Release();
		g_pTextureMPT = NULL;
	}
}

//==================================================================================================================================================================//
// �X�V����
//==================================================================================================================================================================//
void UpdateModelP(void)
{
	ModelParticl *pMPT = &g_MPT[0];

	for (int nNumCnt = 0; nNumCnt < MPT_MAX; nNumCnt++, pMPT++)
	{
		if (pMPT->bUse == true)
		{
			pMPT->oldpos = pMPT->pos;

			// �ʒu�̍X�V
			pMPT->move.y -= 0.1f;
			pMPT->pos.z += pMPT->move.z;
			pMPT->pos.x += pMPT->move.x;
			pMPT->pos.y += pMPT->move.y;


			// �ړ��ʂ̌���
			pMPT->move.z += (0.0f - pMPT->move.z) * 0.4f;
			pMPT->move.x += (0.0f - pMPT->move.x) * 0.4f;
			pMPT->move.y += (0.0f - pMPT->move.y) * 0.013f;

			//if (pMPT->oldpos.y - EFFECT_SIZEW < 0)
			//{// �O��̈ʒu������艺�ɍs������

			// // �ړ��̐ݒ�
			//	float fAngle = (float)((rand() % 628) - 628) / 100.f;

			//	pMPT->move.z = cosf(fAngle + D3DX_PI) * 8.0f;
			//	pMPT->move.x = sinf(fAngle - D3DX_PI) * 8.0f;

			//	pMPT->pos.y = 0 + EFFECT_SIZEW;
			//	pMPT->move.y += 20.0f;
			//}

			// ���C�t�̌���
			pMPT->nlife -= 1;

			// �����`�F�b�N
			if (pMPT->nlife == 0)
			{
				// 0�ɂȂ�����t�H���X�ɕς���
				pMPT->bUse = false;
			}


		}
	}
}

//==================================================================================================================================================================//
// �`�揈��
//==================================================================================================================================================================//
void DrawModelP(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	ModelParticl *pMPT = &g_MPT[0];

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nNumCnt = 0; nNumCnt < MPT_MAX; nNumCnt++, pMPT++)
	{
		if (pMPT->bUse == true)
		{
			D3DXMatrixIdentity(&pMPT->mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pMPT->rot.y, pMPT->rot.x, pMPT->rot.z);
			D3DXMatrixMultiply(&pMPT->mtxWorld, &pMPT->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pMPT->pos.x, pMPT->pos.y, pMPT->pos.z);
			D3DXMatrixMultiply(&pMPT->mtxWorld, &pMPT->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pMPT->mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatMPT->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_NumMatMPT; nCntMat++)
			{
				// �e���f���p�[�c�̕`��
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureMPT);
				// ���f���̕`��
				g_pMeshMPT->DrawSubset(nCntMat);
			}
			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}


//==================================================================================================================================================================//
// ���u�̐ݒu
//==================================================================================================================================================================//
void SetModelP(D3DXVECTOR3 pos, float movex, float movez, float movey, int nIdx, int nLife)
{
	ModelParticl *pMPT = &g_MPT[0];

	for (int nNumCnt = 0; nNumCnt < nIdx; pMPT++)
	{
		if (pMPT->bUse == false)
		{
			// �ʒu�̐ݒ�
			pMPT->pos.x = pos.x;
			pMPT->pos.z = pos.z;
			pMPT->pos.y = pos.y;

			// �ړ��̐ݒ�
			float fAngle = (float)((rand() % 628) - 628) / 100.f;
			// �����
			pMPT->move.z = cosf(fAngle + D3DX_PI) * 100.0f;
			pMPT->move.x = sinf(fAngle - D3DX_PI) * 100.0f;

			pMPT->move.y = movey;

			//pMPT->move.y = tanf(fAngle + D3DX_PI) * 3.0f;

			// �����̐ݒ�
			pMPT->nlife = nLife;

			// �e�𔭎�
			pMPT->bUse = true;

			nNumCnt++;

	//		break;
		}
	}
}


//==================================================================================================================================================================//
// �v���C���[�̏��
//==================================================================================================================================================================//
ModelParticl *GetModelP(void)
{
	return &g_MPT[0];
}