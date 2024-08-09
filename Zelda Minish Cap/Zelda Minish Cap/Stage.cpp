#include "Stage.h"
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
#include "Portal.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "NPC1.h"
#include "CSoul.h"

float	S_fSound1 = 1.f;

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	if (CObjMgr::Get_Instance()->Get_ObjList()[PLAYER].empty()) {
		CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());
		for (int i = 0; i < 5; i++) {
			/*m_vecHeal.push_back(CObjFactory<CHP>::Create((float)(250 + (80 * i)), 144.f, 128.f, 256.f));
			CObjMgr::Get_Instance()->Add_Object(PUI, m_vecHeal.back());*/
			CObj* pObj = CObjFactory<CHP>::Create((float)(250 + (80 * i)), 144.f, 128.f, 256.f);
			CObjMgr::Get_Instance()->Add_HP_UI(pObj);
			CObjMgr::Get_Instance()->Add_Object(PUI, pObj);
		}
		CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoulBase>::Create());
		CObjMgr::Get_Instance()->Add_Object(PUI, CObjFactory<CSoul>::Create());
	}

	CObjMgr::Get_Instance()->Add_Object(PWALL, CObjFactory<CWall>::Create(285.f,1350.f,570.f,1100.f));

	CObj* pObj = CObjFactory<CPortal>::Create(8630.f, 1855.f, 100.f, 130.f);
	dynamic_cast<CPortal*>(pObj)->Set_NextStageID(SC_STAGE2);
	CObjMgr::Get_Instance()->Add_Object(PORTAL, pObj);

	CObjMgr::Get_Instance()->Add_Object(NPC, CObjFactory<CNPC1>::Create(6145.f, 1700.f));
	
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround/Back.bmp", L"Back");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround/Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Back2.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/stage1.bmp", L"Ground1");

	//CCameraMgr::Get_Instance()->Set_LookPos(WINCX / 2, WINCY / 2);

	fPOINT Pos = CSceneMgr::Get_Instance()->Get_PLPos();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(Pos.x, Pos.y);

	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 600.f);
	CCameraMgr::Get_Instance()->Set_MapSize(STAGE1X, STAGE1Y);
	CCameraMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	//CCameraMgr::Get_Instance()->ShakingStart(5.f);

	//CTileMgr::Get_Instance()->Load_Tile();
	CLineMgr::Get_Instance()->Load_Line(STAGE1);

	//SoundMgr::Get_Instance()->StopAll();

	CSoundMgr::Get_Instance()->PlayBGM(L"S_town.wav", S_fSound1);
}

void CStage::Update()
{
	/*if (CKeyMgr::Get_Instance()->Get_Instance()->Key_Pressing('L')) {
		m_bStop = true;
		CCameraMgr::Get_Instance()->ShakingStart(10.f);
	}
	else {
		m_bStop = false;
		CCameraMgr::Get_Instance()->ShakingEnd();
	}*/

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
	CSoundMgr::Get_Instance()->PlaySound(L"S_town.wav", SOUND_BGM, S_fSound1 *0.75);
}

void CStage::Late_Update()
{
	if (!m_bStop) {
		CObjMgr::Get_Instance()->Late_Update();
		//CTileMgr::Get_Instance()->Late_Update();
	}
}

void CStage::Render(HDC hDC)
{
	INFO tLookPos = CCameraMgr::Get_Instance()->Get_LookPos();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC     hGround = CBmpMgr::Get_Instance()->Find_Img(L"Ground1");
	

		//HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
		
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

void CStage::Release()
{
	//CObjMgr::Get_Instance()->Delete_ID(PLAYER);
	CObjMgr::Get_Instance()->Scene_Delete_Object();
	//CBmpMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	
}
