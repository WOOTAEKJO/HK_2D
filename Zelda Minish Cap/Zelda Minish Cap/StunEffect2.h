#pragma once
#include "Effect.h"
class CStunEffect2 :
    public CEffect
{
public:
    CStunEffect2();
    virtual~CStunEffect2();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:
};

