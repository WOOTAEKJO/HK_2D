#include "BossAttack.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

float B_SkillSound1 = 1.f;

CBossAttack::CBossAttack():m_BossState(STATE_END)
{
}

CBossAttack::~CBossAttack()
{
	Release();
}

void CBossAttack::Initialize()
{
	m_eRender = EFFECT;

	m_ObjType = MMELEE;

	m_tInfo.fCX = 601.f;
	m_tInfo.fCY = 217.f;

	m_fColC = {m_tInfo.fCX*0.25f,m_tInfo.fCY * 0.75f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/effect/boss_att_effect.bmp", L"boss_att_eff");

	
	m_pFrameKey = L"boss_att_eff";
	FramSave(0, 4, m_TurnDirection, 100);
}

int CBossAttack::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	
	if (m_TurnDirection == TURNLEFT) {
		m_tInfo.fX = m_Owner->Get_Info()->fX -m_Owner->Get_Info()->fCX*0.25f;
		m_tInfo.fY = m_Owner->Get_Info()->fY+ m_Owner->Get_Info()->fCY*0.06f;
	}
	else if (m_TurnDirection == TURNRIGHT) {
		m_tInfo.fX = m_Owner->Get_Info()->fX + m_Owner->Get_Info()->fCX * 0.25f;
		m_tInfo.fY = m_Owner->Get_Info()->fY + m_Owner->Get_Info()->fCY * 0.06f;
	}
	CSoundMgr::Get_Instance()->PlaySound(L"B_attack.wav", BOSS_ATTACK1, B_SkillSound1);
	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
		Set_Dead();
	}
	CObj::Update_Rect();
	return 0;
}

void CBossAttack::Late_Update()
{
}

void CBossAttack::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);

	/*HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 0, 255));
	HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC,
		LONG(tRenderPos.fX - m_fColC.x * 0.5f),
		LONG(tRenderPos.fY - m_fColC.y * 0.5f),
		LONG(tRenderPos.fX + m_fColC.x * 0.5f),
		LONG(tRenderPos.fY + m_fColC.y * 0.5f));

	SelectObject(hDC, hPrePen);
	DeleteObject(hGreenPen);
	SelectObject(hDC, OldBrush);
	DeleteObject(myBrush);*/
}

void CBossAttack::Release()
{
}

void CBossAttack::Collision()
{
}
