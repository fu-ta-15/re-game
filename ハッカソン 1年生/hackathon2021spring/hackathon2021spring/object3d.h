//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene3d.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CModel;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I�u�W�F�N�g�N���X
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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
    D3DXVECTOR3 m_pos;      // �ʒu
    D3DXVECTOR3 m_rot;      // ��]���
    D3DXVECTOR3 m_size;    // �T�C�Y
};

#endif
