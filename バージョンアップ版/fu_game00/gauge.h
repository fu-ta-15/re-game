//*****************************************************************************
//
// �Q�[�W���� [gauge.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _GAUGE_H_
#define _GAUGE_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"
#include "polygon.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CGauge
{
public:
	//-----------------------------------------------------------------------------
	// �����o�֐�
	//-----------------------------------------------------------------------------
	CGauge();
	~CGauge();

	static CGauge *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size,int Stock);

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Relese(void);

private:
	int			m_nStock;
	D3DXVECTOR3	m_pos;
	D3DXVECTOR3	m_size;
	D3DXCOLOR	m_col;

	CPolygon	*m_pOutPolygon;
	CPolygon	*m_pInPolygon;
};

#endif // !_GAUGE_H_
