#pragma once
#include "Obj.h"
class CAttack :
    public CObj
{
public:
    enum STATE {SLASH=11,UPSLASH,DOWNSLASH,STATE_END};
public:
    CAttack();
    virtual ~CAttack();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_PlayerState(int _n) { m_PlayerState = _n; }
    void    Set_TurnDir(int _n) { m_TurnDirection = _n; }

    int    Get_AttSuc() { return m_AttackSuccess; }

    bool    Get_Success() { return m_bSuccess; }
private:
    int     m_PlayerState;
    bool    m_bStart;
    int     m_iChange;
private:
    int     m_AttackSuccess;
    bool    m_bSuccess;

    bool    m_OneCheck;
private:
    CObj* m_Effect;
};

