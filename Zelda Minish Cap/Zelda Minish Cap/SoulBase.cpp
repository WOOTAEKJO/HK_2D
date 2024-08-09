#include "SoulBase.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "CameraMgr.h"


CSoulBase::CSoulBase()
{
}

CSoulBase::~CSoulBase()
{
	Release();
}

void CSoulBase::Initialize()
{
	
	/*m_tInfo = { 296.f, 280.f, 229.f, 142.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/SOUL_BASE2.bmp", L"SOUL");*/
	/*m_tInfo = { 296.f, 250.f, 256.f, 256.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HP_BASE.bmp", L"SOUL");*/
	m_tInfo = { 296.f, 280.f, 500.f, 200.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HPbar_1.bmp", L"SOUL");

	m_eRender = UI;

	m_ObjType = PUI;

	m_pFrameKey = L"SOUL";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();

	
}

int CSoulBase::Update()
{
	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == 0) {
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	}
	CObj::Update_Rect();
	return 0;
}

void CSoulBase::Late_Update()
{
}

void CSoulBase::Render(HDC hDC)
{
	//INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	//GdiTransparentBlt(hDC,
	//	60, // 복사 받을 위치 X,Y 좌표
	//	10,
	//	(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
	//	(int)m_tInfo.fCY+20,
	//	hMemDC,			// 비트맵 이미지를 담고 있는 DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
	//	m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	
	//	(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
	//	(int)m_tInfo.fCY,
	//	RGB(0, 0, 0)); // 제거하고자 하는 색상

	GdiTransparentBlt(hDC,
		60, // 복사 받을 위치 X,Y 좌표
		10,
		(int)m_tInfo.fCX-50,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iMotion * (int)m_tInfo.fCY,

		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 0)); // 제거하고자 하는 색상
	

	//HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 255));
	//HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	///*Rectangle(hDC,
	//	LONG(tRenderPos.fX - m_tInfo.fCX * 0.5f),
	//	LONG(tRenderPos.fY - m_tInfo.fCY * 0.5f),
	//	LONG(tRenderPos.fX + m_tInfo.fCX * 0.5f),
	//	LONG(tRenderPos.fY + m_tInfo.fCY * 0.5f));*/
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//SelectObject(hDC, hPrePen);
	//DeleteObject(hGreenPen);
	//SelectObject(hDC, OldBrush);
	//DeleteObject(myBrush);
}

void CSoulBase::Release()
{
	
}

void CSoulBase::Collision()
{
}
