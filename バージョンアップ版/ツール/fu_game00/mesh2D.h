//#############################################################################
//
// ���b�V���w�b�_�t�@�C�� [mesh.h]
// Author : SUZUKI FUUTA
//
//#############################################################################
#ifndef _MESH2D_H_
#define _MESH2D_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "Scene2D.h"

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CMesh : public CScene
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�
	//-------------------------------------------------------------------------
	CMesh(int nPriority);
	~CMesh();

	static CMesh *Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	static CMesh *Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, int nPriority);
	HRESULT CreateTexture(const LPCSTR pSrcFile);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�g�֐�  
	void SetWavePos(int nID, float pos);
	void SetVtxPosY(int nID, float posy);
	void SetVtxPosX(int nID, float posx);
	void SetPos(const D3DXVECTOR3 pos)			{ m_pos = pos; }
	void SetSize(const D3DXVECTOR3 size)		{ m_size = size; }
	void SetVertical(const int nVertical)		{ m_nVertical = nVertical; }
	void SetSide(const int nSide)				{ m_nSide = nSide; }
	void SetCol(const D3DXCOLOR col)			{ m_col = col; }
	void SetVtx(LPDIRECT3DVERTEXBUFFER9 Vtx)	{ m_pVtxBuff = Vtx; }

	// �Q�b�g�֐� 
	LPDIRECT3DVERTEXBUFFER9 GetVtx()	{ return m_pVtxBuff; }
	D3DXVECTOR3 GetPos()				{ return m_pos; }
	D3DXVECTOR3 GetSize()				{ return m_size; }
	int GetVertical()					{ return m_nVertical; }
	int GetSide()						{ return m_nSide; }
	int GetVtxNum()						{ return m_nVtx; }
	VERTEX_2D *GetVERTEX()				{ return m_pVtx; }

private:
	HRESULT MeshCreate(int nVertical, int nSide, WORD *pIdx);
	void MeshSetTex(int nVertical, int nSide, VERTEX_2D *pVtx);
	void MeshSetPos(int nVertical, int nSide, VERTEX_2D *pVtx);
	void MeshSetRhw(VERTEX_2D *pVtx);
	void MeshSetCol(VERTEX_2D *pVtx);
	int VertexCreate(int nVertical, int nSide);
	int IndexCreate(int nVertical, int nSide);

	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// ���_�o�b�t�@�̏��
	LPDIRECT3DTEXTURE9			m_pTexture;				// �e�N�X�`���̏��
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff;				// �C���f�b�N�X�o�b�t�@�̏��
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_size;					// �T�C�Y
	D3DXVECTOR3					m_rot;					// ����
	D3DXCOLOR					m_col;					// �F
	D3DXMATRIX					m_mtxWorld;				// ���[���h�}�g���b�N�X
	int							m_nVertical;			// �c�̕�����
	int							m_nSide;				// ���̕�����
	int							m_nVtx;					// ���_
	int							m_nIdx;					// �C���f�b�N�X
	bool						m_bWave;				// �g�̕\�����邩���Ȃ���
	VERTEX_2D *					m_pVtx;					// ���_���̕ۊǗp
};

#endif