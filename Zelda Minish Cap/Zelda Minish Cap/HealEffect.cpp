#include "HealEffect.h"
#include "BmpMgr.h"
CHealEffect::CHealEffect()
{
}

CHealEffect::~CHealEffect()
{
    Release();
}

void CHealEffect::Initialize()
{
	//Set_Size(304.f, 300.f);
	Set_Size(152.f, 150.f);
	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/heal_eff.bmp", L"P_heal_eff");

	m_pFrameKey = L"P_heal_eff";

	FramSave(0, 8, m_TurnDirection, 50);
}

int CHealEffect::Update()
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

void CHealEffect::Late_Update()
{
}

void CHealEffect::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CHealEffect::Release()
{
}

void CHealEffect::Collision()
{
}
