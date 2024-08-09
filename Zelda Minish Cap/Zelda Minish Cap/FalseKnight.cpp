#include "FalseKnight.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "BossAttack.h"
#include "WaveAttack.h"
#include "Death.h"
#include "Death2.h"
#include "ObjFactory.h"
#include "Barrel.h"
#include "BossWall.h"
#include "SoundMgr.h"
#include "MDeathEffet.h"

float B_Sound = 1.f;

CFalseKnight::CFalseKnight() :m_Defense(0), m_PatternCheck(PATTERN_END), m_Distance(0.f), m_JumpAttackTime(GetTickCount64()),
m_JumpCheck(false), m_tempo(0), m_Distance2(0.f), m_bRun(true), m_fOpposite(0.f), m_bEscapeWall(false), m_eJumpState(FRONTJUMP),
m_life(2), m_StunCheck(false), m_Attack2Count(7), m_BarrelTempo(0), m_HitTime(GetTickCount64()), m_bHitCheck(false), m_bReady(false),
m_OneSound(true), m_StunHit(false)
{
}

CFalseKnight::~CFalseKnight()
{
	Release();
}

void CFalseKnight::Initialize()
{

	Set_Size(1400.f, 1400.f);

	/*m_fColC.x = 300.f;
	m_fColC.y = 370.f;*/
	m_fColC.x = m_tInfo.fCX*0.25f;
	m_fColC.y = m_tInfo.fCY * 0.25f;

	m_fJump_Power = 10.f;
	m_fJump_Angle = PI / 3;

	m_fSpeed = 10.f;
	m_fAccel = 3.f;

	m_HP = 10;
	m_Defense = 10;

	m_AttackRange;
	m_JumpRange;
	m_ShockWaveRange;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/idle.bmp", L"Boss1_idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/turn.bmp", L"Boss1_turn");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/hit.bmp", L"Boss1_hit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/run.bmp", L"Boss1_run");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/attack.bmp", L"attack");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/attack2.bmp", L"attack2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/attackend.bmp", L"attackend2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/attackinit.bmp", L"attackinit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jump.bmp", L"Boss1_jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jumpattack1.bmp", L"jumpattack1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jumpattack2.bmp", L"jumpattack2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jumpattack3.bmp", L"jumpattack3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jumpattackinit.bmp", L"jumpattackinit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jumpend.bmp", L"jumpend");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/jumpinit.bmp", L"jumpinit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/stunopen.bmp", L"stunopen");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/stunclose.bmp", L"stunclose");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/stunroll.bmp", L"stunroll");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/stunrollend.bmp", L"stunrollend");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/death1.bmp", L"Boss1_death");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/death2.bmp", L"Boss1_death2");


	m_eCurState = READY;

	//m_pFrameKey = L"Boss1_idle";

	////Set_Size(620.6f, 390.f);
	//FramSave(0, 4, m_TurnDirection, 200);

	/*m_pFrameKey = L"jumpattack1";

	Set_Size(841.5f, 624.f);
	FramSave(0, 1, m_TurnDirection, 500);*/

	m_eRender = GAMEOBJECT;

	m_ObjType = MONSTER;

}

int CFalseKnight::Update()
{
	if (m_bDead) {

		for (auto& iter : m_Wall) {
			dynamic_cast<CBossWall*>(iter)->Set_Distroy();
		}

		return OBJ_DEAD;
	}
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	if (m_bReady) {
		JumpEX();
	}
	
	Act();
	Motion_Change();

	if (m_eCurState != DEATH&&m_eCurState != STUNCLOSE) {
		Collision();
	}

	if (!m_bHitCheck) {
		if (m_HitTime + 500 < GetTickCount64()) {
			m_bHitCheck = true;
			//m_StunHit = false;
			m_HitTime = GetTickCount64();
			m_CollisionObjID = OBJID_END;
			m_CollisionCheck = false;
		}
	}

	Barrel();

	CObj::Move_Frame();
	CObj::Update_Rect();
	return 0;
}

