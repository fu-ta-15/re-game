//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��
	SOUND_LABEL_BGM001,			// �`���[�g���A��
	SOUND_LABEL_BGM002,			// �Q�[��
	SOUND_LABEL_BGM003,			// result
	SOUND_LABEL_BGM004,			// �����L���O

	SOUND_LABEL_SE_PAUSE0,		// �e���ˉ�
	SOUND_LABEL_SE_PAUSE1,			// �q�b�g��
	SOUND_LABEL_SE_PAUSE2,	// ������
	SOUND_LABEL_SE_ATTACK,		// �e���ˉ�
	SOUND_LABEL_SE_BLOCK,
	SOUND_LABEL_SE_CAENGE,
	SOUND_LABEL_SE_OK,
	SOUND_LABEL_SE_NO,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
