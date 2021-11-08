//*****************************************************************************
//
// �t�F�[�h���� [fade.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _FADE_H_
#define _FADE_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "manager.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CFade
{
public:
	//-------------------------------------------------------------------------
	// �t�F�C�h�̏��
	//-------------------------------------------------------------------------
	typedef enum
	{
		FADE_NONE = 0,	// �������ĂȂ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX
	}FADE;

	CFade();
	~CFade();

	static CFade *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// SET�֐�
	void SetFade(CManager::MODE mode);	
	void SetCol(D3DXCOLOR col);

	// Get�֐�
	static FADE GetFade(void);				

private:
	// �|���S���Ɏg�p���郁���o�ϐ�
	static FADE					m_FadeMode;				// �t�F�[�h�̏��
	CManager::MODE				m_modeNext;				// �t�F�[�h�I����̃��[�h�ݒ�p
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_size;					// �T�C�Y
	D3DXCOLOR					m_col;					// �J���[
	VERTEX_2D					*m_pVtx;				// 2D�|���S���̃|�C���^
};


#endif