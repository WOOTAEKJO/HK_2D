#pragma once
#include "Character.h"
class CHusk :
    public CCharacter
{
public:
    enum STATE { IDLE,MOVE, HIT, ATTACK, DEAD, STATE_END };

public:
    CHusk();
    virtual~CHusk();
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
    bool              m_HitCheck;
    DWORD             m_HitTime;
private:
    int               m_iChange;          // �������� �����̸� m_TurnDirection ���� �ݴ�� �ٲ���� �ϱ� ������ ���.
    bool              m_FrameStop;
    int               m_SaveDir;
private:
    CObj* m_StunEffect;
private:
    bool                m_OneCheck;
    float               m_HitSpeed;

};

