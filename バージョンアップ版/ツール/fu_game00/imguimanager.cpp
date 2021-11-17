//*****************************************************************************
//
// ImGui�}�l�[�W������ [imguimanager.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "imguimanager.h"
#include "imgui_ja_gryph_ranges.h"
#include "game.h"
#include "manager.h"
#include "camera.h"
#include "light.h"

//=============================================================================
// ImGui�̏���������
//=============================================================================
HRESULT ImGuiMana::Init(HWND hWnd, D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pD3DDevice)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("imgui/Fonts/Gothic.ttc", 14.0f, nullptr, Japanese::glyphRangesJapanese);
	ImGui::StyleColorsLight();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pD3DDevice);

	return S_OK;
}

//=============================================================================
// ImGui�̏I������
//=============================================================================
void ImGuiMana::Uninit(void)
{
	// DX9�pImgui�̃V���b�g�_�E��
	ImGui_ImplDX9_Shutdown();

	// Win32Imgui�̃V���b�g�_�E��
	ImGui_ImplWin32_Shutdown();

	// �e�L�X�g�̊J��
	ImGui::DestroyContext();
}

//=============================================================================
// ImGui�̍X�V����
//=============================================================================
void ImGuiMana::Update(void)
{
	// ���݂̃��[�h�̎擾
	CManager::MODE mode = CManager::GetMode();

	// DX9�̃t���[������
	ImGui_ImplDX9_NewFrame();

	// Win32�̃t���[������
	ImGui_ImplWin32_NewFrame();

	// �t���[���̐���
	ImGui::NewFrame();

	// ���[�h�擾
	if (mode == CManager::MODE_GAME)
	{
		// Imgui�E�B���h�E����
		ImGui::Begin(u8"���b�V���|���S��");

		// ���b�V������
		MeshList::MeshInfo();

		// Imgui�E�B���h�E��������
		ImGui::End();
	}

	// Imgui�E�B���h�E����
	ImGui::Begin(u8"�J�����⃉�C�getc");

	Option::OperationExplanation();

	// Imgui�E�B���h�E��������
	ImGui::End();

	// �t���[�������I��
	ImGui::EndFrame();
}


