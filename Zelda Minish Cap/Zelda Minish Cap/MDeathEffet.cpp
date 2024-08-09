#include "MDeathEffet.h"
#include "BmpMgr.h"

CMDeathEffet::CMDeathEffet():m_MonsterType(0)
{
}

CMDeathEffet::~CMDeathEffet()
{
	Release();
}

void CMDeathEffet::Initialize()
{
	Set_Size(308.f, 270.f);

	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/m_stun_eff2.bmp", L"m_stun_eff2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/m_stun_eff.bmp", L"m_stun_eff");


	if (m_MonsterType == 1) {
		m_pFrameKey = L"m_stun_eff";
		FramSave(0, 5, m_TurnDirection, 100);
	}
	else {
		m_pFrameKey = L"m_stun_eff2";
		FramSave(0, 5, m_TurnDirection, 300);
	}

	
}

int CMDeathEffet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
		Set_Dead();
	}
	CObj::Update_Rect();
	return 0;
}

void CMDeathEffet::Late_Update()
{
}

void CMDeathEffet::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CMDeathEffet::Release()
{
}

void CMDeathEffet::Collision()
{
}
