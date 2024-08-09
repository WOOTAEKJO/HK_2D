#include "Line.h"
#include "CameraMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CLine::CLine()
{
}

CLine::CLine(LINE& tLine)
	:m_tInfo(tLine)
{
}

CLine::CLine(LINEPOINT _tLpoint, LINEPOINT _tRpoint, LINEID _LineID):
	m_tInfo(_tLpoint, _tRpoint, _LineID)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	/*HPEN hRedPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
	HPEN hPrePen = (HPEN)SelectObject(hDC, hRedPen);*/




	//SCENEID CurScene = SC_END;
	//CurScene = CSceneMgr::Get_Instance()->Get_CurScene();sh

	//if (CurScene == SC_EDIT) {

	//	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();
	//	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScollY();

	//	if (m_tInfo.m_LineID == WALLLINE) {

	//		HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
	//		HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);

	//		MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)(m_tInfo.tLpoint.fY + fScrollY), nullptr);
	//		LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)(m_tInfo.tRpoint.fY + fScrollY));

	//		SelectObject(hDC, hPrePen);
	//		DeleteObject(hGreenPen);
	//	}
	//	else if (m_tInfo.m_LineID == GROUNDLINE) {

	//		HPEN hRedPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
	//		HPEN hPrePen = (HPEN)SelectObject(hDC, hRedPen);

	//		MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)(m_tInfo.tLpoint.fY + fScrollY), nullptr);
	//		LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)(m_tInfo.tRpoint.fY + fScrollY));

	//		SelectObject(hDC, hPrePen);
	//		DeleteObject(hRedPen);
	//	}
	//}
	//else {
	//	LINE tRenderPos = CCameraMgr::Get_Instance()->Get_Line_RenderPos(m_tInfo);

	//	/*MoveToEx(hDC, (int)m_tInfo.tLpoint.fX, (int)m_tInfo.tLpoint.fY, nullptr);
	//	LineTo(hDC, (int)m_tInfo.tRpoint.fX, (int)m_tInfo.tRpoint.fY);*/
	//	MoveToEx(hDC, (int)tRenderPos.tLpoint.fX, (int)tRenderPos.tLpoint.fY, nullptr);
	//	LineTo(hDC, (int)tRenderPos.tRpoint.fX, (int)tRenderPos.tRpoint.fY);

	//	if (m_tInfo.m_LineID == WALLLINE) {

	//		HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
	//		HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);

	//		MoveToEx(hDC, (int)tRenderPos.tLpoint.fX, (int)tRenderPos.tLpoint.fY, nullptr);
	//		LineTo(hDC, (int)tRenderPos.tRpoint.fX, (int)tRenderPos.tRpoint.fY);

	//		SelectObject(hDC, hPrePen);
	//		DeleteObject(hGreenPen);
	//	}
	//	else if (m_tInfo.m_LineID == GROUNDLINE) {

	//		HPEN hRedPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
	//		HPEN hPrePen = (HPEN)SelectObject(hDC, hRedPen);

	//		MoveToEx(hDC, (int)tRenderPos.tLpoint.fX, (int)tRenderPos.tLpoint.fY, nullptr);
	//		LineTo(hDC, (int)tRenderPos.tRpoint.fX, (int)tRenderPos.tRpoint.fY);

	//		SelectObject(hDC, hPrePen);
	//		DeleteObject(hRedPen);
	//	}
	//}
}
