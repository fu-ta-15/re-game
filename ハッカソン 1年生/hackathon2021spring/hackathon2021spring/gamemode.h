//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	gamemode.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_

#include "main.h"

class ICGamemode
{
public:
    ICGamemode(){};
    virtual ~ICGamemode(){};
    virtual HRESULT Init(void) = 0;
    virtual void Update(void)  = 0;
    virtual void Draw(void)    = 0;
    virtual void Uninit(void)  = 0;
};
#endif
