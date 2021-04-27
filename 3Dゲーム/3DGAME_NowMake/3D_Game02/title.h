//##################################################################################################################################################################//
//
// �^�C�g���w�b�_�t�@�C�� [title.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _TITLE_H_
#define _TITLE_H_

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 oldpos;				// �ߋ��̈ʒu
	D3DXVECTOR3 move;				// �ړ���
	D3DXVECTOR3 rot;				// ��]
	D3DXVECTOR3 rotDest;			// ��]�ړI
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	LPD3DXMESH pMesh;				// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
	D3DXMATERIAL *pMat;				// �}�e���A���̃|�C���^
	DWORD NumMat;					// �}�e���A���̐�
	D3DXVECTOR3 g_VtxMinTitle;		// ���f���̍ŏ��l�iMIN�j
	D3DXVECTOR3	g_VtxMaxTitle;		// ���f���̍ő�l�iMAX�j
}TitleModel;

typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 size;				// �T�C�Y
	D3DXCOLOR col;					// �F
	int nTurnFade;					// �t�F�C�h�̐؂�ւ��p
}TitleUi;

//=====================================================================================================================================================================//
// �v���g�^�C�v�錾
//=====================================================================================================================================================================//
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

/* ���f�� */
void InitTitleModel(void);
void UninitTitleModel(void);
void UpdateTitleModel(void);
void DrawTitleModel(void);

/* UI */
HRESULT InitTitleUi(void);
void UninitTitleUi(void);
void UpdateTitleUi(void);
void DrawTitleUi(void);

#endif 