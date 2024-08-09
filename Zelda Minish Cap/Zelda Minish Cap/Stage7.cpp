#include "Stage7.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "SceneMgr.h"
#include "Player.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
#include "SoulBase.h"
#include "HP.h"
#include "CSoul.h"
#include "Wall.h"
#include "Obj.h"
#include "SoundMgr.h"
#include "Portal.h"

float	g_fSound7 = 1.f;

CStage7::CStage7()
{
}

CStage7::~CStage7()
{
	Release();
}

void CStage7::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());

	for (int i = 0; i < 5; i++) {
		CObj* pObj = CObjFactory<CHP>::Create((float)(250 + (80 * i)), 144.f, 128.f, 256.f);
		CObjMgr::Get_Instance()->Add_HP_UI(pObj);
		CObjMgr::Get_Instance()->Add_Object(PUI, pObj);
	}
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoulBase>::Create());
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoul>::Create());

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/colosseum/back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage7.bmp", L"Ground7");

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(4400.f, 1900.f);

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(100.f, 100.f);

	CCameraMgr::Get_Instance()->Set_MapSize(STAGE5X, STAGE5Y);
	CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	CLineMgr::Get_Instance()->Load_Line(STAGE7);
}

void CStage7::Update()
{
	if (m_bStop) {
		if (m_StopTime + 100 < GetTickCount64()) {
			m_bStop = false;
			m_StopTime = GetTickCount64();
		}
	}

	if (!m_bStop) {
		CObjMgr::Get_Instance()->Update();
		CLineMgr::Get_Instance()->Update();
		//CTileMgr::Get_Instance()->Update();
	}
	CCameraMgr::Get_Instance()->Update();
	CSoundMgr::Get_Instance()->PlaySound(L"stage2.wav", SOUND_BGM, g_fSound7);
}

void CStage7::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CStage7::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground7");

	if (!m_bStop) {
		BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
			0, 0, WINCX, WINCY,
			hGround,			// 비트맵 이미지를 담고 있는 DC
			tLookPos.fX - (float)(WINCX / 2),					// 비트맵을 출력할 시작 X,Y좌표
			tLookPos.fY - (float)(WINCY / 2),
			SRCCOPY);


		CObjMgr::Get_Instance()->Render(hMemDC);
		CLineMgr::Get_Instance()->Render(hMemDC);
	}

	BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, WINCX, WINCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);
}

void CStage7::Release()
{
	CObjMgr::Get_Instance()->Scene_Delete_Object();
}
