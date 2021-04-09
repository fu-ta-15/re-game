//===============================================
//
// �{�^������ (Button.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "field.h"
#include "game.h"
#include "rail.h"
//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CPlayer::m_pMesh = NULL;
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;
DWORD CPlayer::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_nPosMapHeight = 11;
	m_nPosMapWidth = 1;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CModelHimiya::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);


	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CPlayer::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CPlayer::Update(void)
{

	Interaction();
	Move();
	CModelHimiya::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/model/player00.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CPlayer::Unload(void)
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
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetObjType(OBJ_TYPE_PLAYER);

	return pPlayer;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���͂��p�x�ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
float CPlayer::InputToAngle(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();				// �L�[�{�[�h�̎擾
	float fInputAngle = 0.0f;
	//�L�[�{�[�h���͂��p�x�ɕϊ�
	if (pKeyboard->GetKeyPress(DIK_A))
	{
		fInputAngle = D3DXToRadian(-90.0f);
	}
	if (pKeyboard->GetKeyPress(DIK_D))
	{
		fInputAngle = D3DXToRadian(90.0f);
	}
	if (pKeyboard->GetKeyPress(DIK_S))
	{
		fInputAngle = D3DXToRadian(180.0f);

		// ���������p�̏���
		if (pKeyboard->GetKeyPress(DIK_A))
		{
			fInputAngle += D3DXToRadian(45.0f);
		}
		if (pKeyboard->GetKeyPress(DIK_D))
		{
			fInputAngle += D3DXToRadian(-45.0f);
		}
	}
	if (pKeyboard->GetKeyPress(DIK_W))
	{
		fInputAngle = D3DXToRadian(0.0f);

		if (pKeyboard->GetKeyPress(DIK_A))
		{
			fInputAngle += D3DXToRadian(-45.0f);
		}
		if (pKeyboard->GetKeyPress(DIK_D))
		{
			fInputAngle += D3DXToRadian(45.0f);
		}
	}
	return fInputAngle;
}

//=============================================================================
// �C���^���N�g����
// Author : ��{��
//=============================================================================
void CPlayer::Interaction(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();				// �L�[�{�[�h�̎擾
	D3DXVECTOR3 pos = GetPos();

	if (pKeyboard->GetKeyPress(DIK_SPACE))
	{
		CRail::Create(CRail::STRAIGHT,D3DXVECTOR3(pos.x, CUBE_SIZE / 2.0f, pos.z));
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ړ��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Move(void)
{
	CField* pField = ((CGame*)CManager::GetGamemode())->GetField();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	float fMoveAngle = InputToAngle();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = D3DXVECTOR3(0,0,0);
	CField::TYPE_TILE tile = CField::NONE;
	if (pKeyboard->GetKeyTrigger(DIK_W))
	{
		tile = pField->GetTile(m_nPosMapHeight - 1, m_nPosMapWidth);
		if (m_nPosMapHeight > 0 && tile != CField::TREE && tile != CField::STONE_BREAK&&tile != CField::STONE_UNBREAK)
		{
			pos.x += CUBE_SIZE;

			m_nPosMapHeight--;
		}
		rot.y = D3DXToRadian(-90);
		SetRot(rot);
	}
	if (pKeyboard->GetKeyTrigger(DIK_A))
	{
		tile = pField->GetTile(m_nPosMapHeight, m_nPosMapWidth - 1);
		if (m_nPosMapWidth > 0 && tile != CField::TREE && tile != CField::STONE_BREAK&&tile != CField::STONE_UNBREAK)
		{
			pos.z += CUBE_SIZE;
			m_nPosMapWidth--;
		}
		rot.y = D3DXToRadian(180);
		SetRot(rot);

	}
	if (pKeyboard->GetKeyTrigger(DIK_S))
	{
		tile = pField->GetTile(m_nPosMapHeight + 1, m_nPosMapWidth);
		if (m_nPosMapHeight < FIELD_HEIGHT - 1 && tile != CField::TREE && tile != CField::STONE_BREAK&&tile != CField::STONE_UNBREAK)
		{
			pos.x -= CUBE_SIZE;

			m_nPosMapHeight++;
		}
		rot.y = D3DXToRadian(90);
		SetRot(rot);
	}
	if (pKeyboard->GetKeyTrigger(DIK_D))
	{
		tile = pField->GetTile(m_nPosMapHeight, m_nPosMapWidth + 1);
		if (m_nPosMapHeight < FIELD_WIDTH - 1 && tile != CField::TREE && tile != CField::STONE_BREAK&&tile != CField::STONE_UNBREAK)
		{
			pos.z -= CUBE_SIZE;

			m_nPosMapWidth++;
		}
		rot.y = D3DXToRadian(-0);
		SetRot(rot);
	}
	
	SetPos(pos);
	LimitMap();
}

void CPlayer::LimitMap(void)
{
	D3DXVECTOR3 pos = GetPos();
	SetPos(pos);
}

CPlayer::ANGLE CPlayer::GetAngle(void)
{
	return m_angle;
}