void CFalseKnight::Late_Update()
{
	if (m_bRun&&m_eCurState==RUN) {
		m_bEscapeWall = false;
		//m_CollisionObjID = OBJID_END;
	} // 달리다가 벽에 부딪쳤을 때 빠져나온다.

	if (m_BossAttack) {
		if (m_BossAttack->Get_Dead()) {
			m_BossAttack = nullptr;
		}
	}

	if (m_BossWave) {
		if (m_BossWave->Get_Dead()) {
			m_BossWave = nullptr;
		}
	}

	if (m_eCurState != STUNROLL) {
		if (m_Defense < 0) {
			m_pFrameKey = L"stunroll";
			m_eCurState = STUNROLL;
			m_Defense = 10.f;
			m_fSpeed_Vertical = 3.f;
			m_bJump = true;

		}
	}

	if (m_StunEffect) {
		if (m_StunEffect->Get_Dead()) {
			m_StunEffect = nullptr;
		}
	}
	
}

void CFalseKnight::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	//CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	if (m_TurnDirection == TURNRIGHT)
	{
		GdiTransparentBlt(hDC,
			(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
			(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f)+200.f,
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(7, 7, 7)); // 제거하고자 하는 색상
	}
	else if (m_TurnDirection == TURNLEFT)
	{
		GdiTransparentBlt(hDC,
			(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
			(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f) + 200.f,
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			(m_tFrame.iFrameEnd - m_tFrame.iFrameStart) * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(7, 7, 7)); // 제거하고자 하는 색상
	}

	//HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 0, 255));
	//HPEN hPrePen = (HPEN)SelectObject(hDC, hGreenPen);
	//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//Rectangle(hDC,
	//	LONG(tRenderPos.fX - m_fColC.x * 0.5f),
	//	LONG(tRenderPos.fY - m_fColC.y * 0.5f),
	//	LONG(tRenderPos.fX + m_fColC.x * 0.5f),
	//	LONG(tRenderPos.fY + m_fColC.y * 0.5f));

	//SelectObject(hDC, hPrePen);
	//DeleteObject(hGreenPen);
	//SelectObject(hDC, OldBrush);
	//DeleteObject(myBrush);
	//

	//	WCHAR _text[80];
	//	_stprintf_s(_text, L"objID: %d \t dir: %d \t col: %d\t rand: %d\t jumpcheck: %d",m_CollisionObjID,m_eDir,
	//		m_CollisionCheck,m_Rand,m_eJumpState);
	//	TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f), LONG(tRenderPos.fY - m_fColC.y * 0.5f), _text, lstrlen(_text));
	//	WCHAR _text1[10];
	//	_stprintf_s(_text, L"hp: %d\t defense: %d\t",m_HP,m_Defense );
	//	TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f), LONG(tRenderPos.fY - m_fColC.y * 0.5f)-30.f,
	//		_text1, lstrlen(_text1));
}

void CFalseKnight::Release()
{
	
}

void CFalseKnight::Act()
{
	switch (m_eCurState)
	{
	case CFalseKnight::READY:
		if (m_pTarget->Get_Info()->fX > m_tInfo.fX) {
			m_bReady = true;

			m_Wall.push_back(CObjFactory<CBossWall>::Create(3775.f, 2050.f));
			dynamic_cast<CBossWall*>(m_Wall.back())->Set_WallTurn(TURNRIGHT);
			CObjMgr::Get_Instance()->Add_Object(PWALL,m_Wall.back());
			m_Wall.push_back(CObjFactory<CBossWall>::Create(6530.f, 2050.f));
			dynamic_cast<CBossWall*>(m_Wall.back())->Set_WallTurn(TURNLEFT);
			CObjMgr::Get_Instance()->Add_Object(PWALL, m_Wall.back());
			m_pFrameKey = L"Boss1_idle";
			m_eCurState = IDLE;
		}
		break;
	case CFalseKnight::IDLE:
		
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			if (m_StunCheck) {
				
			}
			else {
				if (m_pTarget->Get_Info()->fX > m_tInfo.fX) {
					Set_TurnMotion(TURNRIGHT);
				}
				else if (m_pTarget->Get_Info()->fX < m_tInfo.fX) {
					Set_TurnMotion(TURNLEFT);
				}
				
			}
			m_pFrameKey = L"Boss1_turn";
			m_eCurState = TURN;
		}
		
		break;
	case CFalseKnight::TURN:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			
			if (m_StunCheck) {
				if (m_Attack2Count <= 0) {
					m_pFrameKey = L"Boss1_idle";
					m_eCurState = IDLE;
					m_StunCheck = false;
					m_Attack2Count = 7;
				}
				else {
					/*if (m_tempo > 5) {
						
						m_tempo = 0;
					}
					m_tempo++;*/

					m_pFrameKey = L"attack";
					m_eCurState = ATTACK2;
					--m_Attack2Count;
				}
			}
			else {
				m_pFrameKey = L"jumpinit";
			m_eCurState = JUMPINIT;

			/*m_pFrameKey = L"attackinit";
			m_eCurState = ATTACKINIT;*/

			/*m_pFrameKey = L"Boss1_run";
			m_eCurState = RUN;
			if (m_TurnDirection == TURNLEFT) {
				m_Distance = -1*m_fSpeed;
			}
			else if (m_TurnDirection == TURNRIGHT) {
				m_Distance = m_fSpeed;
			}
			m_bRun = true;*/

			/*m_pFrameKey = L"jumpattack1";
			m_eCurState = JUMPATTACK1;*/

				/*m_pFrameKey = L"Boss1_idle";
				m_eCurState = IDLE;*/
			}
			
		}
		break;
	case CFalseKnight::RUN:
		//CCameraMgr::Get_Instance()->ShakingEnd();
		CSoundMgr::Get_Instance()->PlaySound(L"B_run2.wav", BOSS_RUN, B_Sound);
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_run_voice.wav", BOSS_VOICE, B_Sound);
			m_OneSound = false;
		}
		if (!m_bRun) {
			m_OneSound = true;
			m_pFrameKey = L"Boss1_idle";
			m_eCurState = IDLE;
			CSoundMgr::Get_Instance()->StopSound(BOSS_RUN);
		}
		else {
			m_tInfo.fX += m_Distance;
			//Collision();
		}
		
		break;
	case CFalseKnight::HIT:
		break;
	case CFalseKnight::ATTACK:
		CCameraMgr::Get_Instance()->ShakingStart(30.f);
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			WaveAttack();
			m_pFrameKey = L"attackend2";
			m_eCurState = ATTACKEND;
			m_tempo++;
			
		}
		break;
	case CFalseKnight::ATTACK2:
		CCameraMgr::Get_Instance()->ShakingStart(30.f);
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_attack2_voice.wav", BOSS_VOICE2, B_Sound);
			m_OneSound = false;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			JumpAttack();
			m_pFrameKey = L"attackend2";
			m_eCurState = ATTACKEND;
			m_OneSound = true;
			m_tempo++;
			
		}

		break;
	case CFalseKnight::ATTACKEND:
		
		if (m_StunCheck) {
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
				CCameraMgr::Get_Instance()->ShakingEnd();
				if (m_TurnDirection == TURNLEFT) {
					m_TurnDirection = TURNRIGHT;
				}
				else if (m_TurnDirection == TURNRIGHT) {
					m_TurnDirection = TURNLEFT;
				}
				/*m_pFrameKey = L"Boss1_idle";
				m_eCurState = IDLE;*/
				CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK1);
				m_pFrameKey = L"Boss1_turn";
				m_eCurState = TURN;
				
			}
		}else{
			CCameraMgr::Get_Instance()->ShakingEnd();
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"Boss1_idle";
			m_eCurState = IDLE;
		}
		}
		break;
	case CFalseKnight::ATTACKINIT:
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_attackinit_voice.wav", BOSS_VOICE, B_Sound);
			m_OneSound = false;
		}
		CCameraMgr::Get_Instance()->ShakingEnd();
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			if (m_StunCheck) {
				m_pFrameKey = L"attack";
				m_eCurState = ATTACK2;
			}
			else {
				m_pFrameKey = L"attack";
				m_eCurState = ATTACK;
			}
			m_OneSound = true;
		}
		break;
	case CFalseKnight::JUMP:
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_jump.wav", MONSTER_EFFECT, B_Sound*0.5f);
			m_OneSound = false;
		}
		if (m_StunCheck) {
			if (m_bJump) {
				m_tInfo.fX += m_Distance;
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical -= (0.0044f * G);
			}
			else {
				m_OneSound = true;
				m_pFrameKey = L"jumpend";
				m_eCurState = JUMPEND;
			}
		}
		break;
	case CFalseKnight::FRONTJUMP:
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_jump.wav", MONSTER_EFFECT, B_Sound*0.5f);
			m_OneSound = false;
			
		}
		if (m_Rand == 0) {
			if (m_bJump) {

				m_tInfo.fX += m_Distance;
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical -= (0.00044f * G);
			}
			else {
				CCameraMgr::Get_Instance()->ShakingStart(10.f);
				m_pFrameKey = L"jumpend";
				m_eCurState = JUMPEND;
				m_OneSound = true;

			}
			m_eJumpState = BACKJUMP;
		}
		else if (m_Rand == 1) {
			if (m_bJump) {
				m_tInfo.fX += m_Distance;
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical -= (0.00044f * G);


			}
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
				m_pFrameKey = L"jumpattackinit";
				m_eCurState = JUMPATTACKINIT;
				m_OneSound = true;

			}

			m_eJumpState = BACKJUMP;
		}
		break;
	case CFalseKnight::BACKJUMP:
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_jump.wav", MONSTER_EFFECT, B_Sound*0.5f);
			m_OneSound = false;
		}
		if (m_Rand == 1) {
			if (m_bJump) {
				m_tInfo.fX += m_Distance;
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical -= (0.0044f * G);
			}
			else {
				CCameraMgr::Get_Instance()->ShakingStart(10.f);
				m_pFrameKey = L"attackinit";
				m_eCurState = ATTACKINIT;
				m_OneSound = true;

			}
			m_eJumpState = FRONTJUMP;
		}
		else if (m_Rand == 0) {
			if (m_bJump) {
				m_tInfo.fX += m_Distance;
				m_tInfo.fY -= m_fSpeed_Vertical;
				m_fSpeed_Vertical -= (0.0044f * G);
			}
			else {
				m_pFrameKey = L"Boss1_run";
				m_eCurState = RUN;
				m_OneSound = true;
				if (m_TurnDirection == TURNLEFT) {
					m_Distance = -1 * m_fSpeed;
				}
				else if (m_TurnDirection == TURNRIGHT) {
					m_Distance = m_fSpeed;
				}
				m_bRun = true;

			}
			m_eJumpState = FRONTJUMP;
		}
		break;
	case CFalseKnight::JUMPATTACK1:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_jumpattack1_swing.wav", MONSTER_EFFECT, B_Sound * 0.5f);
			JumpAttack();
			CCameraMgr::Get_Instance()->ShakingStart(30.f);
			if (m_tempo > 5) {
				m_pFrameKey = L"jumpattack2";
				m_eCurState = JUMPATTACK2;
				m_tempo = 0;
			}
			m_tempo++;
		}
		break;
	case CFalseKnight::JUMPATTACK2:	
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"jumpattack3";
			m_eCurState = JUMPATTACK3;
		}
		break;
	case CFalseKnight::JUMPATTACK3:
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			CCameraMgr::Get_Instance()->ShakingEnd();
			m_pFrameKey = L"Boss1_idle";
			m_eCurState = IDLE;
		}
		break;
	case CFalseKnight::JUMPATTACKINIT:
		CSoundMgr::Get_Instance()->PlaySound(L"B_jumpattackinit_voice.wav", BOSS_VOICE, B_Sound * 0.5f);
		if (m_bJump) {
			m_tInfo.fX += m_Distance;
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.00044f * G);
		}
		else {
			m_pFrameKey = L"jumpattack1";
			m_eCurState = JUMPATTACK1;
		}
		break;
	case CFalseKnight::JUMPEND:
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_jumpend.wav", MONSTER_EFFECT2, B_Sound*0.5f);
			m_OneSound = false;
			
		}
		if (m_StunCheck) {
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
				CCameraMgr::Get_Instance()->ShakingEnd();
				m_pFrameKey = L"attackinit";
				m_eCurState = ATTACKINIT;
				m_OneSound = true;
			}
		}
		else {
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
				CCameraMgr::Get_Instance()->ShakingEnd();
				m_pFrameKey = L"Boss1_idle";
				m_eCurState = IDLE;
				m_OneSound = true;
			}
		}
		break;
	case CFalseKnight::JUMPINIT:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {

			m_fSpeed_Vertical = 15.f;
			m_Rand = rand() % 2;
			m_Distance = 0.f;

			if (m_StunCheck) {
				m_pFrameKey = L"Boss1_jump";
				m_eCurState = JUMP;
				if (m_TurnDirection == TURNLEFT) {
					m_Distance = -1 * (Distance());
				}
				else if (m_TurnDirection == TURNRIGHT) {
					m_Distance = Distance();
				}
			}
			else {
				m_pFrameKey = L"Boss1_jump";

				if (m_eJumpState == FRONTJUMP) {
					m_eCurState = FRONTJUMP;
					if (m_TurnDirection == TURNLEFT) {
						m_Distance = -1 * (Distance());
					}
					else if (m_TurnDirection == TURNRIGHT) {
						m_Distance = Distance();
					}
				}
				else if (m_eJumpState == BACKJUMP) {
					m_eCurState = BACKJUMP;
					if (m_TurnDirection == TURNLEFT) {
						m_Distance = 10.f;//(Distance());
					}
					else if (m_TurnDirection == TURNRIGHT) {
						m_Distance = -10.f;//-1 * (Distance());
					}
				}
			}
			
			m_bJump = true;
		}
		break;
	case CFalseKnight::STUNOPEN:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			/*m_pFrameKey = L"stunrollend";
			m_eCurState = STUNROLLEND;*/
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd - 2;
			/*if (m_StunHit) {
				m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			}*/
			if (m_HP < 0) {
				if (m_life <= 0) {
					/*m_pFrameKey = L"Boss1_death";
					m_eCurState = DEATH;*/
					if (!m_StunEffect) {
						m_StunEffect = CObjFactory<CMDeathEffet>::Create(m_tInfo.fX, m_tInfo.fY);
						m_StunEffect->Set_TurnDir(m_TurnDirection);
						dynamic_cast<CMDeathEffet*>(m_StunEffect)->Set_MonsterType(1);
						m_StunEffect->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_StunEffect);
						//CCameraMgr::Get_Instance()->ShakingStart(1.f);
					}
					Death();
					Set_Dead();
					CCameraMgr::Get_Instance()->ShakingEnd();
				}
				else {
					m_pFrameKey = L"stunclose";
					m_eCurState = STUNCLOSE;
					m_HP = 10;
					m_life--;
					m_StunCheck = true;
				}
				
			}
		}
		break;
	case CFalseKnight::STUNCLOSE:
		//m_CollisionObjID = OBJID_END;
		if (m_StunCheck) {
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
				m_pFrameKey = L"jumpinit";
				m_eCurState = JUMPINIT;
			}
		}
		else {
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
				m_pFrameKey = L"Boss1_idle";
				m_eCurState = IDLE;
			}
		}
		break;
	case CFalseKnight::STUNROLL:
		CCameraMgr::Get_Instance()->ShakingEnd();
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"B_roll.wav", MONSTER_EFFECT, B_Sound * 0.5f);
			m_OneSound = false;
		}
		if (m_bJump) {
			if (m_eDir == RIGHT) {
				m_tInfo.fX -= 3.f;
			}
			else if (m_eDir == LEFT) {
				m_tInfo.fX += 3.f;
			}
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.0044f * G);
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_pFrameKey = L"stunrollend";
			m_eCurState = STUNROLLEND;
			m_OneSound = true;
			
			
		}
		break;
	case CFalseKnight::STUNROLLEND:
		
		if (m_bJump) {
			if (m_eDir == RIGHT) {
				m_tInfo.fX -= 3.f;
			}
			else if (m_eDir == LEFT) {
				m_tInfo.fX += 3.f;
			}
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.0044f * G);
		}
		else {
			if (m_OneSound) {
				CSoundMgr::Get_Instance()->PlaySound(L"B_rollend.wav", MONSTER_EFFECT2, B_Sound * 0.5f);
				m_OneSound = false;
			}
		}
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_OneSound = true;
			m_pFrameKey = L"stunopen";
			m_eCurState = STUNOPEN;
		}
		break;
	case CFalseKnight::DEATH:
		/*if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}*/
		break;
	case CFalseKnight::DEATH2:
		break;
	default:
		break;
	}
}

