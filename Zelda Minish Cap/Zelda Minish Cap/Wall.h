#pragma once
#include "Obj.h"
class CWall :
    public CObj
{
public:
    CWall();
    virtual ~CWall();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
private:


    
    

};

