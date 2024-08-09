#pragma once
#include "UI.h"
class CHP :
    public CUI
{
public:
    enum STATE {FULL,DESTORY,STATE_END};
public:
    CHP();
    virtual ~CHP();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void		Motion_Change();
    void        Set_AnimTurn() { m_AnimTurn = true; }
    STATE       Get_CurState() { return m_eCurState; }
private:
    bool m_bStart;

    STATE				m_eCurState;
    STATE				m_ePreState;

    CObj* m_Owner;

private:
    bool                m_AnimTurn; // true가 되면 애니메이션 교체.
    
    
};

