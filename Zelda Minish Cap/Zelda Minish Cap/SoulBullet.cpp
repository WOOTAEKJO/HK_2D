#include "SoulBullet.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "ObjMgr.h"

CSoulBullet::CSoulBullet():m_PlayerState(STATE_END), m_bStart(true)
{
}

CSoulBullet::~CSoulBullet()
{
	Release();
}

void CSoulBullet::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_Owner = CObjMgr::Get_Instance()->Get_Player();

	m_ObjType = PBULLET;

	//m_tInfo = { 0.f,0.f,254.f,108.f };

	m_fSpeed = 10.f;

	m_Damage = 3;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/firet.bmp", L"swordrush");

	m_pFrameKey = L"swordrush";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = m_TurnDirection;
	m_tFrame.dwSpeed = 500;
	m_tFrame.dwTime = GetTickCount64();

	if (m_TurnDirection == 0) {
		m_tInfo.fCX = 502.f;
		m_tInfo.fCY = 178.f;
		//Set_Size(151.f, 129.f);
		m_tInfo.fX = m_Owner->Get_Info()->fX + m_Owner->Get_Info()->fCX * 0.5f;// * 0.5f + m_tInfo.fCX * 0.5f * 0.5f;
		m_tInfo.fY = m_Owner->Get_Info()->fY;
		m_fColC.x = m_tInfo.fCX * 0.5f;
		m_fColC.y = m_tInfo.fCY;
	}
	else if (m_TurnDirection == 1) {
		m_tInfo.fCX = 502.f;
		m_tInfo.fCY = 178.f;
		//Set_Size(151.f, 129.f);
		m_tInfo.fX = m_Owner->Get_Info()->fX - m_Owner->Get_Info()->fCX * 0.5f;// * 0.5f - m_tInfo.fCX * 0.5f * 0.5f;
		m_tInfo.fY = m_Owner->Get_Info()->fY;
		m_fColC.x = m_tInfo.fCX * 0.5f;
		m_fColC.y = m_tInfo.fCY;
	}

}

int CSoulBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Collision();


	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
		Set_Dead();

	}
	CObj::Update_Rect();
	return 0;
}

void CSoulBullet::Late_Update()
{
	if (m_TurnDirection == 0) {
		m_tInfo.fX += m_fSpeed;
	}
	else {
		m_tInfo.fX -= m_fSpeed;
	}
}

void CSoulBullet::Render(HDC hDC)
{
	
	CObj::Camera_Col_Render_LR(hDC,0,0,0);
}

void CSoulBullet::Release()
{
}

void CSoulBullet::Collision()
{
	if (m_CollisionCheck) {
		if (m_CollisionObjID == MONSTER) {
			Set_Dead();
		}
	}
}
