//====================================================================
//
// 3D���f������ (scene3d.h)
// Author : ��{��
//
//====================================================================
#ifndef _MODEL_HIMIYA_H_
#define _MODEL_HIMIYA_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//================================================
// �N���X�錾
//================================================

// 3D���f���N���X
class CModelHimiya : public CObject
{
public:
    CModelHimiya();
    virtual ~CModelHimiya();

    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
	void Draw(CModelHimiya *pModel);
    void BindMesh(const LPD3DXMESH pMesh, const  LPD3DXBUFFER pBuffMat, const DWORD nNumMat);
    void BindTexture(const LPDIRECT3DTEXTURE9 pTex);
    void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
    void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
    void SetScale(const D3DXVECTOR3 scale) { m_scale = scale; }

    D3DXVECTOR3 GetPos(void) { return m_pos; }
    D3DXVECTOR3 GetRot(void) { return m_rot; }
    D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
    LPDIRECT3DTEXTURE9		m_pTexture;
    LPD3DXMESH				m_pMesh;
    LPD3DXBUFFER			m_pBuffMat;
    DWORD					m_nNumMat;
    D3DXMATRIX			    m_mtxWorld;		// ���[���h�}�g���b�N�X
    D3DXVECTOR3				m_pos;			// ���W
    D3DXVECTOR3				m_rot;			// ��]
    D3DXVECTOR3				m_scale;
};

#endif