//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRenderer;
class CFade;
class CSound;
class CInputKeyboard;
class ICGamemode;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager
{
public:
	//���[�h�^�C�v
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();     //�R���X�g���N�^
	~CManager();    //�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //�������֐�
	void Uninit(void);                                             //�I���֐�
	void Update(void);                                             //�X�V�֐�
	void Draw(void);                                               //�`��֐�
	static CRenderer* GetRenderer(void);                           //�Q�b�^�[
	//static CSound* GetSound(void){return m_pSound;}
	static void LoadFile(void);
	static void UnloadFiles(void);
	static void SetMode(const MODE mode);    // ���[�h�ؑ�
	static MODE GetMode(void);
	static CFade* GetFade(void){return m_pFade;}   // �t�F�[�h�̎擾
	static ICGamemode*CManager::GetGamemode(void);
	static CInputKeyboard* GetInput(void);
private:
    static CRenderer* m_pRenderer;    //�����_���̃|�C���^
    //static CSound* m_pSound;
    static CFade* m_pFade;            // �t�F�[�h�̃|�C���^
    static MODE m_mode;               // ���[�h�̕ϐ�
	static CInputKeyboard* m_pInput;
	static ICGamemode* m_pGamemode;
};

#endif
