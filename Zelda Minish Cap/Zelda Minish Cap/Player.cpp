#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "CameraComponent.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "HP.h"
#include "ObjFactory.h"
#include "Attack.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "SoulBullet.h"
#include "SceneMgr.h"
#include "Barrel.h"
#include "DashEffec.h"
#include "HealEffect.h"
#include "StunEffect.h"
#include "StunEffect2.h"


CPlayer::CPlayer() :m_iCheck(0), m_bOnGround(true), m_HealCheck(false), m_HealCheckTime(GetTickCount64()), m_bDashCool(true),
m_bDash(false), m_fDashMax(0.f), m_DashTime(GetTickCount64()), m_RunReady(0.f), m_PlayerState(nullptr), g_fSound(1.f),
m_SkillCheck(true), m_bHitCool(false), m_HitCoolTime(GetTickCount64()), m_HitSpeed(0.f), m_WallCheck(false), m_ATTACKNUM(0),
m_OneSound(false), m_DashSound(false), m_AttackCol(OBJID_END), m_GMMODE(false),
m_bDoubleJumpUnLock(true), m_WallUnLock(true),m_DashUnLock(true), m_OneParrying(true)
{
	
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	/*CCameraComponent* camera = new CCameraComponent();
	AddComponent(camera);
	CCharacter::Initialize();*/

	m_tInfo = { 2450.f, 100.f, 256.f, 128.f };

	m_fColC.x = m_tInfo.fCX * 0.25f;
	m_fColC.y = m_tInfo.fCY-50.f ;
	// 충돌 콜라이더 크기

	m_fJump_Power = 10.f;
	m_fJump_Angle = PI / 3;
	m_iAdditionJump_MaxCount = 2;
	m_iAdditionJump_Count = m_iAdditionJump_MaxCount;

	m_fSpeed = 15.f;
	m_fAccel = 3.f;

	m_HP = 5;
	m_Soul = 20;

	m_eRender = GAMEOBJECT;

	m_ObjType = PLAYER;

	

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/idle.bmp", L"idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/move.bmp", L"move");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/attack.bmp", L"attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/top_attack.bmp", L"top_attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/down_attack.bmp", L"down_attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/jump_start.bmp", L"jump_start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/jump_reach.bmp", L"jump_reach");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/jump_falling.bmp", L"jump_falling");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/motion/jump_landing.bmp", L"jump_landing");*/
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/idle.bmp", L"idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/death.bmp", L"death");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/walk.bmp", L"walk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/run.bmp", L"run");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/sit.bmp", L"sit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/stun.bmp", L"stun");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/lookdown.bmp", L"lookdown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/lookdown2idle.bmp", L"lookdown2idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/lookup.bmp", L"lookup");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/lookup2idle.bmp", L"lookup2idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/slash.bmp", L"slash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/slash2.bmp", L"slash2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/upslash.bmp", L"upslash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/downslash.bmp", L"downslash");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/doublejump.bmp", L"doublejump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/jump.bmp", L"jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/wall.bmp", L"wall");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/walljump.bmp", L"walljump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/fall.bmp", L"fall");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/dash.bmp", L"dash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/dash2idle.bmp", L"dash2idle");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/focus.bmp", L"focus");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/focus2idle.bmp", L"focus2idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/knight/fire.bmp", L"fire");

	m_pFrameKey = L"idle";

	Set_Size(60, 127);
	FramSave(0, 5, m_TurnDirection, 200);

	/*CSoundMgr::Get_Instance()->PlayBGM(L"P_dash.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_doublejump.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_fall.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_fireball.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_heal.wav", g_fSound);

	CSoundMgr::Get_Instance()->PlayBGM(L"P_hit.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_jump.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_jumpend.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_run.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_slash.wav", g_fSound);*/

	/*CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_armour.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_non.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_parring.wav", g_fSound);*/
	/*CSoundMgr::Get_Instance()->PlayBGM(L"P_walk.wav", g_fSound);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_wall_jump.wav", g_fSound);*/
}

