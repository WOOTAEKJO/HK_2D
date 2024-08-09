#include "Stage6.h"
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
#include "NPC2.h"
#include "Hive.h"
#include "Bee.h"

float	g_fSound6 = 1.f;

CStage6::CStage6()
{
}

CStage6::~CStage6()
{
	Release();
}

void CStage6::Initialize()
{
	/*CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());

	for (int i = 0; i < 5; i++) {
		CObj* pObj = CObjFactory<CHP>::Create((float)(250 + (80 * i)), 144.f, 128.f, 256.f);
		CObjMgr::Get_Instance()->Add_HP_UI(pObj);
		CObjMgr::Get_Instance()->Add_Object(PUI, pObj);
	}
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoulBase>::Create());
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoul>::Create());*/

	/*CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(279.f, 1300.f, 558.f, 2600.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1732.f, 1140.f, 436.f, 2280.f));

	CObjMgr::Get_Instance()->Add_Object(STRUCT, CObjFactory<CHive>::Create(1000.f,100.f));

	CObjMgr::Get_Instance()->Add_Object(NPC, CObjFactory<CNPC2>::Create(800.f, 2300.f));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBee>::Create(750.f, 470.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBee>::Create(1200.f, 1050.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBee>::Create(800.f, 1700.f));*/

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(215.f, 1100.f, 430.f, 2200.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1680.f, 1300.f, 600.f, 2600.f));

	CObjMgr::Get_Instance()->Add_Object(STRUCT, CObjFactory<CHive>::Create(1000.f, 100.f));

	CObjMgr::Get_Instance()->Add_Object(NPC, CObjFactory<CNPC2>::Create(1000.f, 2350.f));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBee>::Create(600.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBee>::Create(1000.f, 1100.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBee>::Create(700.f, 1600.f));

	CObj* pcobj1 = CObjFactory<CPortal>::Create(75.f, 2400.f, 150.f, 200.f);
	dynamic_cast<CPortal*>(pcobj1)->Set_NextStageID(SC_STAGE3);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pcobj1);

	fPOINT Pos = CSceneMgr::Get_Instance()->Get_PLPos();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(Pos.x, Pos.y);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/colosseum/back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage6.bmp", L"Ground6");

	CCameraMgr::Get_Instance()->Set_MapSize(STAGE6X, STAGE6Y);
	//CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	
	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(300.f, 2430.f);
	CLineMgr::Get_Instance()->Load_Line(STAGE6);

	CSoundMgr::Get_Instance()->PlayBGM(L"S_cave.wav", g_fSound6);
}

void CStage6::Update()
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
	CSoundMgr::Get_Instance()->PlaySound(L"S_cave.wav", SOUND_BGM, g_fSound6 * 0.75);
}

void CStage6::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CStage6::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground6");

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

void CStage6::Release()
{
	CObjMgr::Get_Instance()->Scene_Delete_Object();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
