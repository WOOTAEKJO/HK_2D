#pragma once
#include "Effect.h"
class CSkillGetEffect :
    public CEffect
{
public:
    CSkillGetEffect();
    virtual~CSkillGetEffect();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;

public:
    void    Set_SkillNum(int _Num) { m_SkillNum = _Num; }
private:
    int  m_SkillNum;

    DWORD   m_DistroyTime;

};

