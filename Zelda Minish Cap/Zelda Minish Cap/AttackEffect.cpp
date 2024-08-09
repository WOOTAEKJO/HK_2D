#include "AttackEffect.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CAttackEffect::CAttackEffect()
{
}

CAttackEffect::~CAttackEffect()
{
	Release();
}

void CAttackEffect::Initialize()
{
	Set_Size(250.f,160.f);

	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	m_Owner = CObjMgr::Get_Instance()->Get_Player();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/att_effect.bmp", L"P_att_effect");

	m_pFrameKey = L"P_att_effect";

	FramSave(0, 3, m_TurnDirection, 40);
}

int CAttackEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	//m_Owner = CObjMgr::Get_Instance()->Get_Player();

	//Set_TurnDir(m_Owner->Get_TurnDir());

	/*if (m_TurnDirection == TURNLEFT) {
		FramSave(0, 3, 1, 40);

	}
	else {
		FramSave(0, 3, 0, 40);
	}*/

	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
		Set_Dead();
	}
	CObj::Update_Rect();
	return 0;
}

void CAttackEffect::Late_Update()
{
}

void CAttackEffect::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CAttackEffect::Release()
{
}

void CAttackEffect::Collision()
{
}
