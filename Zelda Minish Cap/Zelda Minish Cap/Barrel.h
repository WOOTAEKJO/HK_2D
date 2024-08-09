#pragma once
#include "Obj.h"
class CBarrel :
    public CObj
{
public:
    CBarrel();
    virtual~CBarrel();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_Move() { m_bMove = true; }
    bool    Get_Move() { return m_bMove; }
public:
    void    Set_PlayerAttack() { m_bPlayerAttack = true; }
    void    Set_TurnDir(int _n) { m_TurnDirection = _n; }
private:
    bool    m_bMove;    //움직임 제어
    bool    m_bPlayerAttack;
};

