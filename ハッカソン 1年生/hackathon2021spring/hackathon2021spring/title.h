//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	title.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "main.h"
#include "gamemode.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CObject2D;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTitle : public ICGamemode
{
public:
	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	static HRESULT Load(void);
	static void Unload(void);
private:
	CObject2D* m_pTitleScreen;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};