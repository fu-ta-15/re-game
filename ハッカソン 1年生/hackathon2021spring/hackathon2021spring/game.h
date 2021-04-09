//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	game.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#include "main.h"
#include "gamemode.h"
#include "camera.h"
#include "field.h"

class CField;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CGame : public ICGamemode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	static CField * GetField(void) { return m_pField; }
private:
	CCamera *m_pCamera;
	static CField *m_pField;
};