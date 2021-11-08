//*****************************************************************************
//
// �����i�X�R�A��^�C���j���� [number.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "manager.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CNumber
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�
	//-------------------------------------------------------------------------
	CNumber();
	~CNumber();

	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float fSplit);
	static void Unload();
	static HRESULT Load(const LPCSTR pSrcFile);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;

	D3DXVECTOR3					m_pos;
	D3DXVECTOR3					m_size;
	float						m_fSplit;
};



#endif // !_NUMBER_H_
