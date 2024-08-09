#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{
}

CLine::CLine(LINE& tLine)	// ���� 0622 �߰�
	:m_tInfo(tLine)
{

}

CLine::CLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint, LINEID _LineID)
	: m_tInfo(_tLpoint, _tRpoint, _LineID)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	// ���� �ڵ�
	//MoveToEx(hDC, (int)m_tInfo.tLpoint.fX, (int)m_tInfo.tLpoint.fY, nullptr);
	//LineTo(hDC, (int)m_tInfo.tRpoint.fX, (int)m_tInfo.tRpoint.fY);

	//// ���� 0622 �߰�
	//float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();

	//MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)m_tInfo.tLpoint.fY, nullptr);
	//LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)m_tInfo.tRpoint.fY);

		// ī�޶� ���� �߰�
	/*LINE tLRenderPos = CCamera::Get_Instance()->Get_Line_RenderPos(m_tInfo);
	MoveToEx(hDC, (int)tLRenderPos.tLpoint.fX, (int)tLRenderPos.tLpoint.fY, nullptr);
	LineTo(hDC, (int)tLRenderPos.tRpoint.fX, (int)tLRenderPos.tRpoint.fY);*/

	/*float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();

	MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)m_tInfo.tLpoint.fY, nullptr);
	LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)m_tInfo.tRpoint.fY);*/

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScollY();

	if (m_tInfo.m_LineID == WALLLINE) {

		HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
		HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);

		MoveToEx(hDC, int(m_tInfo.tLpoint.fX+ fScrollX), (int)(m_tInfo.tLpoint.fY+ fScrollY), nullptr);
		LineTo(hDC, int(m_tInfo.tRpoint.fX+ fScrollX), (int)(m_tInfo.tRpoint.fY+ fScrollY));

		SelectObject(hDC, hPrePen);
		DeleteObject(hGreenPen);
	}
	else if (m_tInfo.m_LineID==GROUNDLINE) {

		HPEN hRedPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
		HPEN hPrePen = (HPEN)SelectObject(hDC, hRedPen);

		MoveToEx(hDC, int(m_tInfo.tLpoint.fX+ fScrollX), (int)(m_tInfo.tLpoint.fY+ fScrollY), nullptr);
		LineTo(hDC, int(m_tInfo.tRpoint.fX+ fScrollX), (int)(m_tInfo.tRpoint.fY+ fScrollY));

		SelectObject(hDC, hPrePen);
		DeleteObject(hRedPen);
	}


	/*MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)(m_tInfo.tLpoint.fY + fScrollY), nullptr);
	LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)(m_tInfo.tRpoint.fY + fScrollY));*/

}