//##################################################################################################################################################################//
//
// �^�C�g�����f������ [titlemodel.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "title.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define TITLE_MODEL_MAX					(1)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
TitleModel g_aTitleModel[TITLE_MODEL_MAX];					// Title�p�̃��f��


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �v���g�^�C�v�錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void GetVtxTitle(int nIdx);



//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
void InitTitleModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ���f�� */
	for (int nNumCnt = 0; nNumCnt < TITLE_MODEL_MAX; nNumCnt++)
	{
		/* No.0 �� */
		g_aTitleModel[nNumCnt].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_aTitleModel[nNumCnt].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleModel[nNumCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aTitleModel[nNumCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleModel[nNumCnt].pMesh = NULL;
		g_aTitleModel[nNumCnt].pBuffMat = NULL;
		g_aTitleModel[nNumCnt].pTexture = NULL;
		g_aTitleModel[nNumCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �t�@�C���̓ǂݍ���
		/* No.0 �� */
		D3DXLoadMeshFromX("data\\MODEL\\Title.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aTitleModel[nNumCnt].pBuffMat, NULL, &g_aTitleModel[nNumCnt].NumMat, &g_aTitleModel[nNumCnt].pMesh);

		g_aTitleModel[nNumCnt].pMat = (D3DXMATERIAL*)g_aTitleModel[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aTitleModel[nNumCnt].NumMat; nCntMat++)
		{
			if (g_aTitleModel[nNumCnt].pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, g_aTitleModel[nNumCnt].pMat[nCntMat].pTextureFilename, &g_aTitleModel[nNumCnt].pTexture);
			}
		}

		// ���f���̒��_�����o��
		GetVtxTitle(nNumCnt);
	}
}


//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitTitleModel(void)
{
	for (int nNumCnt = 0; nNumCnt < TITLE_MODEL_MAX; nNumCnt++)
	{
		if (g_aTitleModel[nNumCnt].pMesh != NULL)
		{// ���b�V���̔j��
			g_aTitleModel[nNumCnt].pMesh->Release();
			g_aTitleModel[nNumCnt].pMesh = NULL;
		}
		if (g_aTitleModel[nNumCnt].pBuffMat != NULL)
		{// �}�e���A���̔j��
			g_aTitleModel[nNumCnt].pBuffMat->Release();
			g_aTitleModel[nNumCnt].pBuffMat = NULL;
		}
		if (g_aTitleModel[nNumCnt].pTexture != NULL)
		{
			g_aTitleModel[nNumCnt].pTexture->Release();
			g_aTitleModel[nNumCnt].pTexture = NULL;
		}
	}
}


//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateTitleModel(void)
{
}


//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawTitleModel(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^


	for (int nNumCnt = 0; nNumCnt < TITLE_MODEL_MAX; nNumCnt++)
	{

		D3DXMatrixIdentity(&g_aTitleModel[nNumCnt].mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTitleModel[nNumCnt].rot.y, g_aTitleModel[nNumCnt].rot.x, g_aTitleModel[nNumCnt].rot.z);
		D3DXMatrixMultiply(&g_aTitleModel[nNumCnt].mtxWorld, &g_aTitleModel[nNumCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aTitleModel[nNumCnt].pos.x, g_aTitleModel[nNumCnt].pos.y, g_aTitleModel[nNumCnt].pos.z);
		D3DXMatrixMultiply(&g_aTitleModel[nNumCnt].mtxWorld, &g_aTitleModel[nNumCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aTitleModel[nNumCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aTitleModel[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aTitleModel[nNumCnt].NumMat; nCntMat++)
		{
			// �e���f���p�[�c�̕`��
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���f���̕`��
			g_aTitleModel[nNumCnt].pMesh->DrawSubset(nCntMat);
		}
		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}


//=====================================================================================================================================================================//
// ���_�����o��
//=====================================================================================================================================================================//
void GetVtxTitle(int nIdx)
{
	/* ���f���̒��_��񔲂��o�� */
	int nNumVtx;													// ���_��
	DWORD sizeFVF;													// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^
	float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;	// �ŏ��l�ۊǗp
	float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;	// �ő�l�ۊǗp

																// ���_�����擾
	nNumVtx = g_aTitleModel[nIdx].pMesh->GetNumVertices();
	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_aTitleModel[nIdx].pMesh->GetFVF());
	// ���_�o�b�t�@�����b�N
	g_aTitleModel[nIdx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��
													// �ő�l�E�ŏ��l�̑������
		if (Vtx.x < MinMob_X)
		{/* �ŏ��l */
			MinMob_X = Vtx.x;
			g_aTitleModel[nIdx].g_VtxMinTitle.x = MinMob_X;
		}
		if (Vtx.y < MinMob_Y)
		{
			MinMob_Y = Vtx.y;
			g_aTitleModel[nIdx].g_VtxMinTitle.y = MinMob_Y;
		}
		if (Vtx.z < MinMob_Z)
		{
			MinMob_Z = Vtx.z;
			g_aTitleModel[nIdx].g_VtxMinTitle.z = MinMob_Z;
		}

		if (Vtx.x > MaxMob_X)
		{/* �ő�l */
			MaxMob_X = Vtx.x;
			g_aTitleModel[nIdx].g_VtxMaxTitle.x = MaxMob_X;
		}
		if (Vtx.y > MaxMob_Y)
		{
			MaxMob_Y = Vtx.y;
			g_aTitleModel[nIdx].g_VtxMaxTitle.y = MaxMob_Y;
		}
		if (Vtx.z > MaxMob_Z)
		{
			MaxMob_Z = Vtx.z;
			g_aTitleModel[nIdx].g_VtxMaxTitle.z = MaxMob_Z;
		}
		pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_aTitleModel[nIdx].pMesh->UnlockVertexBuffer();


}
