//##################################################################################################################################################################//
//
// ���C������ [main.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
//�@�C���N���[�h�t�@�C��
//=====================================================================================================================================================================//
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer = nullptr;

CManager::CManager()
{
}

CManager::~CManager()
{
}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pRenderer = new CRenderer;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}


	return S_OK;
}

void CManager::Uninit(void)
{
	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̏I�������Ăяo��
		m_pRenderer->Uninit();

		//�������̍폜
		delete m_pRenderer;

		//�������̃N���A
		m_pRenderer = nullptr;
	}
}

void CManager::Update(void)
{
	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̍X�V�����Ăяo��
		m_pRenderer->Update();
	}
}

void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Draw();
	}
}

CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}
