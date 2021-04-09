//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//�I�u�W�F�N�g�N���X

class CObject
{
public:
    typedef enum
    {
        OBJTYPE_NONE = 0,
		OBJ_TYPE_DIRT,
		OBJ_TYPE_STONE_BREAK,
		OBJ_TYPE_STONE_UNBREAK,
		OBJ_TYPE_TREE,
		OBJ_TYPE_PLAYER,
        OBJ_TYPE_RAIL,
		OBJ_TYPE_TOOL,
    } OBJTYPE;
    CObject(int nPriority = 0);
    virtual ~CObject();
    virtual HRESULT Init(void) = 0;    //�������z�֐��Q
    virtual void Uninit(void)  = 0;
    virtual void Update(void)  = 0;
    virtual void Draw(void)    = 0;

    static void UpdateAll(void);    //�S�V�[�������Q
    static void DrawAll(void);
    static void ReleaseAll(void);
    void SetObjType(OBJTYPE type);
    static CObject** GetTop(void);
    CObject* GetNext(void);
    CObject* GetPrev(void);
    OBJTYPE GetObjType(void);

protected:
    void Release(void);    //�V�[���̊J��

private:
    void Death(void);
    static CObject* m_pTop[PRIORITY_MAX];
    static CObject* m_pCur[PRIORITY_MAX];
    CObject* m_pPrev;
    CObject* m_pNext;
    int m_nPriority;
    bool m_bDestroy;
    OBJTYPE m_objType;
};

#endif
