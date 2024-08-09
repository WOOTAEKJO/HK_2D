#pragma once
#include "Obj.h"

class CCharacter :
    public CObj
{
public:
    CCharacter();
    virtual~CCharacter();
public:
    virtual void Initialize() PURE;
    virtual int Update() PURE;
    virtual void Late_Update() PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release() PURE;
    virtual void Collision() PURE;
    virtual void Act() PURE;
    virtual void Motion_Change() PURE;
public:
    int    Get_Soul() { return m_Soul; }
protected:
    void    Jump();
    void    JumpEX();
protected:
    void        Set_TurnMotion(int _n) {
        m_tFrame.iMotion = _n;
        m_TurnDirection = _n;
    }
protected:
    // 점프 관련
    bool				m_bJump;
    float				m_fJump_Power;
    float				m_fJump_Angle;

    // 이단 점프 관련
    int					m_iAdditionJump_MaxCount;
    int					m_iAdditionJump_Count;

    // 스텟 관련
    int                 m_HP;
    int                 m_Soul;
protected:
    

};

