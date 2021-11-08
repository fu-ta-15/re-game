//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"


//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CSound
{
public:
	//*************************************************************************
	// �T�E���h�t�@�C��
	//*************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// �^�C�g��
		SOUND_LABEL_BGM001,			// �`���[�g���A��
		SOUND_LABEL_BGM002,			// �Q�[��
		SOUND_LABEL_BGM003,			// result

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:

	static IXAudio2					*m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice		*m_pMasteringVoice;						// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice			*m_apSourceVoice[SOUND_LABEL_MAX];			// �\�[�X�{�C�X
	static BYTE						*m_apDataAudio[SOUND_LABEL_MAX];			// �I�[�f�B�I�f�[�^
	static DWORD						 m_aSizeAudio[SOUND_LABEL_MAX];			// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDPARAM					 m_aParam[SOUND_LABEL_MAX];				// �e���f�ނ̃p�����[�^
		


};


#endif
