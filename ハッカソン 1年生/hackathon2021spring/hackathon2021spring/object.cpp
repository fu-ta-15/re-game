//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
// object.cpp
// Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object.h"

#include "object2d.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject* CObject::m_pTop[PRIORITY_MAX] = {};
CObject* CObject::m_pCur[PRIORITY_MAX] = {};

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject::CObject(int nPriority)
{

	m_bDestroy = false;
    //リスト構造に追加
    m_nPriority = nPriority;
    if(m_pTop[nPriority] != NULL)
    {
        m_pCur[nPriority]->m_pNext = this;
    }
    else
    {
        m_pTop[nPriority] = this;
    }
    this->m_pPrev     = m_pCur[nPriority];
    this->m_pNext     = NULL;
    m_pCur[nPriority] = this;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject::~CObject()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject::UpdateAll(void)
{
    CObject* pNext     = NULL;
    CObject* pNextBuff = NULL;
    int ObjectCount    = 0;
    //リストに含まれるオブジェクトを更新
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
            while(pNext != NULL && !pNext->m_bDestroy)
            {
                pNextBuff = pNext->m_pNext;
                pNext->Update();
                pNext = pNextBuff;
                ObjectCount++;
            }
        }
    }

    //死亡フラグ立ってるやつを殺す
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
            while(pNext != NULL)
            {
                pNextBuff = pNext->m_pNext;
                if(pNext->m_bDestroy == true)
                {
                    pNext->Death();
                }
                pNext = pNextBuff;
            }
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject::DrawAll(void)
{
    CObject* pNext = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
            while(pNext != NULL)
            {
                pNext->Draw();
                pNext = pNext->m_pNext;
            }
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//全開放処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject::ReleaseAll(void)
{
    CObject* pNext     = NULL;
    CObject* pNextBuff = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
            while(pNext != NULL)
            {
                pNextBuff = pNext->m_pNext;
                pNext->Uninit();
                delete pNext;
                pNext = pNextBuff;
            }
        }
        m_pTop[nCount] = NULL;
        m_pCur[nCount] = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//開放処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject::Release(void)
{
    //死亡フラグを立てる
	m_bDestroy = true;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//リストから消去して自身も消える処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject::Death(void)
{
    //消えるときの処理
    if(this == m_pTop[m_nPriority])
    {
        m_pTop[m_nPriority] = m_pNext;
    }
    if(this == m_pCur[m_nPriority])
    {
        m_pCur[m_nPriority] = m_pPrev;
    }
    if(m_pNext != NULL)
    {
        m_pNext->m_pPrev = m_pPrev;
    }
    if(m_pPrev != NULL)
    {
        m_pPrev->m_pNext = m_pNext;
    }
    delete this;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject::SetObjType(OBJTYPE type)
{
    m_objType = type;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject** CObject::GetTop(void)
{
    return m_pTop;
}

CObject* CObject::GetNext(void)
{
    return m_pNext;
}

CObject* CObject::GetPrev(void)
{
    return m_pPrev;
}

CObject::OBJTYPE CObject::GetObjType(void)
{
    return m_objType;
}

