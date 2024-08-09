#pragma once
#include "Effect.h"
class CAttackEffect :
    public CEffect
{
public:
    CAttackEffect();
    virtual~CAttackEffect();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:

};

