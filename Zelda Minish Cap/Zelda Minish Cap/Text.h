#pragma once
#include "Obj.h"
class CText :
    public CObj
{
public:
    CText();
    virtual~CText();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void Set_Text(const TCHAR* _text) { M_Text = _text; }
private:
    const TCHAR* M_Text;
};

