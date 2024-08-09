#pragma once
#include "UI.h"
class CBossTotem :
    public CUI
{
public:
    CBossTotem();
    virtual~CBossTotem();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:
};

