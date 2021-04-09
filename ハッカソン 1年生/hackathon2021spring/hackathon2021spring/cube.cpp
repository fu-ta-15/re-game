//===============================================
//
// �{�^������ (Button.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "Cube.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CCube::m_pMesh[MAX_CUBE] = {};
LPD3DXBUFFER CCube::m_pBuffMat[MAX_CUBE] = {};
DWORD CCube::m_nNumMat[MAX_CUBE] = {};
LPDIRECT3DTEXTURE9 CCube::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCube::CCube()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CCube::~CCube()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CCube::Init(TYPE_CUBE type)
{
	CModelHimiya::Init();
	m_type = type;

	BindMesh(m_pMesh[m_type], m_pBuffMat[m_type], m_nNumMat[m_type]);
	BindTexture(m_pTexture);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CCube::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CCube::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CCube::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CCube::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/model/defaultBox.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[DIRT], NULL, &m_nNumMat[DIRT], &m_pMesh[DIRT]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/stoneBreak.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[STONE_BREAK], NULL, &m_nNumMat[STONE_BREAK], &m_pMesh[STONE_BREAK]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/stoneUnbreak.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[STONE_UNBREAK], NULL, &m_nNumMat[STONE_UNBREAK], &m_pMesh[STONE_UNBREAK]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/tree.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TREE], NULL, &m_nNumMat[TREE], &m_pMesh[TREE]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CCube::Unload(void)
{
	for (int nCount = 0; nCount < MAX_CUBE; nCount++)
	{
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}

	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �C���X�^���X��������
// Author : ��{��
//=============================================================================
CCube * CCube::Create(TYPE_CUBE type, D3DXVECTOR3 pos)
{
	CCube *pCube = NULL;
	pCube = new CCube;
	pCube->Init(type);
	pCube->SetPos(pos);

	switch (type)
	{
	case DIRT:
		pCube->SetObjType(OBJ_TYPE_DIRT);
		break;
	case STONE_BREAK:
		pCube->SetObjType(OBJ_TYPE_STONE_BREAK);
		break;
	case STONE_UNBREAK:
		pCube->SetObjType(OBJ_TYPE_STONE_UNBREAK);
		break;
	case TREE:
		pCube->SetObjType(OBJ_TYPE_TREE);
		break;
	default:
		break;
	}

	return pCube;
}