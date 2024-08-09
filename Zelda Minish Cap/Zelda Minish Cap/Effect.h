#pragma once
#include "Obj.h"
class CEffect :
    public CObj
{
public:
    CEffect();
    virtual~CEffect();
public:
    virtual void Initialize() PURE;
    virtual int Update() PURE;
    virtual void Late_Update() PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release() PURE;
    virtual void Collision() PURE;
protected:

};

