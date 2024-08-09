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

    int                 m_iChange;          // 프레임이 상하이면 m_TurnDirection 값을 반대로 바꿔줘야 하기 때문에 사용.

private:
    int                m_ColCheck;
private:
    CObj*            m_StunEffect;

    
    
};

