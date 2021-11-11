//*****************************************************************************
//
// �t�F�[�h���� [fade.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "fade.h"
#include "scene2D.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define FADE_SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))
#define FADE_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))
#define FADE_SPEED	(0.025f)

CFade::FADE CFade::m_FadeMode;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_FadeMode = FADE_OUT;
	m_modeNext = CManager::MODE_TITLE;

	m_pVtxBuff = NULL;
	m_pVtx = NULL;
	m_pos = FADE_POS;
	m_size = FADE_SIZE;
	m_col = WhiteColor;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// �t�F�[�h�̐���
//=============================================================================
CFade * CFade::Create(void)
{
	CFade* pFade = NULL;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init();
	}

	return pFade;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CFade::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	m_col = WhiteColor;
	m_pos = FADE_POS;
	m_size = FADE_SIZE;
	m_FadeMode = FADE_OUT;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e���_�̍��W
	m_pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	m_pVtx[0].rhw = 1.0f;
	m_pVtx[1].rhw = 1.0f;
	m_pVtx[2].rhw = 1.0f;
	m_pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	m_pVtx[0].col = m_col;
	m_pVtx[1].col = m_col;
	m_pVtx[2].col = m_col;
	m_pVtx[3].col = m_col;

	//�e�N�X�`�����W
	m_pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	m_pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_FadeMode != FADE_NONE)
	{// �t�F�[�h�̏�Ԃ�NONE����Ȃ��ꍇ
		if (m_FadeMode == FADE_IN)
		{// �t�F�[�h�C��

			//���l�����炵�Ă���
			m_col.a -= FADE_SPEED;

			// �F�𔽉f������
			SetCol(m_col);

			if (m_col.a <= 0.0f)
			{// A�l���O�ȉ��̏ꍇ
				m_FadeMode = FADE_NONE;		//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (m_FadeMode == FADE_OUT)
		{// �t�F�[�h�A�E�g

			//���l�𑝂₵�Ă���
			m_col.a += FADE_SPEED;

			// �F�𔽉f������
			SetCol(m_col);

			if (m_col.a >= 1.0f)
			{// A�l���P�ȏ�̏ꍇ
				CManager::SetMode(m_modeNext);	//���̃��[�h��
				m_FadeMode = FADE_IN;		//�t�F�[�h�C���ɐ؂�ւ�
			}
		}
	}
	else if (m_FadeMode == FADE_NONE)
	{
		//�����ɂ���
		m_col.a = 0.0f;

		// �F�𔽉f������
		SetCol(m_col);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		// 0//�`����J�n���钸�_�C���f�b�N�X
}

//=============================================================================
// �t�F�[�h���[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE mode)
{
	m_FadeMode = FADE_OUT;	// �t�F�[�h���
	m_modeNext = mode;		// ���̃��[�h��
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CFade::SetCol(D3DXCOLOR col)
{
	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	m_pVtx[0].col = col;
	m_pVtx[1].col = col;
	m_pVtx[2].col = col;
	m_pVtx[3].col = col;

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �t�F�[�h�̏��擾
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_FadeMode;
}
