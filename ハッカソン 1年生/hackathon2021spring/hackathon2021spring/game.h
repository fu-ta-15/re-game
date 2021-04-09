//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	game.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "main.h"
#include "gamemode.h"
#include "camera.h"
#include "field.h"

class CField;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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