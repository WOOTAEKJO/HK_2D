#include "SkillGetEffect.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CSkillGetEffect::CSkillGetEffect():m_SkillNum(0), m_DistroyTime(GetTickCount64())
{
}

CSkillGetEffect::~CSkillGetEffect()
{
	Release();
}

void CSkillGetEffect::Initialize()
{
	Set_Size(435.f,235.f);

	m_eRender = EFFECT;
	m_ObjType = PEFFECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/doublejump1.bmp", L"swing_t");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/wall1.bmp", L"wall_t");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/dash1.bmp", L"dash_t");


	if (m_SkillNum == 0) {
		m_pFrameKey = L"swing_t";
	}
	else if (m_SkillNum == 1) {
		m_pFrameKey = L"wall_t";
	}
	else if (m_SkillNum == 2) {
		m_pFrameKey = L"dash_t";
	}

	
}

int CSkillGetEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_Owner = CObjMgr::Get_Instance()->Get_Player();

	Set_Pos(m_Owner->Get_Info()->fX, m_Owner->Get_Info()->fY);

	if (m_DistroyTime + 2000 < GetTickCount64()) {
		Set_Dead();
	}

	CObj::Update_Rect();

	return 0;
}

void CSkillGetEffect::Late_Update()
{
}

void CSkillGetEffect::Render(HDC hDC)
{
	CObj::Camera_Col_Render_LR(hDC, 255, 0, 255);
}

void CSkillGetEffect::Release()
{
}

void CSkillGetEffect::Collision()
{
}
