#pragma once
#include "Obj.h"
class CBossWall :
    public CObj
{
public:
    CBossWall();
    virtual~CBossWall();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_WallTurn(int _n) { m_turn = _n; }
public:
    void    Set_Distroy() { m_Distroy = true; }
private:
    bool        m_Distroy;
    bool        m_Start;

    int         m_turn;
};

