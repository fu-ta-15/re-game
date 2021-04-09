//===============================================
//
// ���H���� (rail.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "rail.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CRail::m_pMesh[MAX_RAIL] = {};
LPD3DXBUFFER CRail::m_pBuffMat[MAX_RAIL] = {};
DWORD CRail::m_nNumMat[MAX_RAIL] = {};
LPDIRECT3DTEXTURE9 CRail::m_pTexture = NULL;
CRail * CRail::m_pRailedTop = NULL;
CRail * CRail::m_pRailedCur = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRail::CRail()
{
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CRail::~CRail()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CRail::Init(TYPE_RAIL type)
{
	CModelHimiya::Init();
	m_type = type;
	m_state = UNRAILED;

	BindMesh(m_pMesh[m_type], m_pBuffMat[m_type], m_nNumMat[m_type]);
	BindTexture(m_pTexture);


	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CRail::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CRail::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 posRailed = m_pRailedCur->GetPos();

	if (pos.x <= posRailed.x + 100.0f &&
		pos.x >= posRailed.x - 100.0f &&
		pos.z <= posRailed.z + 100.0f &&
		pos.z >= posRailed.z - 100.0f &&
		m_state == UNRAILED)
	{
		SetRailed();
	}

	CModelHimiya::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CRail::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CRail::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/model/lineStraight.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[STRAIGHT], NULL, &m_nNumMat[STRAIGHT], &m_pMesh[STRAIGHT]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/lineStraight.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[GOAL], NULL, &m_nNumMat[GOAL], &m_pMesh[GOAL]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/lineLeft.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[LEFT], NULL, &m_nNumMat[LEFT], &m_pMesh[LEFT]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/lineRight.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[RIGHT], NULL, &m_nNumMat[RIGHT], &m_pMesh[RIGHT]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CRail::Unload(void)
{
	for (int nCount = 0; nCount < MAX_RAIL; nCount++)
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
CRail * CRail::Create(TYPE_RAIL type, D3DXVECTOR3 pos)
{
	CRail *pRail = NULL;
	pRail = new CRail;
	pRail->Init(type);
	pRail->SetPos(pos);
	pRail->SetObjType(OBJ_TYPE_RAIL);

	return pRail;
}

//=============================================================================
// ���X�g�\������
// Author : ��{��
//=============================================================================
void CRail::SetRailed(void)
{
	m_state = RAILED;
	if (m_pRailedTop != NULL)
	{
		m_pRailedCur->m_pRailedNext = this;
	}
	else
	{
		m_pRailedTop = this;
	}

	this->m_pRailedPrev = m_pRailedCur;
	this->m_pRailedNext = NULL;
	m_pRailedCur = this;
}
