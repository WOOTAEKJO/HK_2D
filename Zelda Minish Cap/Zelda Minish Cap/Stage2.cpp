#include "Stage2.h"
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
#include "Wall.h"
#include "Obj.h"
#include "SoundMgr.h"
#include "Bug.h"
#include "Portal.h"
#include "CSoul.h"
#include "NPC2.h"

float	S_fSound2 = 1.f;

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	/*CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());
	
	for (int i = 0; i < 5; i++) {
		CObj* pObj = CObjFactory<CHP>::Create((float)(250 + (80 * i)), 144.f, 128.f, 256.f);
		CObjMgr::Get_Instance()->Add_HP_UI(pObj);
		CObjMgr::Get_Instance()->Add_Object(PUI, pObj);
	}
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoulBase>::Create());
	CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoul>::Create());*/
	

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(105.f, 1775.f, 200.f, 240.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(475.f, 1565.f, 290.f, 90.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2400.f, 1595.f, 1060.f, 150.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(790.f, 1800.f, 100.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1245.f, 1670.f, 850.f, 200.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(1695.f, 1840.f, 130.f, 200.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2330.f, 1800.f, 100.f, 300.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3380.f, 1750.f, 100.f, 100.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3185.f, 1535.f, 130.f, 30.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3585.f, 1495.f, 210.f, 50.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(3955.f, 1480.f, 130.f, 40.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(4380.f, 1620.f, 300.f, 400.f));

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2200.f, 570.f, 280.f, 1140.f));
	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(2720.f, 570.f, 280.f, 1140.f));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBug>::Create(1235.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBug>::Create(480.f, 1450.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBug>::Create(2000.f, 1860.f));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CObjFactory<CBug>::Create(3780.f, 1730.f));

	CObj* pObj1 = CObjFactory<CPortal>::Create(4490.f, 1310.f, 150.f, 300.f);
	dynamic_cast<CPortal*>(pObj1)->Set_NextStageID(SC_STAGE3);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj1);

	CObj* pObj2 = CObjFactory<CPortal>::Create(2460.f, 30.f, 180.f, 60.f);
	dynamic_cast<CPortal*>(pObj2)->Set_NextStageID(SC_STAGE1);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj2);

	CObj* pObj3 = CObjFactory<CPortal>::Create(35.f, 1550.f, 70.f, 200.f);
	dynamic_cast<CPortal*>(pObj3)->Set_NextStageID(SC_STAGE5);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj3);

	CObjMgr::Get_Instance()->Add_Object(NPC, CObjFactory<CNPC2>::Create(2715.f, 1400.f));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/colosseum/back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage2.bmp", L"Ground2");

	CCameraMgr::Get_Instance()->Set_MapSize(STAGE2X, STAGE2Y);
	//CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	
	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(2460.f, 100.f);
	fPOINT m_PLPos = CSceneMgr::Get_Instance()->Get_PLPos();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(m_PLPos.x, m_PLPos.y);

	//CTileMgr::Get_Instance()->Load_Tile();
	CLineMgr::Get_Instance()->Load_Line(STAGE2);

	CSoundMgr::Get_Instance()->PlayBGM(L"S_cave.wav", S_fSound2);
}

void CStage2::Update()
{
	fPOINT m_PLPos = CSceneMgr::Get_Instance()->Get_PLPos();
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
	//CSoundMgr::Get_Instance()->PlaySound(L"S_cave.wav", SOUND_BGM, S_fSound2);
}

void CStage2::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
		//CTileMgr::Get_Instance()->Late_Update();
	}
}

void CStage2::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	//HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground2");
	//BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
	//	0, 0, WINCX, WINCY,
	//	hGround,			// 비트맵 이미지를 담고 있는 DC
	//	tLookPos.fX,					// 비트맵을 출력할 시작 X,Y좌표
	//	tLookPos.fY,
	//	SRCCOPY);

	if (!m_bStop) {
		BitBlt(hMemDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
			0, 0, WINCX, WINCY,
			hGround,			// 비트맵 이미지를 담고 있는 DC
			tLookPos.fX - (float)(WINCX / 2),					// 비트맵을 출력할 시작 X,Y좌표
			tLookPos.fY - (float)(WINCY / 2),
			SRCCOPY);

		//GdiTransparentBlt(hMemDC,
		//	0, // 복사 받을 위치 X,Y 좌표
		//	0,
		//	7998,	// 복사 받을 가로, 세로 길이
		//	2160,
		//	hGround,			// 비트맵 이미지를 담고 있는 DC
		//	0,					// 비트맵을 출력할 시작 X,Y좌표
		//	0,
		//	7998,		// 출력할 비트맵의 가로, 세로 사이즈
		//	2160,
		//	RGB(0, 0, 0)); // 제거하고자 하는 색상


		//CLineMgr::Get_Instance()->Render(hMemDC);
		//CTileMgr::Get_Instance()->Render(hMemDC);
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

void CStage2::Release()
{
	CObjMgr::Get_Instance()->Scene_Delete_Object();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
