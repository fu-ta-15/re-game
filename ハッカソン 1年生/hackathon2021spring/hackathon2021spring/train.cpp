//===============================================
//
// ���H���� (rail.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "train.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CTrain::m_pMesh = NULL;
LPD3DXBUFFER CTrain::m_pBuffMat = NULL;
DWORD CTrain::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CTrain::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTrain::CTrain()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pRailed = NULL;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CTrain::~CTrain()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CTrain::Init(void)
{
	CModelHimiya::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);
	m_bGetTop = false;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CTrain::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CTrain::Update(void)
{
	D3DXVECTOR3 railPos, railPosOld, pos, move, rot;
	float fAngle1;

	if (m_pRailed != NULL)
	{
		railPos = m_pRailed->GetPos();
		pos = GetPos();
		rot = GetRot();
		fAngle1 = atan2f(railPos.z - pos.z, railPos.x - pos.x);

		move = D3DXVECTOR3(1.0f * cosf(fAngle1), 0.0f, 1.0f * sinf(fAngle1));

		rot.y += ((fAngle1 + D3DXToRadian(90)) - rot.y) * 0.1f;
		pos += move;

		if (pos.x >= railPos.x - 5.0f &&
			pos.x <= railPos.x + 5.0f &&
			pos.z >= railPos.z - 5.0f &&
			pos.z <= railPos.z + 5.0f )
		{
			if (m_pRailed->GetType() == CRail::GOAL)
			{
				CFade *pFade = CManager::GetFade();
				pFade->SetFade(CManager::MODE_RESULT);
			}
			else
			{
				m_pRailed = m_pRailed->GetRailedNext();
			}
		}

		SetRot(rot);
		SetPos(pos);
	}
	else
	{
		if (!m_bGetTop)
		{
			m_pRailed = CRail::GetRailedTop();
			m_bGetTop = true;
		}
	}

	CModelHimiya::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CTrain::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CTrain::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/model/cargo.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CTrain::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
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
CTrain * CTrain::Create(D3DXVECTOR3 pos)
{
	CTrain *pRail = NULL;
	pRail = new CTrain;
	pRail->Init();
	pRail->SetPos(pos);
	pRail->SetObjType(OBJ_TYPE_RAIL);

	return pRail;
}