#pragma once
#include "UI.h"
class CSoul :
    public CUI
{
public:
    enum STATE{ ZERO,FIVE, TEN, FIFTEEN,TWENTY,  STATE_END};
public:
    CSoul();
    virtual~CSoul();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Montion_Change();
    void    Act();
private:
    int                 m_Soul;

    STATE				m_eCurState;
    STATE				m_ePreState;
    
};

