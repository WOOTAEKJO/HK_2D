#include "NPC2.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Text.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "SkillGetEffect.h"

float N2_Sound = 1.f;
CNPC2::CNPC2():m_Cool(GetTickCount64()), m_OneSound(true)
{
}

CNPC2::~CNPC2()
{
	Release();
}

void CNPC2::Initialize()
{
	Save_Text();

	m_eRender = GAMEOBJECT;
	m_ObjType = NPC;
	
	Set_Size(127.f, 191.f);

	m_fColC = { m_tInfo.fCX,m_tInfo.fCY };
	m_fATTRC = { m_tInfo.fCX * 3.f,m_tInfo.fCY };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/npc2_idle1.bmp", L"npc2_idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/npc2_talk1.bmp", L"npc2_talk");

	m_pFrameKey = L"npc2_idle";

	FramSave(0, 11, m_TurnDirection, 500);
}

int CNPC2::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Down('L')) {
		m_pFrameKey = L"npc2_talk";
		m_eCurState = TALK;
	}

	Collision();

	Jump();

	Act();
	Motion_Change();

	ATTR_Check();

	CObj::Move_Frame();
	CObj::Update_Rect();
	return 0;
}

void CNPC2::Late_Update()
{
	if (m_bTextBox) {
		if (m_bTextBox->Get_Dead())
			m_bTextBox = nullptr;
	}
}

void CNPC2::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	CObj::Camera_Col_Render_LR(hDC,7,7,7);

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
	TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f), LONG(tRenderPos.fY - m_fColC.y * 0.5f) - 30.f, _text1, lstrlen(_text1));*/

}

void CNPC2::Release()
{
}

void CNPC2::Collision()
{
	if (m_CollisionCheck) {

	}
}

void CNPC2::Act()
{
	switch (m_eCurState)
	{
	case CNPC2::IDLE:
		break;
	case CNPC2::TALK:
		if (m_OneSound) {
			CSoundMgr::Get_Instance()->PlaySound(L"N2_talk2.wav", NPC_SOUND, N2_Sound * 0.5f);
			//m_OneSound = false;
		}
		if (m_bTalk) {
			
			if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE2) {
				if (!(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
					->Get_DoubleJumpUnLockl())) {

					if (m_nextTalk == 0) {
						Next_Text(m_nextTalk, SC_STAGE2);
						m_nextTalk = 1;
					}
					else if (CObjMgr::Get_Instance()->Get_ObjList()[MONSTER].empty()) {
						m_nextTalk = 2;
						dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
							->Set_DoubleJumpUnLockl();
						CObj* Skill = new CSkillGetEffect;
						//Skill->Set_Pos(m_tInfo.fX, m_tInfo.fY);
						dynamic_cast<CSkillGetEffect*>(Skill)->Set_SkillNum(0); // 0이 더블점프, 1이 벽, 2가 대쉬
						Skill->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, Skill);
					}
					Next_Text(m_nextTalk, SC_STAGE2);
				}
				else {

					m_nextTalk = 3;
					Next_Text(m_nextTalk, SC_STAGE2);
				}
			}
			else if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3) {
				
				if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
					->Get_ALLUnLock()) {
					
					if (m_nextTalk != 3) {
						m_nextTalk = 2;
						Next_Text(m_nextTalk, SC_STAGE3);
						m_nextTalk = 3;
					}
					else {
						Next_Text(m_nextTalk, SC_STAGE3);
					}
				}
				else {
					if (m_nextTalk == 0) {
						Next_Text(m_nextTalk, SC_STAGE3);
						m_nextTalk = 1;
					}
					else {
						Next_Text(m_nextTalk, SC_STAGE3);
					}
				}
				
				
				
			}
			else if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE6) {
				if (!(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
					->Get_DashUnLock())) {
					if (!(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
						->Get_WallUnLock())) {
						Next_Text(0, SC_STAGE6);
						
					}
					else {
						if (m_nextTalk == 0) {
							m_nextTalk = 1;
						}
						if (CObjMgr::Get_Instance()->Get_ObjList()[STRUCT].empty()) {
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
								->Set_DashUnLock();
							CObj* Skill = new CSkillGetEffect;
							//Skill->Set_Pos(m_tInfo.fX, m_tInfo.fY);
							dynamic_cast<CSkillGetEffect*>(Skill)->Set_SkillNum(2); // 0이 더블점프, 1이 벽, 2가 대쉬
							Skill->Initialize();
							CObjMgr::Get_Instance()->Add_Object(PEFFECT, Skill);
							m_nextTalk = 2;
						}

						Next_Text(m_nextTalk, SC_STAGE6);
					}
				}
				else {
					Next_Text(3, SC_STAGE6);
				}
			}
			else if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE5) {
				if (!(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
					->Get_WallUnLock())) {

					if (m_nextTalk == 0) {
						m_nextTalk = 1;
					}
					if (CObjMgr::Get_Instance()->Get_ObjList()[MONSTER].empty()) {
						dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())
							->Set_WallUnLock();
						CObj* Skill = new CSkillGetEffect;
						//Skill->Set_Pos(m_tInfo.fX, m_tInfo.fY);
						dynamic_cast<CSkillGetEffect*>(Skill)->Set_SkillNum(1); // 0이 더블점프, 1이 벽, 2가 대쉬
						Skill->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, Skill);
						m_nextTalk = 2;
					}
					Next_Text(m_nextTalk, SC_STAGE5);

				}
				else {
					Next_Text(3, SC_STAGE5);
				}
			}

		}
		else {
			m_pFrameKey = L"npc2_idle";
			m_eCurState = IDLE;
			m_OneSound = true;
			if (m_bTextBox) {
				m_bTextBox->Set_Dead();
			}
		}
		break;
	default:
		break;
	}
}

