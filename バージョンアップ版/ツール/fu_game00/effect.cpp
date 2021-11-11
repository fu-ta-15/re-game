//*****************************************************************************
//
// �G�t�F�N�g���� [effect.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "effect.h"
#include "renderer.h"
#include "game.h"
#include "collision.h"
#include "tutorial.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect() : CScene2D(OBJ_EFFECT1)
{
	this->m_bUse = true;		// �`�悷�鍇�}
	this->m_col = WhiteColor;	// �F�̏�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// �G�t�F�N�g�|���S���̂̐���
//=============================================================================
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �N���X�̃|�C���^�ϐ�
	CEffect *pEffect = new CEffect;

	// NULL�`�F�b�N
	if (pEffect != NULL)
	{
		pEffect->m_pos = pos;		// �ʒu
		pEffect->m_size = size;		// �T�C�Y
		pEffect->m_bMove = false;	// �ړ����邩���Ȃ���
		pEffect->Init();			// ������
	}

	return pEffect;
}

//=============================================================================
// �p�[�e�B�N���p�̃G�t�F�N�g����
//=============================================================================
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXVECTOR3 move, LPDIRECT3DTEXTURE9 ptex)
{
	// �N���X�̃|�C���^�ϐ�
	CEffect *pEffect = new CEffect;

	// NULL�`�F�b�N
	if (pEffect != NULL)
	{
		pEffect->m_pos = pos;		// �ʒu
		pEffect->m_size = size;		// �T�C�Y
		pEffect->m_move = move;		// �ړ���
		pEffect->SetTexture(ptex);	// �e�N�X�`��
		pEffect->m_bMove = true;	// �ړ��̍��}
		pEffect->Init();			// ������
	}

	return pEffect;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CEffect::Init(void)
{
	// �|���S���̏���������
	CScene2D::Init(m_pos, m_size);

	// �ʒu�̐ݒ�
	CScene2D::SetPos(m_pos);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	// �ʒu�̍X�V
	CScene2D::SetPos(m_pos);

	// �F�̍X�V
	CScene2D::SetCol(m_col);

	// �`�悷�邩�̗L���̍X�V
	CScene2D::SetUse(m_bUse);

	// �����ړ�����Ȃ�
	if (m_bMove)
	{
		// �ړ��ʂ̉��Z
		m_pos += m_move;

		// �ړ��ʂ̌���
		m_move.x += (0 - m_move.x) * 0.025f;
		m_move.y += (0 - m_move.y) * 0.025f;

		// �����x�̉��Z
		m_col.a -= 0.055f;

		// �n�ʂƂ̓����蔻��
		CollisionField();

		// �����x���[���𒴂�����
		if (m_col.a < 0)
		{
			// �|���S���̊J��
			CScene2D::Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	// ���Z����
	D3D_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CScene2D::Draw();

	// �ʏ퍇���ɖ߂�
	D3D_DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3D_DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3D_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// �n�ʂƂ̓����蔻��
//=============================================================================
void CEffect::CollisionField(void)
{

}

