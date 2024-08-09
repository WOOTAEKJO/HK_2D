#pragma once
#include "Obj.h"
class CHive :
    public CObj
{
public:
    CHive();
    virtual~CHive();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:
    int     m_HP;
    bool    m_HitCheck;
};

