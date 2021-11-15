//*****************************************************************************
//
// ���C������ [main.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION	(0x0800)

//-----------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <random>
#include <d3dx9.h>	
#include <dinput.h>
#include <xaudio2.h>
#include <XInput.h>
#include <assert.h>



//-----------------------------------------------------------------------------
// ���C�u�����t�@�C���̃����N
//-----------------------------------------------------------------------------
#pragma comment(lib, "d3d9.lib")	
#pragma comment(lib, "d3dx9.lib")	
#pragma comment(lib, "dxguid.lib")	
#pragma comment(lib, "dinput8.lib")	
#pragma comment(lib, "winmm.lib")	
#pragma comment(lib, "xinput.lib")	

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH	(1366)													// �X�N���[���̕�
#define SCREEN_HEIGHT	(768)													// �X�N���[���̍���
#define WIDTH_HALF		(SCREEN_WIDTH/2)										// �X�N���[���̕��̔���
#define HEIGHT_HALF		(SCREEN_HEIGHT/2)										// �X�N���[���̍����̔���
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// ���_�t�H�[�}�b�g�E���_���W�E���_�J���[�E�e�N�X�`�����W
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)				// ���_�t�H�[�}�b�g�E���_���W�E���_�J���[�E�e�N�X�`�����W
#define NUM_VERTEX		(4)														// ���_��
#define CREATE_POLYGON	(sizeof(VERTEX_2D) * 4)									// �|���S���̐����̃T�C�Y

// �������p�}�N���ϐ�
#define ZeroVector2		(D3DXVECTOR2(0.0f, 0.0f))								// 
#define ZeroVector3		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))							// 
#define WhiteColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						// 
#define BlackColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))						// 
#define CENTER_POS		(D3DXVECTOR3(WIDTH_HALF,HEIGHT_HALF,0.0f))				// 
#define COLOR_RED		(255)													// �ԐF
#define COLOR_BULUE		(255)													// �F
#define COLOR_GREEN		(255)													// �ΐF
#define COLOR_ALPHA		(255)													// �A���t�@�l


//-----------------------------------------------------------------------------
// �\���̒�`
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

typedef  struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;
} VERTEX_3D;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
int GetFps(void);

#endif