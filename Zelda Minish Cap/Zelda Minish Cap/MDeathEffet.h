#pragma once
#include "Effect.h"
class CMDeathEffet :
    public CEffect
{
public:
    CMDeathEffet();
    virtual~CMDeathEffet();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_MonsterType(int _n) { m_MonsterType = _n; }
private:
    int        m_MonsterType;
};

