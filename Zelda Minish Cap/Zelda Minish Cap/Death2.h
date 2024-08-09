#pragma once
#include "Obj.h"
class CDeath2 :
    public CObj
{
public:
    CDeath2();
    virtual~CDeath2();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_TurnDir(int _n) { m_TurnDirection = _n; }
private:
    float   m_Distance;
};

