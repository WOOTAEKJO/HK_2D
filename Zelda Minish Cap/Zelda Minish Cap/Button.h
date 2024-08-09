#pragma once
#include "Obj.h"
class CButton :
    public CObj
{
public:
    CButton();
    virtual~CButton();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:

};

