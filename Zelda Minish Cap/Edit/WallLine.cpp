#include "WallLine.h"
#include "ScrollMgr.h"

CWallLine::CWallLine()
{
}

CWallLine::~CWallLine()
{
}

void CWallLine::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();

	HPEN hRedPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
	HPEN hPrePen = (HPEN)SelectObject(hDC, hRedPen);

	MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)m_tInfo.tLpoint.fY, nullptr);
	LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)m_tInfo.tRpoint.fY);
}
