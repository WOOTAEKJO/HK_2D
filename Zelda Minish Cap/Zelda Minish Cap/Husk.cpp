#include "Husk.h"
#include "ObjMgr.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
#include "MDeathEffet.h"
#include "ObjFactory.h"
#include "ObjMgr.h"

float M_fSound3 = 1.f;

CHusk::CHusk() :m_eCurState(STATE_END), m_ePreState(STATE_END), m_HitCheck(true), m_HitTime(GetTickCount64()), m_iChange(0),
m_FrameStop(false), m_SaveDir(0), m_OneCheck(true)
{
}

CHusk::~CHusk()
{
	Release();
}

void CHusk::Initialize()
{
	Set_Size(256.f, 256.f);

	m_fColC = { m_tInfo.fCX * 0.5f,m_tInfo.fCY * 0.5f };
	m_fATTRC = { m_tInfo.fCX * 4.f,m_tInfo.fCY*0.5f };

	m_eRender = GAMEOBJECT;
	m_ObjType = MONSTER;

	m_HP = 5;

	m_fSpeed = 1.f;
	m_fAccel = 2.f;

	m_fJump_Power = 10.f;
	m_fJump_Angle = PI / 3;
	m_iAdditionJump_MaxCount = 1;
	m_iAdditionJump_Count = m_iAdditionJump_MaxCount;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/husk/idle.bmp", L"husk_idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/husk/attack.bmp", L"husk_attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/husk/move.bmp", L"husk_move");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/husk/dead.bmp", L"husk_dead");

	m_pFrameKey = L"husk_move";
	m_eCurState = MOVE;

	m_TurnDirection = TURNLEFT;

	FramSave(0, 5, m_TurnDirection, 200);
}

int CHusk::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if (m_TurnDirection == 0) {
		m_iChange = 1;
	}
	else {
		m_iChange = 0;
	}*/
	if (m_OneCheck) {
		if (m_HP <= 0) {
			CCameraMgr::Get_Instance()->ShakingStart(2.f);
			m_pFrameKey = L"husk_dead";
			m_eCurState = DEAD;
			m_OneCheck = false;
		}
		
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	JumpEX();

	Collision();
	ATTR_Check();
	
	Act();
	Motion_Change();

	if (!m_FrameStop) {
		
	}
	CObj::Move_Frame();
	CObj::Update_Rect();
	return 0;
}

void CHusk::Late_Update()
{
	if (!m_HitCheck) {
		if (m_HitTime + 200 < GetTickCount64()) {
			m_HitCheck = true;
			m_CollisionObjID = OBJID_END;
			m_HitTime = GetTickCount64();
			m_CollisionCheck = false;
		}

	}

	if (m_StunEffect) {
		if (m_StunEffect->Get_Dead()) {
			m_StunEffect = nullptr;
		}
	}
}

void CHusk::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	CObj::Camera_Col_Render_UD(hDC, 7, 7, 7);

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
	_stprintf_s(_text1, L"hp: %dt\t atr: %d\t atro: %d", m_HP, m_ATTR_Check, m_ATTR_ObjID);
	TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f), LONG(tRenderPos.fY - m_fColC.y * 0.5f) - 30.f,
		_text1, lstrlen(_text1));*/
}

void CHusk::Release()
{
}

void CHusk::Collision()
{
	if (m_CollisionCheck) {
		if (m_eCurState != DEAD) {
			if ((m_CollisionObjID == PMELEE || m_CollisionObjID == PBULLET) && m_HitCheck) {
				m_HP -= m_HitDamage;
				m_HitCheck = false;
				m_eCurState = HIT;
				m_pFrameKey = L"husk_idle";
				m_fSpeed_Vertical = 10.f;
				m_bJump = true;
				if (m_TurnDirection == TURNRIGHT) {
					//m_HitSpeed -= 3.f;
					m_tInfo.fX -= 10.f;
				}
				else if (m_TurnDirection == TURNLEFT) {
					m_tInfo.fX += 10.f;
				}
				if (m_HP > 1) {
					CSoundMgr::Get_Instance()->PlaySound(L"M_hit2.wav", MONSTER_EFFECT, M_fSound3);
					
				}
				else {
					CSoundMgr::Get_Instance()->PlaySound(L"M_death.wav", MONSTER_EFFECT, M_fSound3);
					
				}
			}
		}
	}
}

