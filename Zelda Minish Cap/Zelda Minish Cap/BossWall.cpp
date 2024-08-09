#include "BossWall.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

float B_wallSound = 1.f;

CBossWall::CBossWall():m_Distroy(false), m_Start(true), m_turn(0)
{
}

CBossWall::~CBossWall()
{
	Release();
}

void CBossWall::Initialize()
{

	
	Set_Size(450.f,1500.f);

	m_fColC = { m_tInfo.fCX,m_tInfo.fCY };

	m_eRender = GAMEOBJECT;
	m_ObjType = PWALL;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/wall/wall5.bmp", L"Boss1_wall");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/wall/wall6.bmp", L"Boss1_wall2");

	
}

int CBossWall::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_Distroy) {
		CSoundMgr::Get_Instance()->PlaySound(L"B_wall_break.wav", STRUCTSOUND, B_wallSound*0.5f);
		Set_Dead();
	}

	if (m_turn == 1) {
		m_pFrameKey = L"Boss1_wall";
	}
	else {
		m_pFrameKey = L"Boss1_wall2";
	}
	Collision();
	if (m_Start) {
		CSoundMgr::Get_Instance()->PlaySound(L"B_wall.wav", STRUCTSOUND, B_wallSound * 0.5f);
		m_Start = false;
	}
	CObj::Update_Rect();
	return 0;
}

void CBossWall::Late_Update()
{
}

void CBossWall::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC,7,7,7);
}

void CBossWall::Release()
{
}

void CBossWall::Collision()
{
	if (m_CollisionCheck) {
		if (m_CollisionObjID == PMELEE) {
			CSoundMgr::Get_Instance()->PlaySoundW(L"P_sword_armour.wav", WALLSOUND, B_wallSound);
			m_CollisionCheck = false;
		}
	}
}
