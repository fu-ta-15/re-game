//*****************************************************************************
//
// �V�[������ [scene.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CScene
{
public:
	// �I�u�W�F�N�g�^�C�v
	typedef enum Priority	
	{
		OBJ_NONE = 0,	// �V���v���I�u�W�F�N�g�P
		OBJ_NONE2,		// �V���v���I�u�W�F�N�g�Q
		OBJ_BOSS,		// �{�X�I�u�W�F�N�g
		OBJ_BULLET1,	// �o���b�g�I�u�W�F�N�g�P
		OBJ_BULLET2,	// �o���b�g�I�u�W�F�N�g�Q
		OBJ_PLAYER,		// �v���C���[�I�u�W�F�N�g
		OBJ_CORE,		// �R�A�I�u�W�F�N�g
		OBJ_ENEMY,		// �G�I�u�W�F�N�g
		OBJ_EFFECT1,	// �G�t�F�N�g�I�u�W�F�N�g�P
		OBJ_MAX
	}ObjectType;	
	
	// �|�[�Y�̎��
	enum PauseType
	{
		PAUSE_BG = 0,	// �|�[�Y�̔w�i
		PAUSE_BUTTON1,	// �|�[�Y�̃{�^���P
		PAUSE_BUTTON2,	// �|�[�Y�̃{�^���Q
		PAUSE_BUTTON3,	// �|�[�Y�̃{�^���R
		PAUSE_MAX
	};

	CScene(Priority type);				// �R���X�g���N�^
	CScene(PauseType type);				// �|�[�Y�p�R���X�g���N�^
	CScene(bool bpause);				// �|�[�Y�������}�p�R���X�g���N�^

	// ���z�����֐�
	virtual ~CScene();					// �f�X�g���N
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Update(void)	= 0;	// �X�V
	virtual void Draw(void)		= 0;	// �`��

	static void ReleaseAll(void);		// ���ׂĂ�Release
	static void UpdateAll(void);		// ���ׂĂ̍X�V
	static void DrawAll(void);			// ���ׂĂ̕`��

	void Release(void);					// Release 
	void DeathRelease(void);			// ���S�t���O�������Ă��镨��Release
	void PauseRelease(void);			// �|�[�Y��Release


	// Set�֐� 
	void SetPos(D3DXVECTOR3 pos)	{ m_pos = pos; }		// �ʒu�̐ݒ�
	void SetSize(D3DXVECTOR3 size)	{ m_size = size; }		// �T�C�Y�̐ݒ�
	void SetCol(D3DXCOLOR col)		{ m_col = col; }		// �F�̐ݒ�
	void SetBool(bool bflag)		{ m_bBool = bflag; }	// �����̃t���O

	// Get�֐� 
	D3DXVECTOR3 GetPos(void)	{ return m_pos; }			// ����̃I�u�W�F�N�g�̈ʒu�擾
	D3DXVECTOR3 GetSize(void)	{ return m_size; }			// ����̃I�u�W�F�N�g�̃T�C�Y�擾
	D3DXCOLOR GetCol(void)		{ return m_col; }			// �F�̎擾
	bool GetBool(void)			{ return m_bBool; }			// �t���O�̎擾
	CScene *GetSceneNext(void);								// ���̃V�[���I�u�W�F�N�g�̎擾
	static CScene *GetScene(Priority type) { 				// �V�[���I�u�W�F�N�g�̐擪�̎擾
		return m_pTop[type]; }

private:
	static CScene		*m_pTop[OBJ_MAX];			// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene		*m_pCur[OBJ_MAX];			// ���݁i�Ō���j�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene		*m_pPauseScene;				// �V�[�����~�߂�ÓI�ϐ�
	static CScene		*m_pPauseObj[PAUSE_MAX];	// �|�[�Y�̃I�u�W�F�N�g
	CScene				*m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene				*m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^
	Priority			 m_type;					// �I�u�W�F�N�^�C�v
	D3DXVECTOR3			 m_pos;						// �ʒu
	D3DXVECTOR3			 m_size;					// �T�C�Y
	D3DXCOLOR			 m_col;						// �F
	bool				 m_bBool;					// �����̃t���O
	bool				 m_bDeath;					// ���S�t���O
};


#endif