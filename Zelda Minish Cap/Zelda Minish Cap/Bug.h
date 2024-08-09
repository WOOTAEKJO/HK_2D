#pragma once
#include "Character.h"
class CBug :
    public CCharacter
{
public:
    enum STATE{MOVE,DEAD,HIT,STATE_END};
public:
    CBug();
    virtual~CBug();
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
    
private:
    STATE				m_eCurState;
    STATE				m_ePreState;

    int                 m_iChange;          // �������� �����̸� m_TurnDirection ���� �ݴ�� �ٲ���� �ϱ� ������ ���.

private:
    int                m_ColCheck;
private:
    CObj*            m_StunEffect;

    
    
};

