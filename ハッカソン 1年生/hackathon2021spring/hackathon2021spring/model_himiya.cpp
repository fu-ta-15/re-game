//===============================================
//
// 3D���f������ (scene3d.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "model_himiya.h"
#include "manager.h"
#include "renderer.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelHimiya::CModelHimiya()
{
    m_pTexture = NULL;
    m_pBuffMat = NULL;
    m_pMesh = NULL;
    m_nNumMat = 0;
    D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelHimiya::~CModelHimiya()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModelHimiya::Init(void)
{
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModelHimiya::Uninit(void)
{
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CModelHimiya::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelHimiya::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxScale;
    D3DMATERIAL9 matDef;
    D3DXMATERIAL *pMat;

    D3DXMatrixIdentity(&m_mtxWorld);

    D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    pDevice->GetMaterial(&matDef);

    pDevice->SetTexture(0, m_pTexture);

    ZeroMemory(&matDef, sizeof(D3DMATERIAL9));

    pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
    {
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        m_pMesh->DrawSubset(nCntMat);
    }

    pDevice->SetMaterial(&matDef);

    pDevice->SetTexture(0, NULL);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelHimiya::Draw(CModelHimiya * pModel)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �e�Ƃ̃}�g���b�N�X�v�Z
	if (pModel != NULL)
	{
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &pModel->m_mtxWorld);
	}

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->GetMaterial(&matDef);

	pDevice->SetTexture(0, m_pTexture);

	ZeroMemory(&matDef, sizeof(D3DMATERIAL9));

	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		m_pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���b�V�����蓖��
//=============================================================================
void CModelHimiya::BindMesh(const LPD3DXMESH pMesh, const LPD3DXBUFFER pBuffMat, const DWORD nNumMat)
{
    m_pMesh = pMesh;
    m_pBuffMat = pBuffMat;
    m_nNumMat = nNumMat;
}

//=============================================================================
// �e�N�X�`�����蓖��
//=============================================================================
void CModelHimiya::BindTexture(const LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
