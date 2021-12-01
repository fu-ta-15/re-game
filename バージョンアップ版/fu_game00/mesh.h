//#############################################################################
//
// ���b�V���w�b�_�t�@�C�� [mesh.h]
// Author : SUZUKI FUUTA
//
//#############################################################################
#ifndef _MESH_H_
#define _MESH_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"
#include "scene.h"


//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CMesh : public CScene
{
public:
	CMesh(Priority type);	  // �R���X�g���N�^
	~CMesh();				  // �f�X�g���N�^

	// �|���S�����b�V���̃N���G�C�g
	static CMesh *Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, CScene::ObjectType type);
	
	HRESULT CreateTexture(const LPCSTR pSrcFile);														// �e�N�X�`���̐���
	HRESULT Init(void) { return S_OK; }																	// ������(�������z�֐�)
	HRESULT Init(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// �����t��������
	void Uninit(void);																					// �I��
	void Update(void);																					// �X�V
	void Draw(void);																					// �`��


	// �Z�b�g�֐�  
	void SetVtxPosY(int nID, float posy);
	void SetVtxPosX(int nID, float posx);
	void SetMove(const D3DXVECTOR3 move);
	void SetPos(const D3DXVECTOR3 pos)			{ m_pos = pos; }
	void SetSize(const D3DXVECTOR3 size)		{ m_size = size; }
	void SetVertical(const int nVertical)		{ m_nVertical = nVertical; }
	void SetSide(const int nSide)				{ m_nSide = nSide; }
	void SetCol(const D3DXCOLOR col)			{ m_col = col; }
	void SetVtx(LPDIRECT3DVERTEXBUFFER9 Vtx)	{ m_pVtxBuff = Vtx; }

	// �Q�b�g�֐� 
	LPDIRECT3DVERTEXBUFFER9 GetVtx()	{ return m_pVtxBuff; }
	D3DXVECTOR3 GetPos()				{ return m_pos; }
	D3DXVECTOR3 GetMove()				{ return m_move; }
	D3DXVECTOR3 GetSize()				{ return m_size; }
	int GetVertical()					{ return m_nVertical; }
	int GetSide()						{ return m_nSide; }
	int GetVtxNum()						{ return m_nVtx; }
	VERTEX_2D *GetVERTEX()				{ return m_pVtx; }

private:
	HRESULT MeshCreate(int nVertical, int nSide, WORD *pIdx);
	void MeshSetTex(int nVertical, int nSide, VERTEX_2D *pVtx);
	void MeshSetPos(int nVertical, int nSide, VERTEX_2D *pVtx);
	void MeshSetNor(VERTEX_2D *pVtx);
	void MeshSetCol(VERTEX_2D *pVtx);
	int VertexCreate(int nVertical, int nSide);
	int IndexCreate(int nVertical, int nSide);

	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// ���_�o�b�t�@�̏��
	LPDIRECT3DTEXTURE9			m_pTexture;				// �e�N�X�`���̏��
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff;				// �C���f�b�N�X�o�b�t�@�̏��
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_move;					// �ʒu
	D3DXVECTOR3					m_Centerpos;			// ���S�ʒu
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
	VERTEX_2D *					m_pVtxsub;				// ���_���̕ۊǗp
};

#endif