void CHusk::Act()
{
	switch (m_eCurState)
	{
	case CHusk::IDLE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"husk_move";
			m_eCurState = MOVE;
		}
		break;
	case CHusk::MOVE: 
	{
		CLine m_pLine;
		float fY = INFINITY;
		if (CLineMgr::Get_Instance()->CollisionLine_GroundEX(m_tInfo, m_fColC, &m_pLine, &fY)) {
			if (m_tInfo.fX <= m_pLine.Get_Info()->tLpoint.fX + m_tInfo.fCX*0.5f) {
				Set_TurnMotion(TURNLEFT);
				m_fSpeed = -1 * m_fSpeed;
				m_SaveDir = TURNLEFT;
			}
			else if (m_tInfo.fX >= m_pLine.Get_Info()->tRpoint.fX - m_tInfo.fCX * 0.5f) {
				Set_TurnMotion(TURNRIGHT);
				m_fSpeed = -1 * m_fSpeed;
				m_SaveDir = TURNRIGHT;
			}
			m_tInfo.fX += m_fSpeed;
		}
		
	}
	

		break;
	case CHusk::HIT:
		if (m_bJump) {
			/*if (m_eDir == RIGHT) {
				m_tInfo.fX += 3.f;
			}
			else if (m_eDir == LEFT) {
				m_tInfo.fX -= 3.f;
			}*/
			m_tInfo.fX += m_HitSpeed;
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.0044f * G);
			
		}
		else {
			/*if (m_SaveDir == TURNLEFT) {
				Set_TurnMotion(TURNLEFT);
			}
			else if (m_SaveDir == TURNRIGHT) {
				Set_TurnMotion(TURNRIGHT);
			}*/
			m_CollisionCheck = false;
			m_pFrameKey = L"husk_attack";
			m_eCurState = ATTACK;
		}
		
		break;
	case CHusk::ATTACK:

		if (!m_ATTR_Check) {

			if (m_SaveDir == TURNLEFT) {
				Set_TurnMotion(TURNLEFT);
			}
			else if(m_SaveDir == TURNRIGHT) {
				Set_TurnMotion(TURNRIGHT);
			}

			m_pFrameKey = L"husk_idle";
			m_eCurState = IDLE;
		}
		else {
			if (m_pTarget->Get_Info()->fX <= m_tInfo.fX) {
				Set_TurnMotion(TURNRIGHT);
				//m_fAccel = -1 * m_fAccel;
				m_tInfo.fX -= m_fAccel;
			}
			else if (m_pTarget->Get_Info()->fX > m_tInfo.fX) {
				Set_TurnMotion(TURNLEFT);
				//m_fAccel = -1 * m_fAccel;
				m_tInfo.fX += m_fAccel;
			}
			
		}
		
		break;
	case CHusk::DEAD:
		if (!m_StunEffect) {
			m_StunEffect = CObjFactory<CMDeathEffet>::Create(m_tInfo.fX, m_tInfo.fY);
			m_StunEffect->Set_TurnDir(m_TurnDirection);
			m_StunEffect->Initialize();
			CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect);
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			CCameraMgr::Get_Instance()->ShakingEnd();
			Set_Dead();
		}
		break;
	default:
		break;
	}
}

void CHusk::Motion_Change()
{
	if (m_ePreState != m_eCurState) {

		switch (m_eCurState)
		{
		case CHusk::IDLE:
			FramSave(0, 5, m_TurnDirection, 200);
			break;
		case CHusk::MOVE:
			FramSave(0, 5, m_TurnDirection, 200);
			break;
		case CHusk::HIT:
			break;
		case CHusk::ATTACK:
			FramSave(0, 10, m_TurnDirection, 200);
			break;
		case CHusk::DEAD:
			FramSave(0, 8, m_TurnDirection, 50);
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CHusk::ATTR_Check()
{
	if (m_ATTR_Check) {
		if (m_ATTR_ObjID == PLAYER) {
			if (m_eCurState != DEAD) {
				m_pFrameKey = L"husk_attack";
				m_eCurState = ATTACK;
			}
		}
	}
}
