#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "CameraMgr.h"

CTile::CTile():m_iOption(NON), m_iDrawID(NON)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Å¸ÀÏ.bmp", L"Tile");
}

int CTile::Update()
{

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	//HPEN MyPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	//HPEN OldPen = (HPEN)SelectObject(hDC, MyPen);

	SCENEID CurScene = SC_END;
	CurScene = CSceneMgr::Get_Instance()->Get_CurScene();
	
	if (CurScene == SC_EDIT) {
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();
		float	fScrollY = CScrollMgr::Get_Instance()->Get_ScollY();

		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");

		if (m_iDrawID != NON) {
			BitBlt(hDC,
				m_tRect.left + fScrollX,
				m_tRect.top + fScrollY,
				TILECX,
				TILECY,
				hMemDC,
				TILECX * m_iDrawID,
				0,
				SRCCOPY);
		}
		else {
			Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
				m_tRect.right - fScrollX, m_tRect.bottom - fScrollY);
		}

		//SelectObject(hDC, OldPen);
		SelectObject(hDC, OldBrush);
		//DeleteObject(MyPen);
		DeleteObject(myBrush);
	}
	else if (CurScene == SC_STAGE1) {
		INFO tRenderPos =CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);
		//INFO tRenderPos = CCameraMgr::Get_Instance()->Get_LookPos();
		/*Rectangle(hDC, m_tRect.left + tRenderPos.fX, m_tRect.top + tRenderPos.fY,
			m_tRect.right - tRenderPos.fX, m_tRect.bottom - tRenderPos.fY);*/

		/*float	fScrollX = CScrollMgr::Get_Instance()->Get_ScollX();
		float	fScrollY = CScrollMgr::Get_Instance()->Get_ScollY();*/

		//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");

		if (m_iDrawID != NON) {
			/*BitBlt(hDC,
				m_tRect.left + tRenderPos.fX,
				m_tRect.top + tRenderPos.fY,
				TILECX,
				TILECY,
				hMemDC,
				TILECX * m_iDrawID,
				0,
				SRCCOPY);*/
			HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
			HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
			HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			/*Rectangle(hDC,
				LONG(tRenderPos.fX - m_tInfo.fCX * 0.5f),
				LONG(tRenderPos.fY - m_tInfo.fCY * 0.5f),
				LONG(tRenderPos.fX + m_tInfo.fCX * 0.5f),
				LONG(tRenderPos.fY + m_tInfo.fCY * 0.5f));*/

			Rectangle(hDC,
				LONG(tRenderPos.fX - m_tInfo.fCX * 0.5f),
				LONG(tRenderPos.fY - m_tInfo.fCY * 0.5f),
				LONG(tRenderPos.fX + m_tInfo.fCX * 0.5f),
				LONG(tRenderPos.fY + m_tInfo.fCY * 0.5f));

			SelectObject(hDC, hPrePen);
			DeleteObject(hGreenPen);
			SelectObject(hDC, OldBrush);
			DeleteObject(myBrush);
		}
		else {

			HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC,
				LONG(tRenderPos.fX - m_tInfo.fCX * 0.5f),
				LONG(tRenderPos.fY - m_tInfo.fCY * 0.5f),
				LONG(tRenderPos.fX + m_tInfo.fCX * 0.5f),
				LONG(tRenderPos.fY + m_tInfo.fCY * 0.5f));

			/*Rectangle(hDC, m_tRect.left + tRenderPos.fX, m_tRect.top + tRenderPos.fY,
				m_tRect.right - tRenderPos.fX, m_tRect.bottom - tRenderPos.fY);*/

			//SelectObject(hDC, OldPen);
			SelectObject(hDC, OldBrush);
			//DeleteObject(MyPen);
			DeleteObject(myBrush);
		}

		
		
	}

}

void CTile::Release()
{
}

void CTile::Collision()
{
}
