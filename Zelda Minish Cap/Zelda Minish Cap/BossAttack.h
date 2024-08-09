#pragma once
#include "Obj.h"
class CBossAttack :
    public CObj
{
public:
    enum STATE{JUMPATTACK1=8,STATE_END};
public:
    CBossAttack();
    virtual~CBossAttack();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_BossState(int _n) { m_BossState = _n; }
    void    Set_TurnDir(int _n) { m_TurnDirection = _n; }
private:
    int     m_BossState;
};

