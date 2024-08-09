#pragma once
#include "Character.h"
class CBee :
    public CCharacter
{
public:
    enum STATE{IDLE,HIT,ATTACK,DEATH,TURN,STATE_END};
public:
    CBee();
    virtual~CBee();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
    virtual void Act() override;
    virtual void Motion_Change() override;
public:
    void    ATTR_Check();
private:
    STATE				m_eCurState;
    STATE				m_ePreState;

private:
    INFO              m_SaveInfo;
    bool              m_HitCheck;
    DWORD             m_HitTime;
private:
    int               m_ePreTurnDir;
    bool               m_onecheck;
private:
    CObj* m_StunEffect;
};

