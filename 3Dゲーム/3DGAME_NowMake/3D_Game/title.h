//##################################################################################################################################################################//
//
// �^�C�g���w�b�_�t�@�C�� [title.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//=====================================================================================================================================================================//
// �^�C�g��
//=====================================================================================================================================================================//
typedef enum
{
	TITLEMODEL_BG = 0,
	TITLEMODEL_TITLE,
	TITLEMODEL_BUUTON,
	TITLEMODEL_MAX
}TITLEMODELTYPE;


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

//=====================================================================================================================================================================//
// �v���g�^�C�v�錾
//=====================================================================================================================================================================//
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

void InitTitleModel(void);
void UninitTitleModel(void);
void UpdateTitleModel(void);
void DrawTitleModel(void);
void SetTitleModel(void);

#endif 