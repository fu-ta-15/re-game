//##################################################################################################################################################################//
//
// �p�[�e�B�N������ [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "particle.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_PARTICLE	(2000)
#define PARTICLE_SIZE	(20)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;		 // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	 // ���_�o�b�t�@�̃|�C���^
PARTICLE g_aParticle[MAX_PARTICLE];					 // �p�[�e�B�N���̍\����

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\images.jfif", &g_pTextureParticle);

	// �e�ϐ�������
	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		g_aParticle[nCounterParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCounterParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCounterParticle].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCounterParticle].fRadius = 0.0f;
		g_aParticle[nCounterParticle].nLife = 0;
		g_aParticle[nCounterParticle].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		//�e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCounterParticle].pos.x + PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.y - PARTICLE_SIZE, g_aParticle[nCounterParticle].pos.z);

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);

		//�e�N�X�`���̒��_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�����T�C�Y���i�߂�
		pVtx += 4;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffParticle->Unlock();
	return S_OK;
}


//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitParticle(void)
{
	if (g_pVtxBuffParticle != NULL)
	{	// ���_�o�b�t�@�̔j��
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
	if (g_pTextureParticle != NULL)
	{	// �e�N�X�`���̔j��
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
}


//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateParticle(void)
{
	VERTEX_3D *pVtx;

	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	PARTICLE *pParticle = &g_aParticle[0];

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			pParticle->nLife--;

			pParticle->pos -= pParticle->move;


			if (pParticle->nLife <= 0)
			{
				pParticle->bUse = false;
			}

		}
		pVtx += 4;
	}
	g_pVtxBuffParticle->Unlock();
}


//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawParticle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;
	// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	PARTICLE *pParticle = &g_aParticle[0];
	
	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCounterParticle = 0; nCounterParticle < MAX_PARTICLE; nCounterParticle++)
	{
		if (g_aParticle[nCounterParticle].bUse == true)
		{


			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pParticle->mtxWorld);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pParticle->mtxWorld, NULL, &mtxView); // �t�s������߂�

			pParticle->mtxWorld._41 = 0.0f;
			pParticle->mtxWorld._42 = 0.0f;
			pParticle->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pParticle->pos.x, pParticle->pos.y, pParticle->pos.z);
			D3DXMatrixMultiply(&pParticle->mtxWorld, &pParticle->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pParticle->mtxWorld);


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCounterParticle * 4, 2);

		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//=====================================================================================================================================================================//
// Particle�̐ݒ�
//=====================================================================================================================================================================//
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, int number, int Life, D3DXCOLOR color)
{
	PARTICLE *pParticle;
	pParticle = &g_aParticle[0];

	for (int nCounterParticle = 0; nCounterParticle < number; nCounterParticle++, pParticle++)
	{
		for (int nCounterParticle = 0; nCounterParticle < number; nCounterParticle++, pParticle++)
		{
			if (pParticle->bUse == false)
			{
				// Particle�̊e�X�e�[�^�X����
				pParticle->pos = pos;		// �ʒu
				pParticle->color = color;	// �F
				pParticle->nLife = Life;	// ��������

				// ��������p�x
				float fAngle = (float)((rand() % 628) - 628) / 100.f;
				pParticle->move.x = move.x;	 // X�����̈ړ�
				pParticle->move.z = move.z;	 // Y�����̈ړ�
				pParticle->fRadius = (float)(rand() % 30) + 11;					 // ���a�i�傫���j
				pParticle->bUse = true;											 // �g�p��
				break;
			}
		}
	}
}

PARTICLE *GetParticle(void)
{
	return &g_aParticle[0];
}

