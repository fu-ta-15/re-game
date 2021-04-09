//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	camera.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define CAMERA_VIEW_RANGE (1000000.0f)
#define CAMERA_DISTANCE_FROM_PLAYER (5.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_STAND (75.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_AIM (25.0f)
#define PLAYER_HEAD_HEIGHT (37.0f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CCamera
{
public:
    CCamera();
    ~CCamera();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void SetCamera(void);
    D3DXVECTOR3 GetRot(void);
    void SetRot(D3DXVECTOR3 rot);
    D3DXVECTOR3 GetPosR(void);

private:
    D3DXVECTOR3 m_posV;            //カメラの座標
    D3DXVECTOR3 m_posR;            //注視点の座標
    D3DXVECTOR3 m_vecU;            //カメラの上方向
    D3DXMATRIX m_mtxProjection;    //プロジェクションマトリックス
    D3DXMATRIX m_mtxView;          //ビューマトリックス
    D3DXVECTOR3 m_rot;
	float m_fDistance;
};

#endif