int CPlayer::Update()
{
	if (!m_GMMODE) {
		if (m_bDash) {
			Dash();
		}
		else {
			CCharacter::Jump();
		}
	}

	if (m_GMMODE) {
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
			m_tInfo.fX -= 10.f;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
			m_tInfo.fX += 10.f;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
			m_tInfo.fY -= 10.f;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
			m_tInfo.fY += 10.f;
		}
	}

	/*if (CKeyMgr::Get_Instance()->Key_Down('W')) {
		m_Soul -= 5;
	}*/
	if (CKeyMgr::Get_Instance()->Key_Down('Q')) {
		if (m_Soul < 20) {
			m_Soul += 5;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down('T')) {
		if (m_HP > 1) {
			m_HP --;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down('1')) {
		if (!m_GMMODE) {
			m_GMMODE = true;
		}
		else {
			m_GMMODE = false;
		}
	}


	Wall_Coll_Check();

	if (m_eCurState != DASH|| m_eCurState != DEATH) {
		if (!m_GMMODE) {
			Collision();
		}
	}

	Parrying();

	
	
	if (m_Attack) {
		if (m_Attack->Get_CollisionObjID() == PLAYER) {
			if (!m_OneSound) {
				CSoundMgr::Get_Instance()->PlaySound(L"P_sword_non.wav", PLAYER_SWORD, g_fSound);
				m_OneSound = true;
			}
		}
		else if (m_Attack->Get_CollisionObjID() == MONSTER) {
			m_AttackCount++;
		}
	}
	

	CPlayer::Act();

	CPlayer::Motion_Change();

	CObj::Move_Frame();
	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (m_DashTime + 2000 < GetTickCount64()) {
		m_bDashCool = true;
		m_DashSound = false;
		m_DashTime = GetTickCount64();
	}

	

	if((m_eCurState==SLASH|| m_eCurState == UPSLASH|| m_eCurState == DOWNSLASH)&& m_Attack){
		//m_AttackCount += dynamic_cast<CAttack*>(m_Attack)->Get_AttSuc();
	}
 
	if (m_AttackCount >= 25) {
		if (m_Soul <= 15) {
			m_Soul += 5;
		}
		m_AttackCount = 0;
	}

	if (m_HitCoolTime + 1500 < GetTickCount64()) {

		m_bHitCool = false;
		m_HitCoolTime = GetTickCount64();
	} // 콜리션 쿨타임
	
	

 	if (m_Attack) {
		if (m_Attack->Get_Dead()) {
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			//CSoundMgr::Get_Instance()->StopSound(PLAYER_SWORD);
			//Safe_Delete(m_Attack); 
			m_Attack = nullptr;
			m_ATTACKNUM = 0;
		}
	}

	if (m_DashEffect) {
		if (m_DashEffect->Get_Dead()) {
			m_DashEffect = nullptr;
		}
	}

	if (m_HealEffect) {
		if (m_HealEffect->Get_Dead()) {
			m_HealEffect = nullptr;
		}
	}

	if (m_StunEffect1) {
		if (m_StunEffect1->Get_Dead()) {
			m_StunEffect1 = nullptr;
		}
	}
	if (m_StunEffect2) {
		if (m_StunEffect2->Get_Dead()) {
			m_StunEffect2 = nullptr;
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	
	CObj::Camera_Col_Render_LR(hDC,255,0,255);

	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	//WCHAR text[100];
	//	_stprintf_s(text, L"[Player] x : %f \t y : %f", m_tInfo.fX, m_tInfo.fY);
	//	TextOutW(hDC, 0, 0, text, lstrlen(text));

	//	POINT	ptMouse{};

	//	GetCursorPos(&ptMouse);	// 마우스 위치 값을 얻어오는 함수

	//	ScreenToClient(g_hWnd, &ptMouse); // 스크린 상의 좌표를 우리가 생성한 창 좌표로 변환

	//	CCameraMgr::Get_Instance()->Get_Point_RenderPos(ptMouse);
	//	
	//	_stprintf_s(text, L"x: %d\t y: %d",ptMouse.x, ptMouse.y);
	//	TextOutW(hDC, 0, 20, text, lstrlen(text));

		/*WCHAR _text[100];
		_stprintf_s(_text, L"objID: %d \t dir: %d \t col: %d\t hp: %d\t atc : %d\t wall : %d\T AN : %d",m_CollisionObjID,m_eDir,
			m_CollisionCheck,m_HP, m_AttackCount, m_WallCheck, m_ATTACKNUM);
		TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f)-90.f, LONG(tRenderPos.fY - m_fColC.y * 0.5f)-50.f, _text, lstrlen(_text));*/

		/*WCHAR state[100];
		_stprintf_s(_text, L"state: %s", m_PlayerState);
		TextOutW(hDC, m_tInfo.fX, m_tInfo.fY, state, lstrlen(state));*/

		/*WCHAR _text1[20];
		_stprintf_s(_text, L"dir : %d", m_eDir);
		TextOutW(hDC, 0, 80, _text1, lstrlen(_text1));*/
}

void CPlayer::Release()
{
}

void CPlayer::Attack()
{
	if (!m_Attack) {
		
		m_Attack = new CAttack;
		dynamic_cast<CAttack*>(m_Attack)->Set_PlayerState(m_eCurState);
		dynamic_cast<CAttack*>(m_Attack)->Set_TurnDir(m_TurnDirection);
		m_Attack->Initialize();
		CObjMgr::Get_Instance()->Add_Object(PMELEE, m_Attack);
		
		m_ATTACKNUM++;
	}

	/*CObj* Attack = new CAttack;
	dynamic_cast<CAttack*>(Attack)->Set_PlayerState(m_eCurState);
	dynamic_cast<CAttack*>(Attack)->Set_TurnDir(m_TurnDirection);
	Attack->Initialize();
	CObjMgr::Get_Instance()->Add_Object(PMELEE, Attack);*/

}

void CPlayer::SoulBullet()
{
	CObj* m_SoulBullet = new CSoulBullet;
	//dynamic_cast<CSoulBullet*>(m_Attack)->Set_PlayerState(m_eCurState);
	dynamic_cast<CSoulBullet*>(m_SoulBullet)->Set_TurnDir(m_TurnDirection);
	//m_SoulBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	//m_SoulBullet->Set_Size(479.f, 177.f);
	m_SoulBullet->Initialize();
	CObjMgr::Get_Instance()->Add_Object(PBULLET, m_SoulBullet);
	CSoundMgr::Get_Instance()->PlaySound(L"P_slash.wav", PLAYER_EFFECT, g_fSound*0.5f);
}

void CPlayer::Dash()
{
	if (m_TurnDirection == 1) {
		m_tInfo.fX -= m_fSpeed * m_fAccel;
		m_fDashMax += m_fSpeed * m_fAccel;
	}
	else if (m_TurnDirection == 0) {
		m_tInfo.fX += m_fSpeed * m_fAccel;
		m_fDashMax += m_fSpeed * m_fAccel;
	}

	if (m_fDashMax >= 200.f) {
		m_bDash = false;
		m_fDashMax = 0.f;
		
	}
	if (!m_DashSound) {
		CSoundMgr::Get_Instance()->PlaySound(L"P_dash.wav", PLAYER_EFFECT, g_fSound);
		m_DashSound = true;
	}
	if (!m_DashEffect) {
		m_DashEffect = CObjFactory<CDashEffec>::Create(m_tInfo.fX,m_tInfo.fY);
		if (m_TurnDirection == TURNLEFT) {
			m_DashEffect->Set_TurnDir(TURNRIGHT);
		}
		else {
			m_DashEffect->Set_TurnDir(TURNLEFT);
		}
		
		m_DashEffect->Initialize();
		CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_DashEffect);
	}
	
}

void CPlayer::DownAttack()
{
	

	if (m_Attack) {
		if (m_Attack->Get_CollisionCheck() && m_Attack->Get_CollisionObjID() == MONSTER) {
			m_fSpeed_Vertical = 7.f;
			m_bJump = true;
		}
	}
}

void CPlayer::Parrying()
{
	if (m_Attack) {
		if (m_Attack->Get_CollisionCheck() && (m_Attack->Get_CollisionObjID() == MBULLET|| m_Attack->Get_CollisionObjID() == MMELEE)) {
			CSceneMgr::Get_Instance()->SceneStop();

			if (m_OneParrying) {
				if (m_Attack->Get_CollisionObjID() == MBULLET) {
					CObj* barrel = CObjFactory<CBarrel>::Create(m_Attack->Get_CollisionPos().x, m_Attack->Get_CollisionPos().y);
					dynamic_cast<CBarrel*>(barrel)->Set_PlayerAttack();
					dynamic_cast<CBarrel*>(barrel)->Set_TurnDir(m_TurnDirection);
					barrel->Initialize();
					CObjMgr::Get_Instance()->Add_Object(PBULLET, barrel);
					CSoundMgr::Get_Instance()->PlaySound(L"P_sword_parring.wav", PLAYER_EFFECT, g_fSound);
				}
				m_OneParrying = false;
			}

		}
	}
}

void CPlayer::SkillCheck(STATE _CurState)
{
	if (m_SkillCheck) {
		if (_CurState == SLASH|| _CurState == UPSLASH|| _CurState == DOWNSLASH) {
			Attack();
			
			
		}
		/*else if(_CurState == DOWNSLASH){
			Attack();
			DownAttack();
		}*/
		else if (_CurState == FIRE) {
			SoulBullet();
		}
		m_SkillCheck = false;
	}
	
}

void CPlayer::Collision()
{
	if (!m_bHitCool)   {
		if (m_CollisionCheck) {
			if (m_CollisionObjID == MONSTER) {
				if (m_eCurState != DEATH) {
					m_eCurState = STUN;
					m_pFrameKey = L"stun";
					m_fSpeed_Vertical = 10.f;
					if (m_eDir == RIGHT) {
						m_HitSpeed = -10.f;
					}
					else if (m_eDir == LEFT) {
						m_HitSpeed = 10.f;
					}
					m_bJump = true;
					m_bHitCool = true;

					m_HP--;
					m_HPvec = (CObjMgr::Get_Instance()->Get_HP());	// hp ui가 반드시 player보다 먼저 만들어져야 한다.
					if (!m_HPvec.empty()) {
						for (int i = (m_HPvec.size() - 1); i >= 0; i--) {
							if (dynamic_cast<CHP*>(m_HPvec[i])->Get_CurState() == HPSTATE::FULL) {
								dynamic_cast<CHP*>(m_HPvec[i])->Set_AnimTurn();
								break;
							}
						}
						/*for ( i = CObjMgr::Get_Instance()->Get_HP().size() - 1; i >= 0; --i) {
							if (dynamic_cast<CHP*>(CObjMgr::Get_Instance()->Get_HP()[i])->Get_CurState() == HPSTATE::FULL) {
								dynamic_cast<CHP*>(CObjMgr::Get_Instance()->Get_HP()[i])->Set_AnimTurn();
								}
						}*/
					}
					if (!m_StunEffect1) {
						m_StunEffect1 = CObjFactory<CStunEffect>::Create(m_tInfo.fX, m_tInfo.fY);
						m_StunEffect1->Set_TurnDir(m_TurnDirection);
						m_StunEffect1->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect1);
					}
					if (!m_StunEffect2) {
						m_StunEffect2 = CObjFactory<CStunEffect2>::Create(m_tInfo.fX, m_tInfo.fY);
						m_StunEffect2->Set_TurnDir(m_TurnDirection);
						m_StunEffect2->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect2);
					}
				}
				
			}
			if (m_CollisionObjID == MBULLET|| m_CollisionObjID == MMELEE|| m_CollisionObjID == MBULLET2) {
				if (m_eCurState != DEATH) {
					m_eCurState = STUN;
					m_pFrameKey = L"stun";
					m_fSpeed_Vertical = 10.f;
					if (m_eDir == RIGHT) {
						m_HitSpeed = -10.f;
					}
					else if (m_eDir == LEFT) {
						m_HitSpeed = 10.f;
					}
					m_bJump = true;
					m_bHitCool = true;

					m_HP--;
					m_HPvec = (CObjMgr::Get_Instance()->Get_HP());	// hp ui가 반드시 player보다 먼저 만들어져야 한다.
					if (!m_HPvec.empty()) {
						for (int i = (m_HPvec.size() - 1); i >= 0; i--) {
							if (dynamic_cast<CHP*>(m_HPvec[i])->Get_CurState() == HPSTATE::FULL) {
								dynamic_cast<CHP*>(m_HPvec[i])->Set_AnimTurn();
								break;
							}
						}
						/*for ( i = CObjMgr::Get_Instance()->Get_HP().size() - 1; i >= 0; --i) {
							if (dynamic_cast<CHP*>(CObjMgr::Get_Instance()->Get_HP()[i])->Get_CurState() == HPSTATE::FULL) {
								dynamic_cast<CHP*>(CObjMgr::Get_Instance()->Get_HP()[i])->Set_AnimTurn();
								}
						}*/
					}
					if (!m_StunEffect1) {
						m_StunEffect1 = CObjFactory<CStunEffect>::Create(m_tInfo.fX, m_tInfo.fY);
						m_StunEffect1->Set_TurnDir(m_TurnDirection);
						m_StunEffect1->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect1);
					}
					if (!m_StunEffect2) {
						m_StunEffect2 = CObjFactory<CStunEffect2>::Create(m_tInfo.fX, m_tInfo.fY);
						m_StunEffect2->Set_TurnDir(m_TurnDirection);
						m_StunEffect2->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect2);
					}
				}

			}
		}
		
	}

	if (m_CollisionCheck) {
		if (m_CollisionObjID == PWALL&& (m_eDir == LEFT || m_eDir == RIGHT)) {
			if (m_WallUnLock) {
				if (!m_WallCheck)
				{
					m_fSpeed_Vertical = 3.f;
					m_pFrameKey = L"wall";
					m_eCurState = WALL;
					m_WallCheck = true;
				}
			}
		}
		
	}
	else if (m_CollisionObjID == OBJID_END) {
		m_WallCheck = false;
	}
}

