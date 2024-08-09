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
        wsprintf(szBuff, L"X�� : %d", i);
        TextOut(m_hDC, i + iScrollX, 100, szBuff, lstrlen(szBuff));
        SetBkMode(m_hDC, TRANSPARENT);
        i += 100;
    }

    for (int j = 0; j < 600;)
    {
        wsprintf(szBuff, L"Y�� : %d", j);
        TextOut(m_hDC, 300, j, szBuff, lstrlen(szBuff));
        SetBkMode(m_hDC, TRANSPARENT);
        j += 50;
    }*/

    //INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
    ////HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    //HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    //HDC     hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
    //BitBlt(hMemDC,	// ���� ���� DC(���������� �׸��� �׸� DC����)
    //    0, 0, WINCX, WINCY,
    //    hGround,			// ��Ʈ�� �̹����� ��� �ִ� DC
    //    tLookPos.fX,					// ��Ʈ���� ����� ���� X,Y��ǥ
    //    tLookPos.fY,
    //    SRCCOPY);

    //BitBlt(hDC,	// ���� ���� DC(���������� �׸��� �׸� DC����)
    //    0, 0, BACKCX, BACKCY,
    //    hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
    //    0,					// ��Ʈ���� ����� ���� X,Y��ǥ
    //    0,
    //    SRCCOPY);

    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

    //HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    HDC     hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
    //BitBlt(hMemDC,	// ���� ���� DC(���������� �׸��� �׸� DC����)
    //    0, 0, WINCX, WINCY,
    //    hGround,			// ��Ʈ�� �̹����� ��� �ִ� DC
    //    0,					// ��Ʈ���� ����� ���� X,Y��ǥ
    //    0,
    //    SRCCOPY);

    //BitBlt(m_hDC,	// ���� ���� DC(���������� �׸��� �׸� DC����)
    //    iScrollX, iScrollY, BACKCX, BACKCY,
    //    hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
    //    0,					// ��Ʈ���� ����� ���� X,Y��ǥ
    //    0,
    //    SRCCOPY);

    

    BitBlt(m_hDC,	// ���� ���� DC(���������� �׸��� �׸� DC����)
        iScrollX, iScrollY, BACKCX, BACKCY,
        hGround,			// ��Ʈ�� �̹����� ��� �ִ� DC
        0,					// ��Ʈ���� ����� ���� X,Y��ǥ
        0,
        SRCCOPY);

    CLineMgr::Get_Instance()->Render(m_hDC);

    WCHAR text[100];

    POINT	ptMouse{};

    GetCursorPos(&ptMouse);	// ���콺 ��ġ ���� ������ �Լ�

    ScreenToClient(g_hWnd, &ptMouse); // ��ũ�� ���� ��ǥ�� �츮�� ������ â ��ǥ�� ��ȯ

    
    _stprintf_s(text, L"[Mouse] x : %f \t y : %f", (float)ptMouse.x, (float)ptMouse.y);
    TextOutW(m_hDC, 0, 20, text, lstrlen(text));

}

void CMainGame::Release()
{
    CKeyMgr::Destroy_Instance();
    CLineMgr::Destroy_Instance();

    ReleaseDC(g_hWnd, m_hDC);
}