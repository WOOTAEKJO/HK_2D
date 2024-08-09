#pragma once
#include "UI.h"
class CSoulBase :
    public CUI
{
public:
    CSoulBase();
    virtual ~CSoulBase();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:

    
    
};

