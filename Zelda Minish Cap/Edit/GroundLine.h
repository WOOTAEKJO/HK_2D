#pragma once
#include "Line.h"
class CGroundLine :
    public CLine
{
    
public:
    CGroundLine();
    ~CGroundLine();
public:
    virtual void Render(HDC hDC) override;
};

