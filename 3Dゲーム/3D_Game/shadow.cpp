//##################################################################################################################################################################//
//
// �e���� [shadow.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "shadow.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define LENGTH_SHADOW_X						(15)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_SHADOW_Y						(3)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_SHADOW_Z						(15)								// ���S����e���_�̋��������߂鐔�l
#define COLOR_RED							(155)								// �ԐF
#define COLOR_BULUE							(255)								// �F
#define COLOR_GREEN							(155)								// �ΐF
#define COLOR_ALPHA							(255)								// �A���t�@�l
#define PVTEX_MAX							(4)									// pVtx
#define MAX_SHADOW							(3)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		// �e�N�X�`���̏��
Shadow g_Shadow;

//=====================================================================================================================================================================//
// �v���C���[�̏���������
//=====================================================================================================================================================================//
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^
	VERTEX_3D *pVtx;							// ���_�|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_pTextureShadow);

	if (g_pTextureShadow == NULL)
	{
		printf("%s", "�f�[�^�ǂݍ��ݎ��s");
	}
	else
	{
		printf("%s", "\n �f�[�^�ǂݍ��ݐ��� \n data\\TEXTURE\\shadow000.jpg");
	}
	// ���S���W
	g_Shadow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ��]
	g_Shadow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_Shadow.pos.x - LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z + LENGTH_SHADOW_Z);
	pVtx[1].pos = D3DXVECTOR3(g_Shadow.pos.x + LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z + LENGTH_SHADOW_Z);
	pVtx[2].pos = D3DXVECTOR3(g_Shadow.pos.x - LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z - LENGTH_SHADOW_Z);
	pVtx[3].pos = D3DXVECTOR3(g_Shadow.pos.x + LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z - LENGTH_SHADOW_Z);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	// �e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitShadow(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdateShadow(void)
{

	if (g_Shadow.bUse == true)
	{

	}

}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawShadow(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���Y�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Shadow.mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow.rot.y, g_Shadow.rot.x, g_Shadow.rot.z);
	D3DXMatrixMultiply(&g_Shadow.mtxWorld, &g_Shadow.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Shadow.pos.x, g_Shadow.pos.y, g_Shadow.pos.z);
	D3DXMatrixMultiply(&g_Shadow.mtxWorld, &g_Shadow.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Shadow.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// �e�̐ݒ�
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	int nIdx = -1;
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow.bUse == false)
		{
			g_Shadow.pos = pos;


			g_Shadow.bUse = true;
		}
	}

	return nIdx;
}

// �N�̉e��
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;							// ���_�|�C���^
												// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(pos.x - LENGTH_SHADOW_X, 0.0f, pos.z + LENGTH_SHADOW_Z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + LENGTH_SHADOW_X, 0.0f, pos.z + LENGTH_SHADOW_Z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - LENGTH_SHADOW_X, 0.0f, pos.z - LENGTH_SHADOW_Z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + LENGTH_SHADOW_X, 0.0f, pos.z - LENGTH_SHADOW_Z);
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

}

Shadow *GetShadow(void)
{
	return &g_Shadow;
}
