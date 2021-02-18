//##################################################################################################################################################################//
//
// �Ǐ��� [wall.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "billboard.h"
#include "shadow.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define LENGTH_POLYGON_X					(5)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_POLYGON_Y					(5)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_POLYGON_Z					(50)								// ���S����e���_�̋��������߂鐔�l
#define COLOR_RED							(255)								// �ԐF
#define COLOR_BULUE							(255)								// �F
#define COLOR_GREEN							(255)								// �ΐF
#define COLOR_ALPHA							(255)								// �A���t�@�l
#define PVTEX_MAX							(4)									// pVtx


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		// �e�N�X�`���̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	// ���_�o�b�t�@�̏��
Billboard g_Billboard;
int g_nNumShadowBillboard;

//=====================================================================================================================================================================//
// �v���C���[�̏���������
//=====================================================================================================================================================================//
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^
	VERTEX_3D *pVtx;							// ���_�|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg", &g_pTextureBillboard);

	if (g_pTextureBillboard == NULL)
	{
		printf("%s", "�f�[�^�ǂݍ��ݎ��s");
	}
	else
	{
		printf("%s", "\n �f�[�^�ǂݍ��ݐ��� \n data\\TEXTURE\\wall001.jpg");
	}

	// ���S���W
	g_Billboard.pos = D3DXVECTOR3(0.0f, 20.0f, 10.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_Billboard.pos.x - LENGTH_POLYGON_X, g_Billboard.pos.y + LENGTH_POLYGON_Y, g_Billboard.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Billboard.pos.x + LENGTH_POLYGON_X, g_Billboard.pos.y + LENGTH_POLYGON_Y, g_Billboard.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Billboard.pos.x - LENGTH_POLYGON_X, g_Billboard.pos.y, g_Billboard.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Billboard.pos.x + LENGTH_POLYGON_X, g_Billboard.pos.y, g_Billboard.pos.z);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();

	//g_nNumShadowBillboard = SetShadow(g_Billboard.pos, 10.0f, 10.0f);

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitBillboard(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdateBillboard(void)
{
	//SetPositionShadow(g_nNumShadowBillboard, g_Billboard.pos);
}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawBillboard(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;
	// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Billboard.mtxWorld);

	// �r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_Billboard.mtxWorld, NULL, &mtxView); // �t�s������߂�

	g_Billboard.mtxWorld._41 = 0.0f;
	g_Billboard.mtxWorld._42 = 0.0f;
	g_Billboard.mtxWorld._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Billboard.pos.x, g_Billboard.pos.y, g_Billboard.pos.z);
	D3DXMatrixMultiply(&g_Billboard.mtxWorld, &g_Billboard.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Billboard.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

