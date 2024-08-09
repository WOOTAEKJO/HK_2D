#include "StunEffect2.h"
#include "BmpMgr.h"

CStunEffect2::CStunEffect2()
{
}

CStunEffect2::~CStunEffect2()
{
	Release();
}

void CStunEffect2::Initialize()
{
	Set_Size(308.f, 270.f);
	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/stun_eff2.bmp", L"P_stun_eff2");

	m_pFrameKey = L"P_stun_eff2";

	FramSave(0, 5, m_TurnDirection, 200);
}

int CStunEffect2::Update()
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

void CStunEffect2::Late_Update()
{
}

void CStunEffect2::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CStunEffect2::Release()
{
}

void CStunEffect2::Collision()
{
}
