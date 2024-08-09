#pragma once
#include "Effect.h"
class CStunEffect :
    public CEffect
{
public:
    CStunEffect();
    virtual~CStunEffect();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:
};

