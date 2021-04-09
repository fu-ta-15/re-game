//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene3d.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CModel;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//オブジェクトクラス
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CObject3D : public CObject
{
public:
    CObject3D();
    virtual ~CObject3D();
    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    void SetPosition(D3DXVECTOR3 pos);
    void SetRotation(D3DXVECTOR3 rot);
    void SetScale(D3DXVECTOR3 scale);
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetRot(void);
    D3DXVECTOR3 GetSize(void);

private:
    D3DXVECTOR3 m_pos;      // 位置
    D3DXVECTOR3 m_rot;      // 回転情報
    D3DXVECTOR3 m_size;    // サイズ
};

#endif
