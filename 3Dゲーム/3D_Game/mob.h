//##################################################################################################################################################################//
//
// ���u�w�b�_�t�@�C�� [mob.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MOB_H_
#define _MOB_H_


#include "main.h"

//=====================================================================================================================================================================//
// �\����
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 oldpos;				// �ߋ��̈ʒu
	D3DXVECTOR3 move;				// �ړ���
	D3DXVECTOR3 rot;				// ��]
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	LPD3DXMESH pMesh;				// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
	D3DXMATERIAL *pMat;				// �}�e���A���̃|�C���^
	DWORD NumMat;					// �}�e���A���̐�
	int nIdxModelParent;			// �e���f���̃C���f�b�N�X
	D3DXVECTOR3 g_VtxMinModel;		// ���f���̍ŏ��l�iMIN�j
	D3DXVECTOR3	g_VtxMaxModel;		// ���f���̍ő�l�iMAX�j

}Mob;		// ���f��

typedef struct
{
	/* �v���C���[��� */
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ��]
	D3DXVECTOR3 rotDest;			// ��]�ړI
	D3DXVECTOR3 move;				// �ړ���
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X

									/* ���f����� */
	Mob aModel[1];					// ���f���p�[�c[��]
	int nNumModel;					// ���f���p�[�c��
	int nCuntDown;					// �o���܂ł̃J�E���g�_�E��
	int nCuntUp;
	int nlife;						// ���C�t
	bool bUse;						// �g�p���Ă��邩

									/* �e */
	int nNumShadow;					// �e
}Moblayer;	// �v���C���[(�����Ȃ����f��)

			//=====================================================================================================================================================================//
			// �v���g�^�C�v�錾
			//=====================================================================================================================================================================//
void InitMob(void);
void UninitMob(void);
void UpdateMob(void);
void DrawMob(void);
void SetMob(void);
void FileLoadMob(void);
Moblayer *GetMoblayer(void);

#endif // !_MODEL_H_
