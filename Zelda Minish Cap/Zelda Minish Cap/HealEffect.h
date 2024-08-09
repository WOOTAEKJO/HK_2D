#pragma once
#include "Effect.h"
class CHealEffect :
    public CEffect
{
public:
    CHealEffect();
    virtual~CHealEffect();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:
};

