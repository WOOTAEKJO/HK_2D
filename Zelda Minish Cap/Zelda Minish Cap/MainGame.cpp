#include "MainGame.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "LineMgr.h"

CMainGame::CMainGame():m_bStop(false)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround/Back.bmp", L"Back");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Back2.bmp", L"Back");
	//CSceneMgr::Get_Instance()->Set_StageID(STAGE1);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE1, SC_MENU, 400.f, 600.f);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE2, SC_STAGE1, 2460.f, 100.f);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE1, SC_STAGE2, 8400.f, 1880.f); // 바뀌는 스테이지/ 현재 스테이지/ 좌표
	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE5, SC_STAGE2, 3500.f, 1180.f);
	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE3, SC_STAGE2, 200.f, 1300.f);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE2, SC_STAGE3, 4275.f, 1340.f);
	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE4, SC_STAGE3, 300.f, 1940.f);
	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE6, SC_STAGE3, 300.f, 2430.f);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE3, SC_STAGE4, 1770.f, 1340.f);
	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE1, SC_STAGE4, 6377.5f, 1777.5f);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE3, SC_STAGE6, 3600.f, 1340.f);

	CSceneMgr::Get_Instance()->Add_StagePlayerPos(SC_STAGE2, SC_STAGE5, 165.f, 1580.f);



	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);
	CSoundMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	/*if (CKeyMgr::Get_Instance()->Get_Instance()->Key_Pressing('L')) {
		m_bStop = true;
	}
	else {
		m_bStop = false;
	}*/

	if (!m_bStop) {
		CSceneMgr::Get_Instance()->Update();
	}
}

void CMainGame::Late_Update()
{
	if (!m_bStop) {
		CSceneMgr::Get_Instance()->Late_Update();
	}
}

void CMainGame::Render()
{
	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	//Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(L"Back");

	if (!m_bStop) {
		CSceneMgr::Get_Instance()->Render(m_hDC);
	}

	//BitBlt(m_hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
	//	0, 0, BACKCX, BACKCY,
	//	hMemDC,			// 비트맵 이미지를 담고 있는 DC
	//	0,					// 비트맵을 출력할 시작 X,Y좌표
	//	0,
	//	SRCCOPY);

	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{

	CBmpMgr::Delete_Instance();
	CSceneMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CObjMgr::Delete_Instance();
	CSoundMgr::Delete_Instance();
	CLineMgr::Destroy_Instance();
	
	

	ReleaseDC(g_hWnd, m_hDC);
}
