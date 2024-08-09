#include "Stage4.h"
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
#include "Bug.h"
#include "Portal.h"
#include "FalseKnight.h"
#include "Portal.h"

float	g_fSound4 = 1.f;

CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage4.bmp", L"Ground4");

	/*CObj* pObj = CObjFactory<CPortal>::Create(1950.f, 1340.f, 100.f, 120.f);
	dynamic_cast<CPortal*>(pObj)->Set_NextStageID(SC_STAGE4);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj);*/

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1800.f, 1475.f, 3600.f, 150.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3775.f, 775.f, 450.f, 1550.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(7300.f, 1475.f, 1400.f, 150.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(6530.f, 775.f, 440.f, 1550.f));
	// 보스 룸

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CFalseKnight>::Create(5160.f, 100.f));

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(100.f, 1700.f);
	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(4400.f, 1900.f); // 보스 테스트 위해서
	
	CObj* pcobj1 = CObjFactory<CPortal>::Create(50.f, 1900.f, 100.f, 200.f);
	dynamic_cast<CPortal*>(pcobj1)->Set_NextStageID(SC_STAGE3);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pcobj1);

	CObj* pcobj2 = CObjFactory<CPortal>::Create(7500.f, 1750.f, 1000.f, 500.f);
	dynamic_cast<CPortal*>(pcobj2)->Set_NextStageID(SC_STAGE1);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pcobj2);

	/*fPOINT Pos = CSceneMgr::Get_Instance()->Get_PLPos();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(Pos.x, Pos.y);*/

	CCameraMgr::Get_Instance()->Set_MapSize(STAGE4X, STAGE4Y);
	CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	CLineMgr::Get_Instance()->Load_Line(STAGE4);

	CSoundMgr::Get_Instance()->PlayBGM(L"S_boss.wav", g_fSound4);
}

void CStage4::Update()
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
	CSoundMgr::Get_Instance()->PlaySound(L"S_boss.wav", SOUND_BGM, g_fSound4 * 0.75);
}

void CStage4::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CStage4::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground4");

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

void CStage4::Release()
{
	CObjMgr::Get_Instance()->Scene_Delete_Object();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
