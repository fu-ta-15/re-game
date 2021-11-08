//*****************************************************************************
//
// �^�C�g������ [title.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _TITLE_H_
#define	_TITLE_H_

//=============================================================================
//�@�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "mesh.h"
#include "sound.h"


class CTitle : public CScene
{
public:
	// �^�C�g��UI
	typedef enum TitleUI
	{
		UI_BG = 0,
		UI_BUTTON,
		UI_MAX
	}TitleUI;

	CTitle();
	~CTitle();

	static CTitle *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void ButtonUI(void);								
	void TitleLogo(int nTime);

	static CScene2D*			m_paTitleUI[UI_MAX];	// �^�C�g��UI�|���S��
	static CMesh*				m_pTitleLogo;			// ���b�V���|���S��
	float						AddCol = 0.0f;			// ���l
	int							m_nCntTime = 0;			// �J�E���g�^�C�}�[
	D3DXVECTOR2					m_tex;					// �e�N�X�`�����W
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_rot;					// �p�x
	D3DXVECTOR3					m_size;					// �T�C�Y
	D3DXVECTOR3					m_move;					// �ړ���
	D3DXCOLOR					m_col;					// �J���[
	D3DXCOLOR					m_ButtonCol;			// Button�̐F���

};




#endif // !1

