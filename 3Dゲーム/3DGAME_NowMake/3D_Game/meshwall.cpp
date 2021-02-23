//##################################################################################################################################################################//
//
// �n�ʏ��� [meshfield.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "meshfield.h"
#include "meshwall.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED							(255)								// �ԐF
#define COLOR_BULUE							(255)								// �F
#define COLOR_GREEN							(255)								// �ΐF
#define COLOR_ALPHA							(255)								// �A���t�@�l
#define INDEX_MAX							(14)
#define PVTEX_MAX							(9)									// pVtx

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;		// �e�N�X�`���̏��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	// �C���f�b�N�X�o�b�t�@�̏��

MeshWall g_aMeshWall[MAX_WALL];

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^
	VERTEX_3D *pVtx;							// ���_�|�C���^
	MeshWall *pMeshWall = &g_aMeshWall[0];

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg", &g_pTextureMeshWall);

	if (g_pTextureMeshWall == NULL)
	{
		printf("%s", "�f�[�^�ǂݍ��ݎ��s");
	}
	else
	{
		printf("%s", "\n �f�[�^�ǂݍ��ݐ��� \n data\\TEXTURE\\wall001.jpg");
	}

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		pMeshWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���S���W
		pMeshWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]
		pMeshWall->fIdxDeceHeight = 0.0f;				// ����
		pMeshWall->fIdxDeceWidth = 0.0f;				// ��
		pMeshWall->bUse = false;
	}

	// �ԍ�
	int pVtxIdx = 0;


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		//�e���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[4].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[5].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[6].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[7].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[8].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);

		// �@��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[4].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[5].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[6].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[7].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[8].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		// �e�N�X�`���̒��_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_��񕪐i�߂�
		pVtx += PVTEX_MAX;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_MAX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// �ԍ��f�[�^�̐ݒ�
		pIdx[0] = 3 + pVtxIdx;
		pIdx[1] = 0 + pVtxIdx;
		pIdx[2] = 4 + pVtxIdx;
		pIdx[3] = 1 + pVtxIdx;
		pIdx[4] = 5 + pVtxIdx;
		pIdx[5] = 2 + pVtxIdx;
		pIdx[6] = 2 + pVtxIdx;
		pIdx[7] = 6 + pVtxIdx;
		pIdx[8] = 6 + pVtxIdx;
		pIdx[9] = 3 + pVtxIdx;
		pIdx[10] = 7 + pVtxIdx;
		pIdx[11] = 4 + pVtxIdx;
		pIdx[12] = 8 + pVtxIdx;
		pIdx[13] = 5 + pVtxIdx;

		// �������_�i�X�j���i�߂�
		pVtxIdx += PVTEX_MAX;
		// �����ԍ��i�P�S�j���i�߂�
		pIdx += INDEX_MAX;
	}
	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshWall->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitMeshWall(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdateMeshWall(void)
{
	// �\���̂̃|�C���^�擾
	MeshWall *pMeshWall = &g_aMeshWall[0];

	VERTEX_3D *pVtx;							// ���_�|�C���^

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		if (pMeshWall->bUse == true)
		{
			// ���_�o�b�t�@�����b�N
			g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (PVTEX_MAX * nCntWall);

			//�e���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(pMeshWall->pos.x - pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + (pMeshWall->fIdxDeceHeight * 2), pMeshWall->pos.z);

			pVtx[1].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y + (pMeshWall->fIdxDeceHeight * 2), pMeshWall->pos.z);
			
			pVtx[2].pos = D3DXVECTOR3(pMeshWall->pos.x + pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + (pMeshWall->fIdxDeceHeight * 2), pMeshWall->pos.z);
			
			pVtx[3].pos = D3DXVECTOR3(pMeshWall->pos.x - pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + pMeshWall->fIdxDeceHeight, pMeshWall->pos.z);
			
			pVtx[4].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y + pMeshWall->fIdxDeceHeight, pMeshWall->pos.z);
			
			pVtx[5].pos = D3DXVECTOR3(pMeshWall->pos.x + pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + pMeshWall->fIdxDeceHeight, pMeshWall->pos.z);
			
			pVtx[6].pos = D3DXVECTOR3(pMeshWall->pos.x - pMeshWall->fIdxDeceWidth, pMeshWall->pos.y , pMeshWall->pos.z);
			
			pVtx[7].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y , pMeshWall->pos.z);
			
			pVtx[8].pos = D3DXVECTOR3(pMeshWall->pos.x + pMeshWall->fIdxDeceWidth, pMeshWall->pos.y , pMeshWall->pos.z);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffMeshWall->Unlock();
		}
	}
}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawMeshWall(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	MeshWall *pMeshWall = &g_aMeshWall[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		if (pMeshWall->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pMeshWall->mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pMeshWall->rot.y, pMeshWall->rot.x, pMeshWall->rot.z);
			D3DXMatrixMultiply(&pMeshWall->mtxWorld, &pMeshWall->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
			D3DXMatrixMultiply(&pMeshWall->mtxWorld, &pMeshWall->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pMeshWall->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));
			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0, 0,
				9 * nCntWall, 0, 12);
		}
	}
}

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	MeshWall *pMeshWall = &g_aMeshWall[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		if (pMeshWall->bUse == false)
		{
			pMeshWall->pos = pos;
			pMeshWall->rot = rot;
			pMeshWall->fIdxDeceHeight = fHeight;
			pMeshWall->fIdxDeceWidth = fWidth;

			pMeshWall->bUse = true;
			break;
		}
	}
}

MeshWall * GetMeshWall(void)
{
	return &g_aMeshWall[0];
}
