#pragma once
#include "Character.h"
class CBeetle :
    public CCharacter
{public:
    CBeetle();
    virtual~CBeetle();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
    virtual void Act() override;
    virtual void Motion_Change() override;
private:

};

