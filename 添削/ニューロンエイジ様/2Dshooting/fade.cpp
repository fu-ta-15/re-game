//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//



#include "fade.h"


#define COLOR_RED		(0)		//�ԐF
#define COLOR_BULUE		(0)		//�F
#define COLOR_GREEN		(0)		//�ΐF
#define COLOR_ALPHA		(125)	//�A���t�@�l


//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;		//�e�N�X�`���̏��
FADE g_fade;									//�t�F�[�h�̏��
MODE g_modeNext;								//���̃��[�h
D3DXCOLOR g_colorFade;							//�t�F�[�h�̐F
float g_fAlpha;									//�A���t�@�l


HRESULT InitFade(MODE modeNext)
{

	g_fAlpha = 1.0f;

	LPDIRECT3DDEVICE9 pDevi;

	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevi = GetDevice();


	//���_�o�b�t�@�̐���
	if (FAILED(pDevi->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFade, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fAlpha);


	//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = g_colorFade; 
	pVtx[1].col = g_colorFade; 
	pVtx[2].col = g_colorFade; 
	pVtx[3].col = g_colorFade; 

	//�e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 1);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 0);


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffFade->Unlock();
	return S_OK;

}

void UninitFade(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}

void UpdateFade(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	
	//�t�F�C�h�̃J���[�ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fAlpha);

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = g_colorFade; 
	pVtx[1].col = g_colorFade; 
	pVtx[2].col = g_colorFade; 
	pVtx[3].col = g_colorFade; 

	if (g_fade == FADE_IN)
	{
		//���l�����炵�Ă���
		g_fAlpha -= 0.02f;
		if (g_fAlpha <= 0.0f)
		{
			g_fade = FADE_NONE;		//�������Ă��Ȃ���Ԃɂ���
		}
	}
	else if (g_fade == FADE_OUT)
	{
		//���l�𑝂₵�Ă���
		g_fAlpha += 0.02f;
		if (g_fAlpha >= 1.0f)
		{
			SetMode(g_modeNext);	//���̃��[�h��
			g_fade = FADE_IN;		//�t�F�[�h�C���ɐ؂�ւ�
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFade->Unlock();
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		// 0//�`����J�n���钸�_�C���f�b�N�X
}

//�t�F�C�h�ƃ��[�h�̐؂�ւ�
void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;			//�t�F�[�h
	g_modeNext = modeNext;	//���̃��[�h
}

//�t�F�[�h�̎擾
FADE GetFade(void)
{
	return g_fade;
}
