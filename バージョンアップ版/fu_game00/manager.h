//#############################################################################
//
// �}�l�[�W���[�w�b�_�t�@�C�� [manager.h]
// Author : SUZUKI FUUTA
//
//#############################################################################
#ifndef _MANAGER_H_
#define _MANAGER_H_

//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define GET_DEVICE		(CManager::GetRenderer()->GetDevice())
#define D3D_DEVICE		(GET_DEVICE)

//-----------------------------------------------------------------------------
//�O���錾
//-----------------------------------------------------------------------------
class CRenderer;	// �����_���[
class CKey;			// �L�[�{�[�h
class CFade;		// �t�F�[�h
class CScene;		// �V�[��
class CTitle;		// �^�C�g��
class CTutorial;	// �`���[�g���A��
class CGame;		// �Q�[��
class CResult;		// ���U���g
class CPause;		// �|�[�Y
class CSound;		// �T�E���h
class CCamera;		// �J����
class CLight;		// ���C�g

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CManager
{
public:
	//-------------------------------------------------------------------------
	//���[�h�̗񋓌^
	//-------------------------------------------------------------------------
	typedef enum
	{
		MODE_TITLE = 0,	//�^�C�g�����
		MODE_TUTORIAL,	//�`���[�g���A�����
		MODE_GAME,		//�Q�[�����
		MODE_RESULT,	//���U���g���
		MODE_MAX		//MAX���l
	}MODE;

	//-------------------------------------------------------------------------
	// �����o�֐�
	//-------------------------------------------------------------------------
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void UninitMode(MODE mode);
	static void CreateMode(MODE mode);

	// Set�֐�
	static void SetMode(MODE mode);
	static void SetPause(bool bPause) { m_bPause = bPause; }

	// Get�֐�
	static MODE GetMode(void)				{ return m_mode; }
	static CRenderer *GetRenderer(void)		{ return m_pRenderer; }
	static CKey *GetKey(void)				{ return m_pKey; }
	static CFade * CManager::GetFade(void)	{ return m_pFade; }
	static CSound *GetSound(void)			{ return m_pSound; }
	static CPause *GetPause(void)			{ return m_pPause; }
	static CCamera *GetCamera(void)			{ return m_pCamera; }
	static CLight *GetLight(void)			{ return m_pLight; }


private:
	// �|�[�Y�̍X�V
	void PauseUpdate(void);

	static MODE				 m_mode;				// ���[�h
	static CRenderer		*m_pRenderer;			// �����_���[�|�C���^
	static CKey				*m_pKey;				// �L�[�|�C���^
	static CFade			*m_pFade;				// �t�F�[�h�N���X�̃|�C���^
	static CTitle			*m_pTitle;				// �^�C�g���N���X�̃|�C���^
	static CTutorial		*m_pTutorial;			// �`���[�g���A���̃|�C���^
	static CGame			*m_pGame;				// �Q�[���̃|�C���^
	static CResult			*m_pResult;				// ���U���g�̃|�C���^
	static CSound			*m_pSound;				// �T�E���h�̃|�C���^
	static CCamera			*m_pCamera;				// �J�����̃|�C���^
	static CLight			*m_pLight;				// ���C�g�̃|�C���^
	static CPause			*m_pPause;				// �|�[�Y�̃|�C���^
	static bool				 m_bPause;				// �|�[�Y�̃t���O
};

#endif // !_MANAGER_H_
