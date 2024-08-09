#pragma once
#include "framework.h"


class CLine
{
public:
	CLine();
	CLine(LINE& tLine);
	CLine(LINEPOINT _tLpoint, LINEPOINT _tRpoint, LINEID _LineID);
	~CLine();
public:
	void Render(HDC hDC);
	LINE* Get_Info() { return &m_tInfo; }
private:
	LINE m_tInfo;

};

