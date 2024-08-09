#pragma once
#include "NPC.h"
class CNPC1 :
    public CNPC
{
public:
    CNPC1();
    virtual~CNPC1();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
    virtual void Act() override;
    virtual void Motion_Change() override;
public:
    void    ATTR_Check();
private:

    
};

