#include "Obj.h"
#include "CameraMgr.h"
#include "BmpMgr.h"

CObj::CObj() :m_bDead(false), m_pFrameKey(nullptr), m_eRender(RENDER_END), m_fSpeed(0.f), m_TurnDirection(0), m_fAngle(0.f),
m_fAccel(0.f), m_fSpeed_Vertical(0.f), m_bChangeM(true), m_CollisionCheck(false), m_ObjType(OBJID_END), m_Damage(0),
m_HitDamage(0), m_ATTR_Check(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
	ZeroMemory(&m_fColC, sizeof(m_fColC));
	ZeroMemory(&m_fATTRC, sizeof(m_fATTRC));
	ZeroMemory(&m_CollisionPos, sizeof(m_CollisionPos));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	/*m_tCollider.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f)*0.25f);
	m_tCollider.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tCollider.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f) * 0.25f);
	m_tCollider.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));*/

	m_tCollider.left = LONG(m_tInfo.fX - (m_fColC.x*0.5f));
	m_tCollider.top = LONG(m_tInfo.fY - (m_fColC.y * 0.5f));
	m_tCollider.right = LONG(m_tInfo.fX + (m_fColC.x * 0.5f));
	m_tCollider.bottom = LONG(m_tInfo.fY + (m_fColC.y * 0.5f));

	m_AttackRange.left = LONG(m_tInfo.fX - (m_fATTRC.x*0.5f));
	m_AttackRange.top = LONG(m_tInfo.fY - (m_fATTRC.y * 0.5f));
	m_AttackRange.right = LONG(m_tInfo.fX + (m_fATTRC.x * 0.5f));
	m_AttackRange.bottom = LONG(m_tInfo.fY + (m_fATTRC.y * 0.5f));
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
	{
			++m_tFrame.iFrameStart;

			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd) {
				m_tFrame.iFrameStart = 0;
			}
			m_tFrame.dwTime = GetTickCount64();
	}
}

void CObj::FramSave(int _start, int _end, int _turnDir, int _dwspeed)
{
	m_tFrame.iFrameStart = _start;
	m_tFrame.iFrameEnd = _end;
	m_tFrame.iMotion = _turnDir;
	m_tFrame.dwSpeed = _dwspeed;
	m_tFrame.dwTime = GetTickCount64();
}

void CObj::Camera_Col_Render_LR(HDC hDC, int _R, int _G, int _B)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	if (m_TurnDirection == TURNRIGHT)
	{
		GdiTransparentBlt(hDC,
			(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
			(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f),
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(_R, _G, _B)); // 제거하고자 하는 색상
	}
	else if (m_TurnDirection == TURNLEFT)
	{
		GdiTransparentBlt(hDC,
			(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
			(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f),
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			(m_tFrame.iFrameEnd - m_tFrame.iFrameStart) * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(_R, _G, _B)); // 제거하고자 하는 색상
	}


	//HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
	//HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//Rectangle(hDC,
	//	LONG(tRenderPos.fX - m_fColC.x * 0.5f),
	//	LONG(tRenderPos.fY - m_fColC.y * 0.5f),
	//	LONG(tRenderPos.fX + m_fColC.x * 0.5f),
	//	LONG(tRenderPos.fY + m_fColC.y * 0.5f));

	//SelectObject(hDC, hPrePen);
	//DeleteObject(hGreenPen);
	//SelectObject(hDC, OldBrush);
	//DeleteObject(myBrush);
}

void CObj::Camera_Col_Render_UD(HDC hDC, int _R, int _G, int _B)
{


	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);


	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
		(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f),
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		m_tFrame.iMotion * (int)m_tInfo.fCX, // 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iFrameStart * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(_R, _G, _B)); // 제거하고자 하는 색상
	// 프레임이 상하로 존재 할 때
	//m_TurnDirection 이거를 반대로 해줘야 한다.

	/*HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
	HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC,
		LONG(tRenderPos.fX - m_fColC.x * 0.5f),
		LONG(tRenderPos.fY - m_fColC.y * 0.5f),
		LONG(tRenderPos.fX + m_fColC.x * 0.5f),
		LONG(tRenderPos.fY + m_fColC.y * 0.5f));

	SelectObject(hDC, hPrePen);
	DeleteObject(hGreenPen);
	SelectObject(hDC, OldBrush);
	DeleteObject(myBrush);*/
}
