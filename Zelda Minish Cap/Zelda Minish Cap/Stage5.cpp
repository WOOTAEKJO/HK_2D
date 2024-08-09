#include "Stage5.h"
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
#include "Husk.h"

float	g_fSound5 = 1.f;

CStage5::CStage5()
{
}

CStage5::~CStage5()
{
	Release();
}

void CStage5::Initialize()
{

	/*CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());

	for (int i = 0; i < 5; i++) {
		CObj* pObj = CObjFactory<CHP>::Create((float)(250 + (80 * i)), 144.f, 128.f, 256.f);
		CObjMgr::Get_Instance()->Add_HP_UI(pObj);
		CObjMgr::Get_Instance()->Add_Object(PUI, pObj);
	}
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoulBase>::Create());
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoul>::Create());*/


	/*CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(232.5f,1365.f,465.f,200.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(536.f,572.5f,292.f,531.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(922.f,859.f,358.f,152.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2696.f,1383.f,444.f,226.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3601.f,1421.5f,206.f,191.f));*/


	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(112.5f, 1423.f, 225.f, 200.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1161.f, 844.5f, 486.f, 117.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1027.f, 1418.f, 434.f, 300.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1559.5f, 986.5f, 111.f, 103.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1792.f, 1184.f, 210.f, 52.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2075.f, 1044.f, 110.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2870.5f, 858.5f, 495.f, 157.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3143.f, 504.5f, 220.f, 549.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3491.5f, 1344.5f, 463.f, 159.f));

	CObjMgr::Get_Instance()->Add_Object(NPC, CObjFactory<CNPC2>::Create(2816.f, 310.f));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CHusk>::Create(2900.f, 1300.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CHusk>::Create(400.f, 1300.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CHusk>::Create(1100.f, 650.f));

	CObj* pcobj1 = CObjFactory<CPortal>::Create(3700.f, 1100.f, 200.f, 400.f);
	dynamic_cast<CPortal*>(pcobj1)->Set_NextStageID(SC_STAGE2);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pcobj1);

	fPOINT Pos = CSceneMgr::Get_Instance()->Get_PLPos();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(Pos.x, Pos.y);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/colosseum/back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage5.bmp", L"Ground5");

	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(3500.f, 1180.f);

	CCameraMgr::Get_Instance()->Set_MapSize(STAGE5X, STAGE5Y);
	//CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	CLineMgr::Get_Instance()->Load_Line(STAGE5);

	CSoundMgr::Get_Instance()->PlayBGM(L"S_cave.wav", g_fSound5);
}

void CStage5::Update()
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
	CSoundMgr::Get_Instance()->PlaySound(L"S_cave.wav", SOUND_BGM, g_fSound5 * 0.75);
}

void CStage5::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CStage5::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground5");

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

void CStage5::Release()
{
	CObjMgr::Get_Instance()->Scene_Delete_Object();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
