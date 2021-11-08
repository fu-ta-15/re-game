//*****************************************************************************
//
// �V�[������ [scene.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _POLYGON_H_
#define _POLYGON_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CPolygon
{
public:

	typedef enum POLYGON_MOVE
	{
		POLYGON_CENTER = 0,
		POLYGON_LIGHT,
		POLYGON_LEFT,
		POLYGON_MAX
	}POLYGON_MOVE;

	CPolygon();
	~CPolygon();

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT CreateTexture(const LPCSTR pSrcFile);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// SET�֐�
	void SetPos(const D3DXVECTOR3 pos);
	void SetSize(const D3DXVECTOR3 size);
	void SetCol(const D3DXCOLOR col);
	void SetTex(const D3DXVECTOR2 tex, const D3DXVECTOR2 fnumber);
	void SetUse(bool bUse);
	void SizeChangeX(float AddSize, POLYGON_MOVE type);

	// GET�֐�
	D3DXVECTOR3 GetPos(void);
	D3DCOLOR GetCol(void);

private:
	// �|���S���Ɏg�p���郁���o�ϐ�
	LPDIRECT3DTEXTURE9			m_pTex = NULL;			// �e�N�X�`���ւ̃|�C���g
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_rot;					// �p�x
	D3DXVECTOR3					m_size;					// �T�C�Y
	D3DXVECTOR3					m_move;					// �ړ���
	D3DXVECTOR2					m_tex;					// �e�N�X�`�����W
	D3DXCOLOR					m_col;					// �J���[
	float						m_fAngle;				// �Ίp���̊p�x
	float						m_fAnimeY;				// �A�j���[�V�������WY
	float						m_fAnimeX;				// �A�j���[�V�������WX

	bool						m_bUse;
};


#endif