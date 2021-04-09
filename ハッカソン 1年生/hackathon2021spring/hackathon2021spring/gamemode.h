//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	gamemode.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

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
