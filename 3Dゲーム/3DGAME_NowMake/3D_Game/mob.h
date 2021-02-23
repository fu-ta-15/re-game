//##################################################################################################################################################################//
//
// ���u�w�b�_�t�@�C�� [mob.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MOB_H_
#define _MOB_H_


#include "main.h"


#define MOB_MAX				(10)


//=====================================================================================================================================================================//
// �\����
//=====================================================================================================================================================================//

typedef struct
{
	/* �v���C���[��� */
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
	D3DXVECTOR3 g_VtxMinMob;		// ���f���̍ŏ��l�iMIN�j
	D3DXVECTOR3	g_VtxMaxMob;		// ���f���̍ő�l�iMAX�j
									/* ���f����� */
	int nNumModel;					// ���f���p�[�c��
	int nCuntDown;					// �o���܂ł̃J�E���g�_�E��
	int nCuntUp;					// �J�E���g�A�b�v
	int nlife;						// ���C�t
	int nMobNum;					// ���u�̐�
	bool bColl;
	bool bUse;						// �g�p���Ă��邩

									/* �e */
	int nNumShadow;					// �e
}Moblayer;	// �v���C���[(�����Ȃ����f��)



typedef struct
{
	D3DXVECTOR3 MotionPos;
	D3DXVECTOR3 MotionRot;
	D3DXVECTOR3 MotionPosDest;
	D3DXVECTOR3 MotionRotDest;
	int Key;
	int NextKey;

}MotionMob;

//=====================================================================================================================================================================//
// �v���g�^�C�v�錾
//=====================================================================================================================================================================//
void InitMob(void);
void UninitMob(void);
void UpdateMob(void);
void DrawMob(void);
void SummonMob(void);
void SetMob(void);
void FileLoadMob(void);
Moblayer *GetMoblayer(void);

#endif // !_MODEL_H_
