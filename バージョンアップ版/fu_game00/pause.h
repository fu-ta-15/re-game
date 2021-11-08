//*****************************************************************************
//
// �|�[�Y���� [pause.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "manager.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CScene2D;

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CPause : public CScene
{
public:
	typedef enum PAUSEMENU
	{
		MENU_RETRY = 0,
		MENU_QUIT,
		MENU_CONTINUE,
		MENU_MAX
	}PAUSEMENU;

	CPause();
	~CPause();

	static CPause *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SelectMenu(const int nMenuID);
	void MenuOk(const int nMenuID);

private:
	LPDIRECT3DTEXTURE9			m_pTex = NULL;			// �e�N�X�`���ւ̃|�C���g

	D3DXVECTOR2					m_tex;					// �e�N�X�`�����W
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_ButtonPos;			// Button�̈ʒu
	D3DXVECTOR3					m_rot;					// �p�x
	D3DXVECTOR3					m_size;					// �T�C�Y
	D3DXVECTOR3					m_move;					// �ړ���
	D3DXCOLOR					m_col;					// �J���[

	static CScene2D	*m_pScene2D;
	static CScene2D	*m_pPauseButton[MENU_MAX];
	static bool m_bPause;
	static int m_nMenuID;
};

#endif // !_PAUSE_H_
