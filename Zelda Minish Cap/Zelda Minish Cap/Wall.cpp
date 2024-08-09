#include "Wall.h"
#include "CameraMgr.h"
#include "SoundMgr.h"

float W_fSound = 1.f;

CWall::CWall()
{
}

CWall::~CWall()
{
	Release();
}

void CWall::Initialize()
{
	m_eRender = GAMEOBJECT;

	m_fColC.x = m_tInfo.fCX;
	m_fColC.y = m_tInfo.fCY;

	m_ObjType = PWALL;
}

int CWall::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Collision();

	CObj::Update_Rect();
	return 0;
}

void CWall::Late_Update()
{
}

void CWall::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

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

void CWall::Release()
{
}

void CWall::Collision()
{
	if (m_CollisionCheck) {
		if (m_CollisionObjID == PMELEE) {
			CSoundMgr::Get_Instance()->PlaySoundW(L"P_sword_armour.wav", WALLSOUND,W_fSound);
			m_CollisionCheck = false;
		}
	}
}
