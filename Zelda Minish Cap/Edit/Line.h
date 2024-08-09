#pragma once
#include "framework.h"
//#include "ScrollMgr.h"


class CLine
{
public:
	CLine();
	CLine(LINE& tLine);	// 유정 0622 추가
	CLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint,LINEID _LineID);
	virtual ~CLine();

public:
	LINE*		Get_Info() { return &m_tInfo; }

public:

	virtual void		Render(HDC hDC);

protected:
	LINE		m_tInfo;

};

