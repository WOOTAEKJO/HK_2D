#include "DashEffec.h"
#include "BmpMgr.h"

CDashEffec::CDashEffec()
{
}

CDashEffec::~CDashEffec()
{
	Release();
}

void CDashEffec::Initialize()
{
	Set_Size(379.f,328.f);

	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/dash_eff.bmp", L"P_dash_effect");

	m_pFrameKey = L"P_dash_effect";

	FramSave(0, 4, m_TurnDirection, 50);
}

int CDashEffec::Update()
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

void CDashEffec::Late_Update()
{
}

void CDashEffec::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CDashEffec::Release()
{
}

void CDashEffec::Collision()
{
}
