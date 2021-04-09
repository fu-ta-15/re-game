#pragma once
//====================================================================
//
// �c�[���̏��� (cube.h)
// Author : ��{��
//
//====================================================================
#ifndef _TOOL_H_
#define _TOOL_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "model_himiya.h"

//================================================
// �}�N����`
//================================================


//================================================
// �N���X�錾
//================================================

// UI�N���X
class CTool : public CModelHimiya
{
public:
	CTool();
	~CTool();

	typedef enum
	{
		PICKAXE = 0,
		AXE,
		MAX_TOOL
	}TYPE_TOOL;

	HRESULT Init(TYPE_TOOL type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CTool *Create(TYPE_TOOL type, D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh[MAX_TOOL];
	static LPD3DXBUFFER				m_pBuffMat[MAX_TOOL];
	static DWORD					m_nNumMat[MAX_TOOL];
	D3DXVECTOR3						m_rot;
	TYPE_TOOL						m_type;
};

#endif
