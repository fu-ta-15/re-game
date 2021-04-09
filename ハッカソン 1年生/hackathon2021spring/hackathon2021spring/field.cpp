//===============================================
//
// �t�B�[���h���� (field.cpp)
// Author : ��{��
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// �C���N���[�h�t�@�C��
//========================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include "cube.h"
#include "player.h"
#include "rail.h"
#include "tool.h"
#include "train.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================

//=============================================================================
// �R���X�g���N�^
// Author : ��{��
//=============================================================================
CField::CField()
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			m_aGround[nCountHeight][nCountWidth] = NONE;
		}
	}

	m_nHeight = FIELD_HEIGHT;
	m_nWidth = FIELD_WIDTH;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CField::~CField()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CField::Init(void)
{
	m_nHeight = FIELD_HEIGHT;
	m_nWidth = FIELD_WIDTH;

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CField::Uninit(void)
{
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CField::Update(void)
{
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CField::Draw(void)
{
}

//=============================================================================
// �}�b�v�f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
void CField::LoadMapData(void)
{
	FILE *pFile = NULL;
	int nLoadHeight = 0;
	int nLoadWidth = 0;

		pFile = fopen("./Data/map/rail_map.csv", "r");
	m_nWidth = FIELD_WIDTH;

	// �J����
	if (pFile != NULL)
	{
		for (int nCountMap = 0; nCountMap < m_nWidth * m_nHeight; nCountMap++)
		{
			while (fscanf(pFile, "%d,", &m_aGround[nLoadHeight][nLoadWidth]) != EOF)
			{
				nLoadWidth++;
				if (nLoadWidth >= m_nWidth)
				{
					nLoadWidth = 0;
					nLoadHeight++;
				}
			}
		}

		fclose(pFile);
	}
	// �J���Ȃ�
	else
	{
		printf("�J����܂���ł���\n");
	}
}

//=============================================================================
// �C���X�^���X��������
// Author : ��{��
//=============================================================================
CField* CField::Create(TYPE_FIELD type)
{
	CField *m_pField;

	m_pField = new CField;
	m_pField->Init();

	// �t�B�[���h�ǂݍ���
	m_pField->LoadMapData();

	// �t�B�[���h�ݒu
	m_pField->SetField();

	return m_pField;
}

//=============================================================================
// �t�B�[���h��������
// Author : ��{��
//=============================================================================
void CField::SetField(void)
{
	int nHeight = 0;

	for (int nCountHeight = m_nHeight - 1; nCountHeight > -1; nCountHeight--)
	{
		for (int nCountWidth = 0; nCountWidth < m_nWidth; nCountWidth++)
		{
			CCube::Create(CCube::DIRT, D3DXVECTOR3(nCountHeight * CUBE_SIZE, 0.0f, -nCountWidth * CUBE_SIZE));

			switch (m_aGround[nHeight][nCountWidth])
			{
			case TREE:
				CCube::Create(CCube::TREE, D3DXVECTOR3((nCountHeight - 0.5f) * CUBE_SIZE, CUBE_SIZE, -nCountWidth * CUBE_SIZE));
				break;
			case STONE_BREAK:
				CCube::Create(CCube::STONE_BREAK, D3DXVECTOR3((nCountHeight - 0.5f) * CUBE_SIZE, CUBE_SIZE, -nCountWidth * CUBE_SIZE));
				break;
			case STONE_UNBREAK:
				CCube::Create(CCube::STONE_UNBREAK, D3DXVECTOR3((nCountHeight - 0.5f) * CUBE_SIZE, CUBE_SIZE, -nCountWidth * CUBE_SIZE));
				break;
			case PLAYER:
				CPlayer::Create(D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE));
				CTool::Create(CTool::PICKAXE, D3DXVECTOR3((nCountHeight - 1.5f) * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE));
				CTool::Create(CTool::AXE, D3DXVECTOR3((nCountHeight - 1.5f) * CUBE_SIZE, CUBE_SIZE / 2.0f, -(nCountWidth + 1) * CUBE_SIZE));
				break;
			case RAIL:
				CRail::Create(CRail::STRAIGHT, D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE))->SetRailed();
				break;
			case TRAIN:
				CRail::Create(CRail::STRAIGHT, D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE))->SetRailed();
				m_pTrain = CTrain::Create(D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -(nCountWidth + 0.5f) * CUBE_SIZE));
				break;
			case GOAL:
				CRail::Create(CRail::GOAL, D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE));
			default:
				break;
			}
		}

		nHeight++;
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�^�C���擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CField::TYPE_TILE CField::GetTile(int nHeight, int nWidth)
{
	return m_aGround[nHeight][nWidth];
}