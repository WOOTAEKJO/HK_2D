#include "MyEdit.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CMyEdit::CMyEdit():m_OptionNum(NON), m_DrawID(NON)
{
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	CTileMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage2.bmp", L"editg");

}

void CMyEdit::Update()
{
	Key_Input();

	CTileMgr::Get_Instance()->Update();
}

void CMyEdit::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMyEdit::Render(HDC hDC)
{

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC     hGround = CBmpMgr::Get_Instance()->Find_Img(L"editg");

	

	BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		iScrollX, iScrollY, BACKCX, BACKCY,
		hGround,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);
	/*GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		BACKCX,
		BACKCY,
		hGround,
		0,
		0,
		BACKCX,
		BACKCY,
		RGB(0, 0, 0));*/

	CTileMgr::Get_Instance()->Render(hMemDC);

	BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, BACKCX, BACKCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);

	WCHAR text[100];

	POINT	ptMouse{};

	GetCursorPos(&ptMouse);	// 마우스 위치 값을 얻어오는 함수

	ScreenToClient(g_hWnd, &ptMouse); // 스크린 상의 좌표를 우리가 생성한 창 좌표로 변환

	//CCameraMgr::Get_Instance()->Get_Point_RenderPos(ptMouse);

	_stprintf_s(text, L"x: %d\t y: %d", ptMouse.x - iScrollX, ptMouse.y- iScrollY);
	TextOutW(hDC, 0, 20, text, lstrlen(text));
	
}

void CMyEdit::Release()
{
	
}

void CMyEdit::Save_Tile()
{
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(20.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-20.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(20.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-20.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, m_DrawID, m_OptionNum);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('1')) {
		m_OptionNum = NON;
		m_DrawID = NON;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('2')) {
		m_OptionNum = WALL;
		m_DrawID = WALL;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('3')) {
		m_OptionNum = GROUND;
		m_DrawID = GROUND;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CTileMgr::Get_Instance()->Save_Tile();

	if (CKeyMgr::Get_Instance()->Key_Down('B'))
		CTileMgr::Get_Instance()->Load_Tile();
	
}
