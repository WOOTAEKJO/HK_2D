#include "Bug.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
#include "MDeathEffet.h"
#include "ObjFactory.h"
#include "ObjMgr.h"


float M_fSound1 = 1.f;

CBug::CBug():m_iChange(0),m_eCurState(STATE_END),m_ePreState(STATE_END), m_ColCheck(0)
{
}

CBug::~CBug()
{
	Release();
}

void CBug::Initialize()
{
	m_fJump_Power = 10.f;
	m_fJump_Angle = PI / 3;
	m_iAdditionJump_MaxCount = 1;
	m_iAdditionJump_Count = m_iAdditionJump_MaxCount;

	m_fSpeed = 1.f;

	m_eRender = GAMEOBJECT;

	m_HP = 3;

	Set_Size(256.f, 256.f);

	m_fColC.x = m_tInfo.fCX * 0.35f;
	m_fColC.y = m_tInfo.fCY * 0.20f;

	m_TurnDirection = TURNLEFT;
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/bug/move.bmp", L"move");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/bug/dead.bmp", L"dead");

	//CSoundMgr::Get_Instance()->PlayBGM(L"M_hit.wav", M_fSound1);
	//CSoundMgr::Get_Instance()->PlayBGM(L"M_death.wav", M_fSound1);

	m_pFrameKey = L"move";
	CObj::FramSave(0,3,m_TurnDirection,50);

	m_eCurState = MOVE;

	m_ObjType = MONSTER;
}

int CBug::Update()
{
	/*if (m_TurnDirection == 0) {
		m_iChange = 1;
	}
	else {
		m_iChange = 0;
	}*/

	JumpEX();

	if (m_bDead)
		return OBJ_DEAD;

	CBug::Act();
	CBug::Motion_Change();

	CObj::Move_Frame();
	CObj::Update_Rect();
	return 0;
}

void CBug::Late_Update()
{
	if (m_StunEffect) {
		if (m_StunEffect->Get_Dead()) {
			m_StunEffect = nullptr;
		}
	}
}

void CBug::Render(HDC hDC)
{
	CObj::Camera_Col_Render_UD(hDC, 0, 0, 0);
	
	
}

void CBug::Release()
{
}

void CBug::Act()
{
	switch (m_eCurState)
	{
	case CBug::MOVE:
	{
		m_pFrameKey = L"move";
		m_eCurState = MOVE;
		CLine m_pLine;
		float fY = INFINITY;
		if (CLineMgr::Get_Instance()->CollisionLine_GroundEX(m_tInfo, m_fColC, &m_pLine, &fY)) { 
			if (m_tInfo.fX <= m_pLine.Get_Info()->tLpoint.fX+ m_tInfo.fCX*0.25f) {
				//m_tInfo.fX += m_fSpeed;
				//m_TurnDirection = 0;
				Set_TurnMotion(TURNLEFT);
				m_fSpeed = -1 * m_fSpeed; 
			}
			else if (m_tInfo.fX >= m_pLine.Get_Info()->tRpoint.fX-m_tInfo.fCX*0.25f) {
				//m_tInfo.fX -= m_fSpeed;
				//m_TurnDirection = 1;
				Set_TurnMotion(TURNRIGHT);
				m_fSpeed = -1 * m_fSpeed;
			}
			m_tInfo.fX += m_fSpeed;
		}
		else {
		}
		//m_tInfo.fX += m_fSpeed;aaa
		
	}

	Collision();

	if (m_HP <= 0) {
		CCameraMgr::Get_Instance()->ShakingStart(5.f); 
		m_pFrameKey = L"dead";
		m_eCurState = DEAD;
	}
		break;
	case CBug::DEAD:
		CSoundMgr::Get_Instance()->PlaySound(L"M_death.wav", MONSTER_EFFECT, M_fSound1);
		
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
	case CBug::HIT:
		CSoundMgr::Get_Instance()->PlaySound(L"M_hit2.wav", MONSTER_EFFECT, M_fSound1);
		if (m_bJump) {
			if (m_eDir == RIGHT) {
				m_tInfo.fX -= 7.f;
			}
			else if (m_eDir == LEFT) {
				m_tInfo.fX += 7.f;
			}
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.0044f * G);
		}
		else {
			
			m_CollisionCheck = false;
			m_pFrameKey = L"move";
			m_eCurState = MOVE;
		}
		break;
	default:
		break;
	}
}

void CBug::Motion_Change()
{
	if (m_ePreState != m_eCurState) {
		switch (m_eCurState)
		{
		case CBug::MOVE:
			FramSave(0, 3, m_TurnDirection, 200);
			break;
		case CBug::DEAD:
			FramSave(0, 2, m_TurnDirection, 200);
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBug::Collision()
{
	if (m_CollisionCheck) {
		if (m_CollisionObjID == PBULLET|| m_CollisionObjID == PMELEE) {
			m_eCurState = HIT;
			m_fSpeed_Vertical = 4.f;
			m_bJump = true;

			if (m_HitDamage >= m_HP) {
				m_HP = 0;
			}
			else {
				m_HP -= m_HitDamage;
			}

		}
	}

}
