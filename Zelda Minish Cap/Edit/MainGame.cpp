#include "MainGame.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CMainGame::CMainGame() : m_dwTime(GetTickCount()), m_iFPS(0)
{
    ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
    Release();
}

void CMainGame::Initialize()
{
    m_hDC = GetDC(g_hWnd);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Back2.bmp", L"Back");
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/main.bmp", L"Ground");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage3.bmp", L"Ground");


    CLineMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
    CLineMgr::Get_Instance()->Update();
}


void CMainGame::Late_Update()
{
    CLineMgr::Get_Instance()->Late_Update();
    CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render()
{
   /* ++m_iFPS;
    if (m_dwTime + 1000 < GetTickCount())
    {
        swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
        SetWindowText(g_hWnd, m_szFPS);

        m_iFPS = 0;
        m_dwTime = GetTickCount();
    }

    Rectangle(m_hDC, 0, 0, 4500, WINCY);


    int      iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();

    TCHAR   szBuff[100] = L"";
    for (int i = 0; i < 4500;)
    {
        wsprintf(szBuff, L"X값 : %d", i);
        TextOut(m_hDC, i + iScrollX, 100, szBuff, lstrlen(szBuff));
        SetBkMode(m_hDC, TRANSPARENT);
        i += 100;
    }

    for (int j = 0; j < 600;)
    {
        wsprintf(szBuff, L"Y값 : %d", j);
        TextOut(m_hDC, 300, j, szBuff, lstrlen(szBuff));
        SetBkMode(m_hDC, TRANSPARENT);
        j += 50;
    }*/

    //INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
    ////HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    //HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    //HDC     hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
    //BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
    //    0, 0, WINCX, WINCY,
    //    hGround,			// 비트맵 이미지를 담고 있는 DC
    //    tLookPos.fX,					// 비트맵을 출력할 시작 X,Y좌표
    //    tLookPos.fY,
    //    SRCCOPY);

    //BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
    //    0, 0, BACKCX, BACKCY,
    //    hMemDC,			// 비트맵 이미지를 담고 있는 DC
    //    0,					// 비트맵을 출력할 시작 X,Y좌표
    //    0,
    //    SRCCOPY);

    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

    //HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    HDC     hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
    //BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
    //    0, 0, WINCX, WINCY,
    //    hGround,			// 비트맵 이미지를 담고 있는 DC
    //    0,					// 비트맵을 출력할 시작 X,Y좌표
    //    0,
    //    SRCCOPY);

    //BitBlt(m_hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
    //    iScrollX, iScrollY, BACKCX, BACKCY,
    //    hMemDC,			// 비트맵 이미지를 담고 있는 DC
    //    0,					// 비트맵을 출력할 시작 X,Y좌표
    //    0,
    //    SRCCOPY);

    

    BitBlt(m_hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
        iScrollX, iScrollY, BACKCX, BACKCY,
        hGround,			// 비트맵 이미지를 담고 있는 DC
        0,					// 비트맵을 출력할 시작 X,Y좌표
        0,
        SRCCOPY);

    CLineMgr::Get_Instance()->Render(m_hDC);

    WCHAR text[100];

    POINT	ptMouse{};

    GetCursorPos(&ptMouse);	// 마우스 위치 값을 얻어오는 함수

    ScreenToClient(g_hWnd, &ptMouse); // 스크린 상의 좌표를 우리가 생성한 창 좌표로 변환

    
    _stprintf_s(text, L"[Mouse] x : %f \t y : %f", (float)ptMouse.x, (float)ptMouse.y);
    TextOutW(m_hDC, 0, 20, text, lstrlen(text));

}

void CMainGame::Release()
{
    CKeyMgr::Destroy_Instance();
    CLineMgr::Destroy_Instance();

    ReleaseDC(g_hWnd, m_hDC);
}