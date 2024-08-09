#pragma once
#include "Line.h"
class CWallLine :
    public CLine
{
public:
    CWallLine();
    virtual ~CWallLine();

public:
    
    virtual void Render(HDC hDC) override;

};

