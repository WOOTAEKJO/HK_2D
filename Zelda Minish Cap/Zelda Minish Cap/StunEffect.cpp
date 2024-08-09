#include "StunEffect.h"
#include "BmpMgr.h"

CStunEffect::CStunEffect()
{
}

CStunEffect::~CStunEffect()
{
    Release();
}

void CStunEffect::Initialize()
{
	
	Set_Size(699.f, 140.f);
	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/stun_eff.bmp", L"P_stun_eff");

	m_pFrameKey = L"P_stun_eff";

	FramSave(0, 2, m_TurnDirection, 150);
}

int CStunEffect::Update()
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

void CStunEffect::Late_Update()
{
}

void CStunEffect::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CStunEffect::Release()
{
}

void CStunEffect::Collision()
{
}
