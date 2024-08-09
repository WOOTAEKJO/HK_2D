#pragma once
#include "Obj.h"
class CSoulBullet :
    public CObj
{
public:
    enum STATE {FIRE=23,STATE_END};
public:
    CSoulBullet();
    ~CSoulBullet();
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
private:
    int     m_PlayerState;
    bool    m_bStart;

    
    
};

