//##################################################################################################################################################################//
//
// �|���S������ [polygon.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
//�@�C���N���[�h�t�@�C��
//=====================================================================================================================================================================//
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//=====================================================================================================================================================================//
//�@static������
//=====================================================================================================================================================================//
vector<CPolygon*> CPolygon::m_pPolygon = {};

//=====================================================================================================================================================================//
//�@�R���X�g���N�^
//=====================================================================================================================================================================//
CPolygon::CPolygon()
{
	//�e�����o�ϐ��̃N���A
	m_pVtxBuff = nullptr;
	m_pos = ZeroVector3;
	m_size = ZeroVector3;

	CPolygon *pPolygon = nullptr;

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] == nullptr)
	//	{
	//		m_pPolygon[nCnt] = this;
	//		break;
	//	}
	//}

	pPolygon = this;

	m_pPolygon.push_back(pPolygon);
}

CPolygon::~CPolygon()
{
}

CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// polygon�̃N���X�̃|�C���^
	CPolygon *pPolygon = nullptr;

	// �������̊m��
	pPolygon = new CPolygon;

	// null�`�F�b�N
	if (pPolygon != nullptr)
	{
		// �������J�n
		pPolygon->m_pos = pos;
		pPolygon->m_size = size;
		pPolygon->Init();
	}
	else return nullptr;

	return pPolygon;
}

HRESULT CPolygon::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y + m_size.y, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = D3DCOLOR_RGBA(225, 225, 225, 225);
	pVtx[1].col = D3DCOLOR_RGBA(225, 225, 225, 225);
	pVtx[2].col = D3DCOLOR_RGBA(225, 225, 225, 225);
	pVtx[3].col = D3DCOLOR_RGBA(225, 225, 225, 225);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CPolygon::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

void CPolygon::Update(void)
{
}

void CPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void CPolygon::DrawAllList(void)
{
	for (size_t nCnt = 0; nCnt < m_pPolygon.size(); nCnt++)
	{
		if (m_pPolygon.at(nCnt) != nullptr)
		{
			m_pPolygon.at(nCnt)->Draw();
		}
	}
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] != nullptr)
	//	{
	//		m_pPolygon[nCnt]->Draw();
	//	}
	//}
}

void CPolygon::ReleceAllList(void)
{
	for (size_t nCnt = 0; nCnt < m_pPolygon.size(); nCnt++)
	{
		if (m_pPolygon.at(nCnt) != nullptr)
		{
			delete m_pPolygon.at(nCnt);
			m_pPolygon.at(nCnt) = nullptr;

		}
	}
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] != nullptr)
	//	{
	//		delete m_pPolygon[nCnt];
	//		m_pPolygon[nCnt] = nullptr;
	//	}
	//}
}

void CPolygon::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CPolygon::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}

void CPolygon::SetColor(const D3DXCOLOR color)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
