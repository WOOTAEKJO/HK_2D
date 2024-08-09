#include "Portal.h"
#include "CameraMgr.h"
#include "SceneMgr.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
	Release();
}

void CPortal::Initialize()
{
	m_ObjType = PORTAL;
	m_eRender = GAMEOBJECT;
}

int CPortal::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_CollisionCheck) {
		CSceneMgr::Get_Instance()->Scene_Change(m_NextStageID);
	}

	CObj::Update_Rect();
	return 0;
}

void CPortal::Late_Update()
{
}

void CPortal::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	/*HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(255, 0, 255));
	HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC,
		LONG(tRenderPos.fX - m_tInfo.fCX* 0.5f),
		LONG(tRenderPos.fY - m_tInfo.fCY * 0.5f),
		LONG(tRenderPos.fX + m_tInfo.fCX * 0.5f),
		LONG(tRenderPos.fY + m_tInfo.fCY * 0.5f));

	SelectObject(hDC, hPrePen);
	DeleteObject(hGreenPen);
	SelectObject(hDC, OldBrush);
	DeleteObject(myBrush);*/
}

void CPortal::Release()
{
}

void CPortal::Collision()
{
}
