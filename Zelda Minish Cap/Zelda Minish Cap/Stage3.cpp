#include "Stage3.h"
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
#include "NPC2.h"

float	g_fSound3 = 1.f;

CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	//CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/colosseum/back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage3.bmp", L"Ground3");

	/*CObj* pObj1 = CObjFactory<CPortal>::Create(1950.f, 1340.f, 100.f, 120.f);
	dynamic_cast<CPortal*>(pObj1)->Set_NextStageID(SC_STAGE4);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj1);*/
	// 보스 룸

	CObj* pObj2 = CObjFactory<CPortal>::Create(35.f, 1300.f, 140.f, 200.f);
	dynamic_cast<CPortal*>(pObj2)->Set_NextStageID(SC_STAGE2);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj2);

	CObj* pObj3 = CObjFactory<CPortal>::Create(3750.f, 1300.f, 100.f, 200.f);
	dynamic_cast<CPortal*>(pObj3)->Set_NextStageID(SC_STAGE6);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj3);

	CObjMgr::Get_Instance()->Add_Object(NPC, CObjFactory<CNPC2>::Create(2185.f, 1300.f));

	fPOINT Pos = CSceneMgr::Get_Instance()->Get_PLPos();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(Pos.x, Pos.y);

	
	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(200.f, 1300.f);
	CCameraMgr::Get_Instance()->Set_MapSize(STAGE3X, STAGE3Y);
	//CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	CLineMgr::Get_Instance()->Load_Line(STAGE3);

	CSoundMgr::Get_Instance()->PlayBGM(L"S_cave.wav", g_fSound3);
}

void CStage3::Update()
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
	CSoundMgr::Get_Instance()->PlaySound(L"S_cave.wav", SOUND_BGM, g_fSound3 * 0.75);
}

void CStage3::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CStage3::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground3");
	
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

void CStage3::Release()
{
	CObjMgr::Get_Instance()->Scene_Delete_Object();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