void CNPC2::Motion_Change()
{
	if (m_ePreState != m_eCurState) {
		switch (m_eCurState)
		{
		case CNPC2::IDLE:
			FramSave(0, 11, m_TurnDirection, 1000);
			break;
		case CNPC2::TALK:
			FramSave(0, 4, m_TurnDirection, 200);
			break;
		default:
			break;
		}
		CSoundMgr::Get_Instance()->StopSound(NPC_SOUND);
		m_ePreState = m_eCurState;
	}
}

void CNPC2::ATTR_Check()
{
	if (m_ATTR_Check) {
		if (m_ATTR_ObjID == PLAYER) {
			m_bTalk = true;

		}
	}
	else {
		m_bTalk = false;
	}
}

void CNPC2::Next_Text(int _NextNum, SCENEID _StageID)
{
	if (_StageID == SC_STAGE2) {
		if (_NextNum == 0) {
			Create_Text(2);
		}
		else if (_NextNum == 1) {
			Create_Text(5);
		}
		else if (_NextNum == 2) {
			Create_Text(3);
		}
		else if (_NextNum == 3) {
			Create_Text(6);
		}
	}
	else if (_StageID == SC_STAGE3) {
		if (_NextNum == 0) {
			Create_Text(7);
		}
		else if (_NextNum == 1) {
			Create_Text(8);
		}
		else if (_NextNum == 2) {
			Create_Text(9);
		}
		else if (_NextNum == 3) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);
		}
	}
	else if (_StageID == SC_STAGE5) {
	if (_NextNum == 1) {
		Create_Text(2);
	}
	else if (_NextNum == 2) {
		Create_Text(3);
	}
	else if (_NextNum == 3) {
		Create_Text(6);
	}
	}
	else if (_StageID == SC_STAGE6) {
		if (_NextNum == 0) {
			Create_Text(10);
		}
		else if (_NextNum == 1) {
			Create_Text(11);
		}
		else if (_NextNum == 2) {
			Create_Text(3);
		}
		else if (_NextNum == 3) {
			Create_Text(6);
		}
	}
}
