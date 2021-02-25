#include "score.h"
#include "time.h"
#include "fade.h"

//�}�N���ϐ�
#define MAX_TIME	(3)


//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;;		//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nTime;
int g_nTimeCounter;

//=====================================================================================================================================================================//
//����������
//=====================================================================================================================================================================//
HRESULT InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�ϐ��̏�����
	g_nTime = 120;
	g_nTimeCounter = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureTime);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTime, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���E�e�N�X�`���̏������ݒ�
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{

		//�e���_���W
		pVtx[0].pos = D3DXVECTOR3(550 + ((float)nCntTime * 50), 0 + 110, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(550 + ((float)nCntTime * 50), 0 + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(600 + ((float)nCntTime * 50), 0 + 110, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600 + ((float)nCntTime * 50), 0 + 10, 0.0f);

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(225, 225, 225, 225);
		pVtx[1].col = D3DCOLOR_RGBA(225, 225, 225, 225);
		pVtx[2].col = D3DCOLOR_RGBA(225, 225, 225, 225);
		pVtx[3].col = D3DCOLOR_RGBA(225, 225, 225, 225);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

		//���_4�i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTime->Unlock();

	AddTime(0);

	return S_OK;
}

//=====================================================================================================================================================================//
//�I������
//=====================================================================================================================================================================//
void UninitTime(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//=====================================================================================================================================================================//
//�X�V����
//=====================================================================================================================================================================//
void UpdateTime(void)
{

	g_nTimeCounter += 1;

	if ((g_nTimeCounter % 60) == 0)
	{
		AddTime(1);
		if (g_nTime <= 0)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//=====================================================================================================================================================================//
//�`�揈��
//=====================================================================================================================================================================//
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}

}

//=====================================================================================================================================================================//
//�^�C�}�[�̉��Z
//=====================================================================================================================================================================//
void AddTime(int nValue)
{
	int nMath = 1000;		//�^�C�}�[�v�Z
	int aNumber[MAX_TIME];	//�^�C�}�[�̃i���o�[
	VERTEX_2D *pVtx;		//�|�C���^

	//�o�b�t�@�̃��b�N
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	g_nTime -= nValue;		//�^�C�}�[

	//�^�C�}�[�̕ύX
	for (int nCunTimeNum = 0; nCunTimeNum < MAX_TIME; nCunTimeNum++)
	{
		//�^�C�}�[�̌v�Z
		aNumber[nCunTimeNum] = (g_nTime%nMath / (nMath / 10));

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCunTimeNum] / 10, 1.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCunTimeNum] / 10, 0);
		pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCunTimeNum] / 10) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCunTimeNum] / 10) + 0.1f, 0);

		pVtx += 4;		//�|�C���^���W���l�i�߂�
		nMath /= 10;	//����10�����Ď��̌���
	}
	//�o�b�t�@�̃A�����b�N
	g_pVtxBuffTime->Unlock();
}