void CFalseKnight::Motion_Change()
{
	if (m_ePreState != m_eCurState) {
		switch (m_eCurState)
		{
		case CFalseKnight::IDLE:
			//Set_Size(620.6f, 390.f);
			FramSave(0, 4, m_TurnDirection, 200);
			break;
		case CFalseKnight::READY:
			break;
		case CFalseKnight::TURN:
			//Set_Size(548.f, 391.f);
			FramSave(0, 1, m_TurnDirection, 100);
			break;
		case CFalseKnight::RUN:
			//Set_Size(548.f, 391.f);
			FramSave(0, 6, m_TurnDirection, 200);
			break;
		case CFalseKnight::HIT:
			//Set_Size(548.f, 391.f);
			FramSave(0, 8, m_TurnDirection, 600);
			break;
		case CFalseKnight::ATTACK:
			//Set_Size(692.33f, 594.f);
			FramSave(0, 2, m_TurnDirection, 100);
			break;
		case CFalseKnight::ATTACKEND:
			//Set_Size(657.f, 578.f);
			FramSave(0, 4, m_TurnDirection, 100);
			break;
		case CFalseKnight::ATTACKINIT:
			//Set_Size(582.f, 402.f);
			FramSave(0, 5, m_TurnDirection, 200);
			break;
		case CFalseKnight::JUMP:
			//Set_Size(603.5f, 339.f);
			FramSave(0, 3, m_TurnDirection, 100);
		case CFalseKnight::FRONTJUMP:
			//Set_Size(603.5f, 339.f);
			FramSave(0, 3, m_TurnDirection, 100);
		case CFalseKnight::BACKJUMP:
			//Set_Size(603.5f, 339.f);
			FramSave(0, 3, m_TurnDirection, 100);
			break;
		case CFalseKnight::JUMPATTACK1:
			//Set_Size(841.5f, 624.f);
			FramSave(0, 1, m_TurnDirection, 300);
			break;
		case CFalseKnight::JUMPATTACK2:
			//Set_Size(488.5f, 592.f);
			FramSave(0, 1, m_TurnDirection, 300);
			break;
		case CFalseKnight::JUMPATTACK3:
			//Set_Size(618.f, 398.f);
			FramSave(0, 1, m_TurnDirection, 200);
			break;
		case CFalseKnight::JUMPATTACKINIT:
			//Set_Size(713.f, 424.f);
			FramSave(0, 4, m_TurnDirection, 200);
			break;
		case CFalseKnight::JUMPEND:
			//Set_Size(609.66f, 383.f);
			FramSave(0, 2, m_TurnDirection, 80);
			break;
		case CFalseKnight::JUMPINIT:
			//Set_Size(609.33f, 383.f);
			FramSave(0, 2, m_TurnDirection, 100);
			break;
		case CFalseKnight::STUNOPEN:
			//Set_Size(396.f, 457.f);
			FramSave(0, 4, m_TurnDirection, 100);
			break;
		case CFalseKnight::STUNCLOSE:
			//Set_Size(396.f, 457.f);
			FramSave(0, 7, m_TurnDirection, 200);
			break;
		case CFalseKnight::STUNROLL:
			//Set_Size(764.8f, 518.f);
			FramSave(0, 4, m_TurnDirection, 100);
			break;
		case CFalseKnight::STUNROLLEND:
		//	Set_Size(418.75f, 468.f);
			FramSave(0, 3, m_TurnDirection, 100);
			break;
		case CFalseKnight::DEATH:
			//Set_Size(270.f, 234.f);
			FramSave(0, 9, m_TurnDirection, 100);
			break;
		case CFalseKnight::DEATH2:
			//Set_Size(273.f, 196.f);
			FramSave(0, 3, m_TurnDirection, 100);
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CFalseKnight::Pattern()
{
	if (m_PatternCheck == PATTERN1) {
		

	}else if (m_PatternCheck == PATTERN2) {
		
	}
	else if (m_PatternCheck == PATTERN3) {

	}
}

float CFalseKnight::Distance()
{
	float fx = m_pTarget->Get_Info()->fX;
	//float fy = m_pTarget->Get_Info()->fY;
	return (float)(abs(fx - m_tInfo.fX))*0.01f;
}

void CFalseKnight::JumpAttack()
{
	/*if (!m_BossAttack) {
		m_BossAttack = new CBossAttack;
		m_BossAttack->SetOwner(this);
		dynamic_cast<CBossAttack*>(m_BossAttack)->Set_BossState(m_eCurState);
		dynamic_cast<CBossAttack*>(m_BossAttack)->Set_TurnDir(m_TurnDirection);
		m_BossAttack->Initialize();
		CObjMgr::Get_Instance()->Add_Object(MBULLET, m_BossAttack);
	}*/
	CObj* m_BossAttack = new CBossAttack;
	m_BossAttack->SetOwner(this);
	dynamic_cast<CBossAttack*>(m_BossAttack)->Set_BossState(m_eCurState);
	dynamic_cast<CBossAttack*>(m_BossAttack)->Set_TurnDir(m_TurnDirection);
	m_BossAttack->Initialize();
	CObjMgr::Get_Instance()->Add_Object(MMELEE, m_BossAttack);
	
}

void CFalseKnight::WaveAttack()
{
	if (!m_BossWave) {
		m_BossWave = new CWaveAttack;
		m_BossWave->SetOwner(this);
		dynamic_cast<CWaveAttack*>(m_BossWave)->Set_BossState(m_eCurState);
		dynamic_cast<CWaveAttack*>(m_BossWave)->Set_TurnDir(m_TurnDirection);
		m_BossWave->Initialize();
		CObjMgr::Get_Instance()->Add_Object(MBULLET2, m_BossWave);
	}
}

void CFalseKnight::Death()
{

	CObj* m_Death2 = new CDeath2;
	m_Death2->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CDeath2*>(m_Death2)->Set_TurnDir(m_TurnDirection);
	m_Death2->Initialize();
	CObjMgr::Get_Instance()->Add_Object(STRUCT, m_Death2);

	//CObj* m_Death = CObjFactory<CDeath>::Create(m_tInfo.fX, m_tInfo.fY);
	CObj* m_Death = new CDeath;
	m_Death->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CDeath*>(m_Death)->Set_TurnDir(m_TurnDirection);
	m_Death->Initialize();
	CObjMgr::Get_Instance()->Add_Object(STRUCT, m_Death);

	

}

void CFalseKnight::Barrel()
{
	if (m_eCurState == ATTACK2) {
		if (m_Barrelvec.empty()) {
			for (int i = 0; i < 10; i++) {
				int irand = rand() % 43 + 40;
				if (irand > 62) {
					irand -= 20;
				}
				irand=irand * 100;
				m_Barrelvec.push_back( CObjFactory<CBarrel>::Create((float)irand, 200.f));
				CObjMgr::Get_Instance()->Add_Object(MBULLET, m_Barrelvec.back());
			}
		}
	}
	else if (m_eCurState == JUMPATTACK1) {
		if (m_Barrelvec.empty()) {
			for (int i = 0; i < 4; i++) {
				int irand = rand() % 43 + 40;
				if (irand > 62) {
					irand -= 20;
				}
				irand = irand * 100;
				m_Barrelvec.push_back(CObjFactory<CBarrel>::Create((float)irand, 200.f));
				CObjMgr::Get_Instance()->Add_Object(MBULLET, m_Barrelvec.back());
			}
		}
	}

	if (!m_Barrelvec.empty()) {
		if (m_BarrelTempo > 5) {
			for (int i = 0; i < m_Barrelvec.size(); i++) {
				if (!dynamic_cast<CBarrel*>(m_Barrelvec[i])->Get_Move()) {
					dynamic_cast<CBarrel*>(m_Barrelvec[i])->Set_Move();
					break;
				}
			}
			m_BarrelTempo = 0;
		}
		m_BarrelTempo++;

		for (int i = 0; i < m_Barrelvec.size(); i++) {
			if (m_Barrelvec[i]->Get_Dead()) {
				m_Barrelvec.erase(m_Barrelvec.begin() + i);
			}
		}
	}
}

void CFalseKnight::Collision()
{
	if (m_CollisionCheck) {
		if (m_eCurState == RUN) {
			if (m_CollisionObjID == PWALL && !m_bEscapeWall) {
				m_bRun = false;
				m_bEscapeWall = true;
				
			}
		}

		if ((m_CollisionObjID == PBULLET|| m_CollisionObjID == PMELEE) &&m_bHitCheck) {
			if(m_eCurState==STUNOPEN){
				m_HP-= m_HitDamage;
				CSoundMgr::Get_Instance()->PlaySound(L"B_hit.wav", BOSS_HIT, B_Sound * 0.5f);
			}
			else {
				if (m_Defense <= 0) {
					CSoundMgr::Get_Instance()->PlaySound(L"B_armour_final.wav", BOSS_HIT, B_Sound*3.f);
				}
				else {
					CSoundMgr::Get_Instance()->PlaySound(L"B_armour_hit.wav", BOSS_HIT, B_Sound);
				}
				m_Defense-=m_HitDamage;
				
				
			}
			m_bHitCheck = false;
			//m_StunHit = true;
		}
		/*else if (m_CollisionObjID == PMELEE && !m_bHitCheck) {
			if (m_eCurState == STUNOPEN) {
				m_HP--;
			}
			else {
				m_Defense--;
			}
			m_bHitCheck = true;
		}*/
	}
}