//=============================================================================
// ImGui�̕`�揈��
//=============================================================================
void ImGuiMana::Draw(void)
{
	// DX9�ł̃����_���[�J�n
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//=============================================================================
// ImGui�̕`��I������
//=============================================================================
void ImGuiMana::DrawEnd(HRESULT result, LPDIRECT3DDEVICE9 pD3DDevice, D3DPRESENT_PARAMETERS d3dpp)
{
	// �ȉ��ɂ�������������Ă�����
	if (result == D3DERR_DEVICELOST && pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		// DX�X�Ŏg�p���Ă����I�u�W�F�N�g��f�o�C�X�̔j��
		ImGui_ImplDX9_InvalidateDeviceObjects();
		HRESULT hr = pD3DDevice->Reset(&d3dpp);
		if (hr == D3DERR_INVALIDCALL)
			IM_ASSERT(0);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

//=============================================================================
// ImGui�̃��b�V���|���S���̏��
//
// �E�����ݒ�/�g�̕\���̐ݒ�c
//=============================================================================
void MeshList::MeshInfo(void)
{
	// �f���E�B���h�E�̕\���ؑ�Button
	if (ImGui::Button(u8"[�f���E�B���h�E�̐���]"))
	{
		// �f���E�B���h�E�̕\���؂�ւ�
		m_bDemo = m_bDemo ? false : true;
	}

	// true�̏ꍇ�̂݃f���E�B���h�E�\��
	if (m_bDemo)
	{
		// �f���E�B���h�E�̐���
		ImGui::ShowDemoWindow();
	}

	// �󔒂̍s�𐶐�
	ImGui::Spacing();

	// ���b�V���̏��m�[�h
	if (ImGui::TreeNode(u8"---���---"))
	{

		// ��������ۂ̏��
		if (ImGui::TreeNode(u8"---����---"))
		{
			// ���b�V���̐���
			CreateMeshMenu();

			// �m�[�h�����I��
			ImGui::TreePop();
		}

		// �󔒂̍s�𐶐�
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		// �g�̕\���̏��
		if (ImGui::TreeNode(u8"---�g�̕\��---"))
		{
			// �g�̕\��
			MeshWave();

			// �m�[�h�����I��
			ImGui::TreePop();
		}

		// �m�[�h�����I��
		ImGui::TreePop();
	}
}

//=============================================================================
// ���b�V���|���S���ɂ��g�̕\���ݒ�
//=============================================================================
void MeshList::MeshWave(void)
{
	// �J�E���g�J�n�E��~�̐؂�ւ��{�^��
	if (ImGui::Button(u8"[�Đ�]�E[��~]"))
	{
		// �����ꂽ��Đ��ƒ�~�̂ǂ��炩�ɂ���
		m_bTimeStart = m_bTimeStart ? false : true;
	}

	// �t���[���J�E���g�J�n����Ă�����
	if (m_bTimeStart)
	{
		// �J�E���g�A�b�v
		m_nTime++;
	}

	if (m_pMesh != NULL)
	{
		m_pMesh->MeshWave(m_WaveCenter, m_nTime, m_fHeight, m_nCycle);
	}

	// �g�̏ڍאݒ�m�[�h
	if (ImGui::TreeNode(u8"---�g�̏ڍאݒ�---"))
	{
		// �g�Ƃ���̍���
		ImGui::InputFloat(u8"����", &m_fHeight, 0.5f);

		// �g�̎����̒���
		ImGui::InputInt(u8"����", &m_nCycle, 1);

		// �g���N�������_�̐ݒ�m�[�h
		if (ImGui::TreeNode(u8"�k��"))
		{
			// �g���N�������_�̐ݒ�
			ImGui::InputFloat(u8"X���W", &m_WaveCenter.x, 0.5f);
			ImGui::InputFloat(u8"Z���W", &m_WaveCenter.z, 0.5f);

			// �m�[�h�̏I��
			ImGui::TreePop();
		}

		// �t���[���J�E���g�\���m�[�h
		if (ImGui::TreeNode("FRAME"))
		{
			// �t���[���̕\��
			ImGui::Text(u8" �J�E���g�� : %d", m_nTime);

			// �m�[�h�̏I��
			ImGui::TreePop();
		}
		// �m�[�h�̏I��
		ImGui::TreePop();
	}
}

//=============================================================================
// ���b�V���������邽�߂̏ڍאݒ�
//=============================================================================
void MeshList::CreateMeshMenu(void)
{
	// ���ɕ��ׂ邽�߂̋󔒂̏���
	float SpacingButton = ImGui::GetStyle().ItemInnerSpacing.x;

	// Button�����s��������
	ImGui::PushButtonRepeat(true);

	// ���b�V���̐���Button
	if (ImGui::Button(u8"[�����{�^��]"))
	{
		// NULL�ł���ΐ�������
		if (m_pMesh == NULL)
		{// NULL�`�F�b�N

			// �i�o�l�p�̒��ɓ���p�c�̖{���E���̖{���E�ʒu�E�T�C�Y�j
			m_pMesh = CMesh3D::Create(m_nVertical, m_nSide, m_pos, m_size);
		}
	}

	// �󔒂̐���
	ImGui::SameLine(0.0f, SpacingButton);

	// ���b�V���̍폜�{�^��
	if (ImGui::Button(u8"[�폜�{�^��]"))
	{
		// NULL�łȂ���΍폜����
		if (m_pMesh != NULL)
		{// NULL�`�F�b�N

			// ���b�V���̊J��
			m_pMesh->Uninit();

			// NULL���
			m_pMesh = NULL;
		}
	}

	// �󔒂̐���
	ImGui::SameLine(0.0f, SpacingButton);

	// �ݒ肵�Ă������l�����Z�b�g
	if (ImGui::Button(u8"[���l���Z�b�g]"))
	{
		m_nVertical = 0;	  // �c���̖{��
		m_nSide = 0;		  // �����̖{��
		m_pos = ZeroVector3;  // �ʒu
		m_size = ZeroVector3; // �T�C�Y
	}

	// �J��Ԃ��\���̏I��
	ImGui::PopButtonRepeat();

	// ���݂̐��l�\���E���l���͉\�E�{�^���łP�}�\
	ImGui::InputInt(u8"�c��", &m_nVertical, 1);

	// ���E�l���z���Ă�����߂�����
	if (m_nVertical < 0) { m_nVertical = 0; }
	else if (m_nVertical > 150) { m_nVertical = 150; }

	// ���݂̐��l�\���E���l���͉\�E�{�^���łP�}�\
	ImGui::InputInt(u8"����", &m_nSide, 1);

	// ���E�l���z���Ă�����߂�����
	if (m_nSide < 0) { m_nSide = 0; }
	else if (m_nSide > 150) { m_nSide = 150; }

	// ���b�V���̈ʒu�ݒ�m�[�h
	if (ImGui::TreeNode(u8"---�ʒu---"))
	{
		// ���b�V�������J�n�̈ʒu�ݒ�
		ImGui::InputFloat(u8"X���W", &m_pos.x, 0.5f);
		ImGui::InputFloat(u8"Y���W", &m_pos.y, 0.5f);
		ImGui::InputFloat(u8"Z���W", &m_pos.z, 0.5f);

		// �m�[�h�̏I��
		ImGui::TreePop();
	}

	// ���b�V���̃T�C�Y�ݒ�m�[�h
	if (ImGui::TreeNode(u8"---�T�C�Y---"))
	{
		// ���b�V���̏c�Ɖ��̐ݒ�
		ImGui::InputFloat(u8"���T�C�Y", &m_size.x, 0.5f);
		ImGui::InputFloat(u8"�c�T�C�Y", &m_size.z, 0.5f);

		// �m�[�h�̏I��
		ImGui::TreePop();
	}

	TextureMake::TextureLoad();
}

void TextureMake::TextureLoad(void)
{

	if (ImGui::TreeNode(u8"�e�N�X�`������"))
	{




		// �m�[�h�̏I��
		ImGui::TreePop();
	}

}

void TextureMake::TextureBind(void)
{
}


void LightOption::LightMove(void)
{
	// ���C�g�̏��擾
	CLight *pLight = CManager::GetLight();

}

void Option::OperationExplanation(void)
{
	if (ImGui::TreeNode(u8"�J��������"))
	{
		ImGui::Text(u8"�ړ����@");
		ImGui::Text(u8"W/�O : S/�� : A/�E : D/��");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text(u8"����");
		ImGui::Text(u8"Q/���_�̍����� : E/���_�̉E����");
		ImGui::Text(u8"Z/�����_�̍����� : C/�����_�̉E����");

		// �m�[�h�̏I��
		ImGui::TreePop();
	}
}