void CPlayer::Act()
{
	switch (m_eCurState)
	{
	case CPlayer::IDLE:
		m_eCurState = IDLE;
		m_pFrameKey = L"idle";
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {

			//m_TurnDirection = TURNLEFT;
			Set_TurnMotion(TURNLEFT);
			m_pFrameKey = L"walk";
			m_eCurState = WALK;

		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {

			//m_TurnDirection = TURNRIGHT;
			Set_TurnMotion(TURNRIGHT);
			m_pFrameKey = L"walk";
			m_eCurState = WALK;

		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {

			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"upslash";
				m_eCurState = UPSLASH;
				
			}
			else {
				/*m_pFrameKey = L"lookup";
				m_eCurState = LOOKUP;*/
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A')) {
			m_pFrameKey = L"slash";
			m_eCurState = SLASH;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
			m_pFrameKey = L"lookdown";
			m_eCurState = LOOKDOWN;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('C')) {
			if (m_DashUnLock) {
				if (m_bDashCool) {
					m_pFrameKey = L"dash";
					m_eCurState = DASH;
				}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
			if (0 < m_iAdditionJump_Count--)
			{
				m_fSpeed_Vertical = 12.f;
				m_bJump = true;
				m_pFrameKey = L"jump";
				m_eCurState = JUMP;
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('X')) {
			m_pFrameKey = L"sit";
			m_eCurState = SIT;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('S')) {
			if (m_Soul > 0) {
				m_pFrameKey = L"fire";
				m_eCurState = FIRE;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down('D')) {
			if(m_Soul>0&&m_HP<5){
			m_pFrameKey = L"focus";
			m_eCurState = FOCUS;
			}
		}
		//Collision();// 피격

		if (m_fSpeed_Vertical<0) {
			float fy=0.f;
			if (!CLineMgr::Get_Instance()->CollisionLine_Ground(m_tInfo, &fy)) {
				m_pFrameKey = L"fall";
				m_eCurState = FALL;
			}
		}

		/*if (!m_bJump) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}*/

		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}

		break;
	case CPlayer::DEATH:
		if (!m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"P_death.wav", PLAYER_EFFECT, g_fSound);
			m_OneSound = true;
		}
		if (!m_OneSound) {

			m_OneSound = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_eCurState = IDLE;
			m_pFrameKey = L"idle";
			m_HP=5;
		}
		break;
	case CPlayer::WALK:
		CSoundMgr::Get_Instance()->PlaySound(L"P_walk.wav", PLAYER_EFFECT, g_fSound);
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {

			if (m_eDir != LEFT) {
				m_tInfo.fX -= m_fSpeed * 0.5f;
				m_RunReady += m_fSpeed;
			}
			Set_TurnMotion(TURNLEFT);

			if (m_RunReady > 500.f) {
				m_pFrameKey = L"run";
				m_eCurState = RUN;
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {

			if (m_eDir != RIGHT) {
				m_tInfo.fX += m_fSpeed * 0.5f;
				m_RunReady += m_fSpeed;
			}
			Set_TurnMotion(TURNRIGHT);

			if (m_RunReady > 500.f) {
				m_pFrameKey = L"run";
				m_eCurState = RUN;
			}
		}
		else {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"upslash";
				m_eCurState = UPSLASH;
				
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A')) {
			m_pFrameKey = L"slash";
			m_eCurState = SLASH;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('C')) {
			if (m_DashUnLock) {
				if (m_bDashCool) {
					m_pFrameKey = L"dash";
					m_eCurState = DASH;
				}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
			if (0 < m_iAdditionJump_Count--)
			{
				m_fSpeed_Vertical = 12.f;
				m_bJump = true;
				m_pFrameKey = L"jump";
				m_eCurState = JUMP;
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('S')) {
			if (m_Soul > 0) {
				m_pFrameKey = L"fire";
				m_eCurState = FIRE;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down('D')) {
			if (m_Soul > 0 && m_HP < 5) {
				m_pFrameKey = L"focus";
				m_eCurState = FOCUS;
			}
		}
		//Collision();// 피격
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}
		break;
	case CPlayer::RUN:
		CSoundMgr::Get_Instance()->PlaySound(L"P_run.wav", PLAYER_EFFECT, g_fSound*0.5f);
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {

			if (m_eDir != LEFT) {
				m_tInfo.fX -= m_fSpeed;
			}
			//m_TurnDirection = TURNLEFT;
			Set_TurnMotion(TURNLEFT);

		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {

			if (m_eDir != RIGHT) {
				m_tInfo.fX += m_fSpeed;
			}
			//m_TurnDirection = TURNRIGHT;
			Set_TurnMotion(TURNRIGHT);
		}
		else {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
			m_RunReady = 0;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"upslash";
				m_eCurState = UPSLASH;
				
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A')) {
			m_pFrameKey = L"slash";
			m_eCurState = SLASH;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('C')) {
			if (m_DashUnLock) {
				if (m_bDashCool) {
					m_pFrameKey = L"dash";
					m_eCurState = DASH;
				}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
			if (0 < m_iAdditionJump_Count--)
			{
				m_fSpeed_Vertical = 12.f;
				m_bJump = true;
				m_pFrameKey = L"jump";
				m_eCurState = JUMP;
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('S')) {
			if (m_Soul > 0) {
				m_pFrameKey = L"fire";
				m_eCurState = FIRE;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down('D')) {
			if (m_Soul > 0 && m_HP < 5) {
				m_pFrameKey = L"focus";
				m_eCurState = FOCUS;
			}
		}
		//Collision();// 피격
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}
		/*if (m_fSpeed_Vertical < 0) {
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/
		break;
	case CPlayer::SIT:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE ;
		}
		break;
	case CPlayer::STUN:
		CSoundMgr::Get_Instance()->PlaySound(L"P_hit.wav", PLAYER_EFFECT, g_fSound);
		if (m_bJump) {

			m_tInfo.fX += m_HitSpeed;
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.044f * G);
		}
		else {

			////m_CollisionCheck = false;
			//if (m_HitCoolTime + 1500 < GetTickCount64()) {
			//	m_pFrameKey = L"idle";
			//	m_eCurState = IDLE;
			//	m_bHitCool = false;
			//	m_HitCoolTime = GetTickCount64();
			//}
			//m_CollisionCheck = false;
			
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}
		break;
	case CPlayer::LOOKDOWN:
		// 키를 때면 추가
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"lookdown2idle";
			m_eCurState = LOOKDOWN2IDLE;
		}
		break;
	case CPlayer::LOOKDOWN2IDLE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		break;
	case CPlayer::LOOKUP:
		// 키를 때면 추가
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"lookup2idle";
			m_eCurState = LOOKUP2IDLE;
		}
		break;
	case CPlayer::LOOKUP2IDLE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		break;
	case CPlayer::SLASH:
		SkillCheck(SLASH);
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"slash2";
			m_eCurState = SLASH2;
			m_SkillCheck = true;
		}
		//Collision();// 피격
		break;
	case CPlayer::SLASH2:
		//Attack();
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		/*if (m_fSpeed_Vertical < 0) {
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/
		//Collision();// 피격

		/*if (m_fSpeed_Vertical < 0) {

			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}*/
		break;
	case CPlayer::UPSLASH:
		SkillCheck(UPSLASH);
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
			m_SkillCheck = true;
		}
		/*if (m_fSpeed_Vertical < 0) {
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/
		//Collision();// 피격

		/*if (m_fSpeed_Vertical < 0) {

			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/
		/*if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}*/
		break;
	case CPlayer::DOWNSLASH:
		SkillCheck(DOWNSLASH);
		//DownAttack();
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
			m_SkillCheck = true;
			
		}

		if (m_bJump) {
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.0044f * G);
		}

		/*if (m_fSpeed_Vertical < 0) {
			
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/


		//Collision();// 피격
		/*if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}*/
		break;
	case CPlayer::DOUBLEJUMP:
		CSoundMgr::Get_Instance()->PlaySound(L"P_doublejump.wav", PLAYER_EFFECT, g_fSound);
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {

			if (m_eDir != LEFT) {
				m_tInfo.fX -= m_fSpeed;
			}
			//m_TurnDirection = TURNLEFT;
			Set_TurnMotion(TURNLEFT);

		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {

			if (m_eDir != RIGHT) {
				m_tInfo.fX += m_fSpeed;
			}
			//m_TurnDirection = TURNRIGHT;
			Set_TurnMotion(TURNRIGHT);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"upslash";
				m_eCurState = UPSLASH;
				//Attack();
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"downslash";
				m_eCurState = DOWNSLASH;
				//Attack();
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A')) {
			m_pFrameKey = L"slash";
			m_eCurState = SLASH;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('C')) {
			if (m_DashUnLock) {
				if (m_bDashCool) {
					m_pFrameKey = L"dash";
					m_eCurState = DASH;
				}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('S')) {
			if (m_Soul > 0) {
				m_pFrameKey = L"fire";
				m_eCurState = FIRE;
			}
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			if (m_fSpeed_Vertical < 0) {
				m_pFrameKey = L"fall";
				m_eCurState = FALL;
			}
		}
		//Collision();// 피격
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}
		break;
	case CPlayer::JUMP:
		CSoundMgr::Get_Instance()->PlaySound(L"P_jump.wav", PLAYER_EFFECT, g_fSound);
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {

			if (m_eDir != LEFT) {
				m_tInfo.fX -= m_fSpeed;
			}
			//m_TurnDirection = TURNLEFT;
			Set_TurnMotion(TURNLEFT);

		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {

			if (m_eDir != RIGHT) {
				m_tInfo.fX += m_fSpeed;
			}
			//m_TurnDirection = TURNRIGHT;
			Set_TurnMotion(TURNRIGHT);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"upslash";
				m_eCurState = UPSLASH;
				
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"downslash";
				m_eCurState = DOWNSLASH;
				
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A')) {
			m_pFrameKey = L"slash";
			m_eCurState = SLASH;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('C')) {
			if (m_DashUnLock) {
				if (m_bDashCool) {
					m_pFrameKey = L"dash";
					m_eCurState = DASH;
				}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('S')) {
			if (m_Soul > 0) {
				m_pFrameKey = L"fire";
				m_eCurState = FIRE;
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
			if (m_bDoubleJumpUnLock) {
				if (0 < m_iAdditionJump_Count--)
				{
					m_fSpeed_Vertical = 14.f;
					m_bJump = true;
					m_pFrameKey = L"doublejump";
					m_eCurState = DOUBLEJUMP;
				}
			}
		}

		if (m_fSpeed_Vertical < 0) {
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}
		
		//Collision();// 피격
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}
		break;
	case CPlayer::JUMPEND:
		if (!m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"P_jumpend.wav", PLAYER_EFFECT, g_fSound*0.5f);
			m_OneSound = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd/3) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		break;
	case CPlayer::WALL:
		if (!m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"P_wall.wav", PLAYER_EFFECT, g_fSound * 0.5f);
			m_OneSound = true;
		}
		if (m_eDir == LEFT) {
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical = (0.0000000015f * G);
			}
			else {
				Set_TurnMotion(TURNRIGHT);
				m_pFrameKey = L"idle";
				m_eCurState = IDLE;
			}

			if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
				m_fSpeed_Vertical = 7.f;
				m_bJump = true;
				m_pFrameKey = L"walljump";
				m_eCurState = WALLJUMP;
			}

		}
		
		if (m_eDir == RIGHT) {
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical = (0.0000000015f * G);
			}
			else {
				Set_TurnMotion(TURNLEFT);
				m_pFrameKey = L"idle";
				m_eCurState = IDLE;
			}

			if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
				m_fSpeed_Vertical = 7.f;
				m_bJump = true;
				m_pFrameKey = L"walljump";
				m_eCurState = WALLJUMP;
			}
		}
		
		
	
		break;
	case CPlayer::WALLJUMP:
		if (!m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"P_wall_jump.wav", PLAYER_EFFECT, g_fSound);
			m_OneSound = true;
		}
		if (m_TurnDirection == TURNLEFT) {
			m_tInfo.fX += m_fSpeed;
		}
		else if (m_TurnDirection == TURNRIGHT) {
			m_tInfo.fX -= m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
			if (0 < m_iAdditionJump_Count--)
			{
				
			}
			if (m_TurnDirection == VK_RIGHT) {
				Set_TurnMotion(VK_LEFT);
			}
			else {
				Set_TurnMotion(TURNRIGHT);
			}
			if (m_bDoubleJumpUnLock) {
				m_fSpeed_Vertical = 14.f;
				m_bJump = true;
				m_pFrameKey = L"doublejump";
				m_eCurState = DOUBLEJUMP;
			}
		}

		if (m_fSpeed_Vertical < 0) {
			if (m_TurnDirection == VK_RIGHT) {
				Set_TurnMotion(VK_LEFT);
			}
			else {
				Set_TurnMotion(TURNRIGHT);
			}
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}
		break;
	case CPlayer::FALL:
		//CSoundMgr::Get_Instance()->PlaySound(L"P_fall.wav", PLAYER_EFFECT, g_fSound*0.25f);
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {

			if (m_eDir != LEFT) {
				m_tInfo.fX -= m_fSpeed;
			}
			//m_TurnDirection = TURNLEFT;
			Set_TurnMotion(TURNLEFT);

		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {

			if (m_eDir != RIGHT) {
				m_tInfo.fX += m_fSpeed;
			}
			//m_TurnDirection = TURNRIGHT;
			Set_TurnMotion(TURNRIGHT);
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"upslash";
				m_eCurState = UPSLASH;
				
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
			if (CKeyMgr::Get_Instance()->Key_Down('A')) {
				m_pFrameKey = L"downslash";
				m_eCurState = DOWNSLASH;
				
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('A')) {
			m_pFrameKey = L"slash";
			m_eCurState = SLASH;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('C')) {
			if (m_DashUnLock) {
				if (m_bDashCool) {
					m_pFrameKey = L"dash";
					m_eCurState = DASH;
				}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('S')) {
			if (m_Soul > 0) {
				m_pFrameKey = L"fire";
				m_eCurState = FIRE;
			}
		}

		if (!m_bJump) {
			//CSoundMgr::Get_Instance()->PlaySound(L"P_jumpend.wav", PLAYER_EFFECT, g_fSound);
			m_pFrameKey = L"idle";
			m_eCurState = JUMPEND;
		}
		//Collision();// 피격
		if (m_HP <= 0) {
			m_pFrameKey = L"death";
			m_eCurState = DEATH;
		}
		break;
	case CPlayer::DASH:
		m_bDash = true;
		m_bDashCool = false;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		/*if (m_fSpeed_Vertical < 0) {
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/
		//Collision();// 피격
		break;
	case CPlayer::DASH2IDLE:
		break;
	case CPlayer::FOCUS:
		if (!m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"P_heal.wav", PLAYER_EFFECT, g_fSound);
			m_OneSound = true;
		}
		if (!m_HealEffect) {
			m_HealEffect = CObjFactory<CHealEffect>::Create(m_tInfo.fX, m_tInfo.fY);
			m_HealEffect->Set_TurnDir(m_TurnDirection);
			m_HealEffect->Initialize();
			CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_HealEffect);
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_HPvec = (CObjMgr::Get_Instance()->Get_HP());	
			if (!m_HPvec.empty()) {
				for (int i = 0; i < (m_HPvec.size()); i++) {
					if (dynamic_cast<CHP*>(m_HPvec[i])->Get_CurState() == HPSTATE::DESTORY) {
						dynamic_cast<CHP*>(m_HPvec[i])->Set_AnimTurn();
						m_HP++;
						m_Soul -= 5;
						break;
					}
				}
			}
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
		}
		//Collision();// 피격
		CSoundMgr::Get_Instance()->PlaySound(L"heal.wav", SOUND_EFFECT, g_fSound);
		break;
	case CPlayer::FOCUS2IDLE:
		break;
	case CPlayer::FIRE:
		SkillCheck(FIRE);
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {

			m_Soul -= 5;
			m_pFrameKey = L"idle";
			m_eCurState = IDLE;
			m_SkillCheck = true;
		}
		//Collision();// 피격
		/*if (m_fSpeed_Vertical < 0) {
			m_pFrameKey = L"fall";
			m_eCurState = FALL;
		}*/
		break;
	default:
		break;
	}
}

void CPlayer::Motion_Change()
{
	if ((m_ePreState != m_eCurState)) {
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			Set_Size(60, 127);
			FramSave(0, 5, m_TurnDirection, 100);
			break;
		case CPlayer::DEATH:
			Set_Size(107, 124);
			FramSave(0, 11, m_TurnDirection, 500);
			break;
		case CPlayer::WALK:
			Set_Size(60, 127);
			FramSave(0, 6, m_TurnDirection, 200);
			break;
		case CPlayer::RUN:
			Set_Size(82, 127);
			FramSave(0, 11, m_TurnDirection, 100);
			break;
		case CPlayer::SIT:
			Set_Size(76, 129);
			FramSave(0, 4, 0, 200);
			break;
		case CPlayer::STUN:
			Set_Size(94, 124);
			FramSave(0, 0, m_TurnDirection, 50);
			break;
		case CPlayer::LOOKDOWN:
			Set_Size(67, 127);
			FramSave(0, 0, m_TurnDirection, 200);
			break;
		case CPlayer::LOOKDOWN2IDLE:
			Set_Size(67, 127);
			FramSave(0, 1, m_TurnDirection, 200);
			break;
		case CPlayer::LOOKUP:
			Set_Size(58, 127);
			FramSave(0, 0, m_TurnDirection, 200);
			break;
		case CPlayer::LOOKUP2IDLE:
			Set_Size(58, 127);
			FramSave(0, 1, m_TurnDirection, 200);
			break;
		case CPlayer::SLASH:
			Set_Size(82, 127);
			FramSave(0, 4, m_TurnDirection, 40);
			break;
		case CPlayer::SLASH2:
			Set_Size(118, 127);
			FramSave(0, 4, m_TurnDirection, 40);
			break;
		case CPlayer::UPSLASH:
			Set_Size(95, 121);
			FramSave(0, 4, m_TurnDirection, 80);
			break;
		case CPlayer::DOWNSLASH:
			Set_Size(118, 121);
			FramSave(0, 4, m_TurnDirection, 80);
			break;
		case CPlayer::DOUBLEJUMP:
			Set_Size(116, 129);
			FramSave(0, 7, m_TurnDirection, 70);
			break;
		case CPlayer::JUMP:
			Set_Size(77, 127);
			FramSave(0, 5, m_TurnDirection, 100);
			break;
		case CPlayer::JUMPEND:
			Set_Size(60, 127);
			FramSave(0, 5, m_TurnDirection, 100);
			break;
		case CPlayer::WALL:
			Set_Size(75, 128);
			FramSave(0, 3, m_TurnDirection, 200);
			break;
		case CPlayer::WALLJUMP:
			Set_Size(97, 123);
			FramSave(0, 5, m_TurnDirection, 100);
			break;
		case CPlayer::FALL:
			Set_Size(87, 129);
			FramSave(0, 5, m_TurnDirection, 600);
			break;
		case CPlayer::DASH:
			Set_Size(172, 114);
			FramSave(0, 6, m_TurnDirection, 30);
			break;
		case CPlayer::DASH2IDLE:
			Set_Size(124, 127);
			FramSave(0, 3, m_TurnDirection, 200);
			break;
		case CPlayer::FOCUS:
			Set_Size(94, 115);
			FramSave(0, 9, m_TurnDirection, 200);
			break;
		case CPlayer::FOCUS2IDLE:
			Set_Size(62, 127);
			FramSave(0, 1, m_TurnDirection, 200);
			break;
		case CPlayer::FIRE:
			Set_Size(87, 127);
			FramSave(0, 6, m_TurnDirection, 100);
			break;
		default:
			break;
		}

		if (m_ePreState == WALLJUMP) {
			if (m_TurnDirection == TURNRIGHT) {
				m_TurnDirection = TURNLEFT;
			}
			else if (m_TurnDirection == TURNLEFT) {
				m_TurnDirection - TURNRIGHT;
			}
		}
		m_OneParrying = true;

		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		m_OneSound = false;
		m_ePreState = m_eCurState;
		//m_bChangeM = false;
	}
}

void CPlayer::Wall_Coll_Check()
{
	fPOINT fLP, fRP;

	if (CLineMgr::Get_Instance()->CollisionLine_Wall(m_tCollider, &fLP, &fRP)) {

		float relativeX = m_tInfo.fX - (fLP.x + fRP.x) / 2;
		float relativeY = m_tInfo.fY - (fLP.y + fRP.y) / 2;

		bool LineCollRight = (fLP.x < fRP.x);

		if (abs(relativeX) > abs(relativeY)) {
			//m_tInfo.fX -= copysign(m_tInfo.fCX / 2, relativeX);
			//m_tInfo.fX -= m_fSpeed;
			if (LineCollRight&&m_tInfo.fX< fLP.x) {
				//m_tInfo.fX = fLP.x - m_tInfo.fCX * 0.5f;
				m_tInfo.fX -= m_fSpeed;
			}
			else if (!LineCollRight && m_tInfo.fX > fLP.x) {
				//m_tInfo.fX = fLP.x + m_tInfo.fCX * 0.5f;
				m_tInfo.fX += m_fSpeed;
			}
			
		}
		else {
			//m_tInfo.fY -= copysign(m_tInfo.fCY / 2, relativeY);
			m_tInfo.fY += m_fSpeed;
		}


	}
}

//void CPlayer::FramSave(int _start, int _end, int _turnDir, int _dwspeed)
//{
//	m_tFrame.iFrameStart = _start;
//	m_tFrame.iFrameEnd = _end;
//	m_tFrame.iMotion = _turnDir;
//	m_tFrame.dwSpeed = _dwspeed;
//	m_tFrame.dwTime = GetTickCount64();
//}

