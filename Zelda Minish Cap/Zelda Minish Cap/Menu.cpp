#include "Menu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMenu::CMenu()
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/colosseum/back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TitleScreen/Menu.bmp", L"Menu");
}

void CMenu::Update()
{

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1);
	}

	CObjMgr::Get_Instance()->Update();
}

void CMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update(); 
}

void CMenu::Render(HDC hDC)
{
	
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	
	BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, WINCX, WINCY,
		hGround,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);
	
	BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, WINCX, WINCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);
}

void CMenu::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	//CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CObjMgr::Get_Instance()->Scene_Delete_Object();
}
