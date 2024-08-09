#include "Bee.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "CameraMgr.h"
#include "SoundMgr.h"
#include "MDeathEffet.h"
#include "ObjFactory.h"
#include "ObjMgr.h"

float M_fSound2 = 1.f;

CBee::CBee():m_eCurState(STATE_END),m_ePreState(STATE_END), m_HitCheck(true), m_HitTime(GetTickCount64()), m_ePreTurnDir(0),
m_onecheck(true)
{
	
}

CBee::~CBee()
{
	Release();
}

void CBee::Initialize()
{
	Set_Size(152.f, 133.f);

	m_SaveInfo = m_tInfo;

	m_fColC = { m_tInfo.fCX,m_tInfo.fCY };
	m_fATTRC = { m_SaveInfo.fCX * 12.f,m_SaveInfo.fCY * 5.f };

	m_eRender = GAMEOBJECT;
	m_ObjType = MONSTER;

	m_HP = 1;

	m_fSpeed = 3.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/bee/idle1.bmp", L"bee_idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/bee/attack1.bmp", L"bee_attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/bee/death.bmp", L"bee_death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/bee/turn.bmp", L"bee_turn");

	m_pFrameKey = L"bee_idle";
	FramSave(0, 5, m_TurnDirection, 200);
}

int CBee::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_HP <= 0) {
		
		m_pFrameKey = L"bee_death";
		m_eCurState = DEATH;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	Collision();
	ATTR_Check();

	Act();
	Motion_Change();

	CObj::Move_Frame();
	CObj::Update_Rect();

	return 0;
}

void CBee::Late_Update()
{
	

	if (!m_HitCheck) {
		if (m_HitTime + 500 < GetTickCount64()) {
			m_HitCheck = true;
			m_CollisionObjID = OBJID_END;
			m_CollisionCheck = false;
			m_HitTime = GetTickCount64();
		}
		
	}

	
	if (m_StunEffect) {
		if (m_StunEffect->Get_Dead()) {
			m_StunEffect = nullptr;
		}
	}
	
}

void CBee::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	CObj::Camera_Col_Render_LR(hDC, 255, 0, 255);

	/*HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(255, 255, 0));
	HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC,
		LONG(tRenderPos.fX - m_fATTRC.x * 0.5f),
		LONG(tRenderPos.fY - m_fATTRC.y * 0.5f),
		LONG(tRenderPos.fX + m_fATTRC.x * 0.5f),
		LONG(tRenderPos.fY + m_fATTRC.y * 0.5f));

	SelectObject(hDC, hPrePen);
	DeleteObject(hGreenPen);
	SelectObject(hDC, OldBrush);
	DeleteObject(myBrush);

	WCHAR _text1[100];
	_stprintf_s(_text1, L"hp: %dt\t atr: %d\t atro: %d",m_HP,m_ATTR_Check,m_ATTR_ObjID );
	TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f), LONG(tRenderPos.fY - m_fColC.y * 0.5f) - 30.f, _text1, lstrlen(_text1));*/


}

void CBee::Release()
{
}

void CBee::Collision()
{
	if (m_CollisionCheck) {
		if ((m_CollisionObjID == PMELEE || m_CollisionObjID == PBULLET)&&m_HitCheck) {
			//m_eCurState = HIT;
			
			if (m_TurnDirection == TURNLEFT) {
				m_tInfo.fX += 30.f;
			}
			else if (m_TurnDirection == TURNRIGHT) {
				m_tInfo.fX -= 30.f;
			}
			m_HP -= m_HitDamage;
			if (m_HP <= 0) {
				CSoundMgr::Get_Instance()->PlaySound(L"M_death.wav", MONSTER_EFFECT, M_fSound2);
			}
			else {
				CSoundMgr::Get_Instance()->PlaySound(L"M_hit2.wav", MONSTER_EFFECT, M_fSound2);
			}
			m_HitCheck = false;
		}
	}
}

void CBee::Act()
{
	switch (m_eCurState)
	{
	case CBee::IDLE:
	{
		float fW = 0.f;
		float fH = 0.f;
		float fD = 0.f;
		float fR = 0.f;

		fW = m_SaveInfo.fX - m_tInfo.fX;
		fH = m_SaveInfo.fY - m_tInfo.fY;

		fD = sqrtf(fW * fW + fH * fH);

		fR = acosf(fW / fD);

		if (m_SaveInfo.fY > m_tInfo.fY)
			fR = (2 * PI) - fR;

		if (fD > 3.f) {

		m_tInfo.fX += cosf(fR) * m_fSpeed;
		m_tInfo.fY -= sinf(fR) * m_fSpeed;

		}

	}

		break;
	case CBee::HIT:
		
		
		/*if (m_HitCheck) {
			m_pFrameKey = L"bee_idle";
			m_eCurState = IDLE;
		}*/
		break;
	case CBee::ATTACK: {

		float fW = m_pTarget->Get_Info()->fX - m_tInfo.fX;
		float fH = m_pTarget->Get_Info()->fY - m_tInfo.fY;

		float fD = sqrtf(fW * fW + fH * fH);

		float fR = acosf(fW / fD);

		if (m_pTarget->Get_Info()->fY > m_tInfo.fY)
			fR = (2 * PI) - fR;

		m_tInfo.fX += cosf(fR) * m_fSpeed;
		m_tInfo.fY -= sinf(fR) * m_fSpeed;

		if (m_pTarget->Get_Info()->fX <= m_tInfo.fX) {
			//Set_TurnMotion(TURNLEFT);
			m_TurnDirection = TURNLEFT;
		}
		else {
			//Set_TurnMotion(TURNRIGHT);
			m_TurnDirection = TURNRIGHT;
		}
		if (m_ePreTurnDir != m_TurnDirection) {
			m_pFrameKey = L"bee_turn";
			m_eCurState = TURN;

			m_ePreTurnDir = m_TurnDirection;
		}

		if (!m_ATTR_Check) {
			m_pFrameKey = L"bee_idle";
			m_eCurState = IDLE;
		}
	}
		break;
	case CBee::DEATH:
		if (!m_StunEffect) {
			m_StunEffect = CObjFactory<CMDeathEffet>::Create(m_tInfo.fX, m_tInfo.fY);
			m_StunEffect->Set_TurnDir(m_TurnDirection);
			m_StunEffect->Initialize();
			CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect);
			//CCameraMgr::Get_Instance()->ShakingStart(1.f);
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			//CCameraMgr::Get_Instance()->ShakingEnd();
			Set_Dead();
		}
		break;
	case CBee::TURN:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"bee_idle";
			m_eCurState = IDLE;
		}
		break;
	default:
		break;
	}
}

void CBee::Motion_Change()
{
	if (m_ePreState != m_eCurState) {
		switch (m_eCurState)
		{
		case CBee::IDLE:
			FramSave(0, 5, m_TurnDirection, 200);
			break;
		case CBee::ATTACK:
			FramSave(0, 11, m_TurnDirection, 200);
			break;
		case CBee::DEATH:
			FramSave(0, 5, m_TurnDirection, 200);
			break;
		case CBee::TURN:
			FramSave(0, 1, m_TurnDirection, 200);

			break;
		default:
			break;
		}
		//CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
		m_ePreState = m_eCurState;
	}
}

void CBee::ATTR_Check()
{
	if (m_ATTR_Check) {
		if (m_ATTR_ObjID == PLAYER) {
			if (m_eCurState != DEATH) {
				m_pFrameKey = L"bee_attack";
				m_eCurState = ATTACK;
			}
		}
		
	}
}
