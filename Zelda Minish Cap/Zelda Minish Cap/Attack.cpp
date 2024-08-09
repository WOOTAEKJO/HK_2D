#include "Attack.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "CameraMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "AttackEffect.h"

float g_fSound_a = 1.f;

CAttack::CAttack():m_PlayerState(STATE_END), m_bStart(true), m_iChange(0), m_AttackSuccess(0), m_bSuccess(true),
m_OneCheck(true)
{
}

CAttack::~CAttack()
{
	Release();
}

void CAttack::Initialize()
{
	m_eRender = EFFECT;
	m_Owner = CObjMgr::Get_Instance()->Get_Player();

	m_ObjType = PMELEE;

	m_Damage = 1;

	//m_tInfo = { 0.f,0.f,256.f,128.f };

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect1/slash.bmp", L"slash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect1/slash2.bmp", L"slash2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect1/upslash.bmp", L"upslash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect1/downslash.bmp", L"downslash");*/

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/P_att.bmp", L"att_eff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/P_down_att.bmp", L"down_att_eff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/P_up_att.bmp", L"top_att_eff");


	/*CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_armour.wav", g_fSound_a);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_non.wav", g_fSound_a);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_parring.wav", g_fSound_a);*/

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/slash.bmp", L"slash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/slash2.bmp", L"slash2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/upslash.bmp", L"upslash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/effect/downslash.bmp", L"downslash");*/
	
	/*CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_armour.wav", g_fSound_a);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_non.wav", g_fSound_a);
	CSoundMgr::Get_Instance()->PlayBGM(L"P_sword_parring.wav", g_fSound_a);*/

}

int CAttack::Update()
{
 	if (m_bDead) {
		//Get_CollisionObjID();
		//CSoundMgr::Get_Instance()->StopSound(PLAYER_SWORD);
		return OBJ_DEAD;
	}

	if (m_TurnDirection == 0) {
		m_iChange = 1;
	}
	else {
		m_iChange = 0;
	}

	Collision();

	if (m_PlayerState == SLASH) {
		if (m_TurnDirection == 0) {
			m_tInfo.fCX = 256.f;
			m_tInfo.fCY = 128.f;
			//Set_Size(151.f, 129.f);
			m_tInfo.fX = m_Owner->Get_Info()->fX + m_Owner->Get_Info()->fCX * 0.5f*0.5f + m_tInfo.fCX * 0.5f* 0.5f;
			m_tInfo.fY = m_Owner->Get_Info()->fY;
			m_fColC.x = m_tInfo.fCX * 0.5f;
			m_fColC.y = m_tInfo.fCY;
		}
		else if (m_TurnDirection == 1) {
			m_tInfo.fCX = 256.f;
			m_tInfo.fCY = 128.f;
			//Set_Size(151.f, 129.f);
			m_tInfo.fX = m_Owner->Get_Info()->fX - m_Owner->Get_Info()->fCX * 0.5f * 0.5f - m_tInfo.fCX * 0.5f* 0.5f;
			m_tInfo.fY = m_Owner->Get_Info()->fY;
			m_fColC.x = m_tInfo.fCX * 0.5f;
			m_fColC.y = m_tInfo.fCY;
		}
	}
	//else if (m_PlayerState == SLASH2) {

	//	if (m_TurnDirection == 0) {
	//		m_tInfo.fCX = 256.f;
	//		m_tInfo.fCY = 128.f;
	//		//Set_Size(180.f,83.f);
	//		m_tInfo.fX = m_Owner->Get_Info()->fX - m_Owner->Get_Info()->fCX * 0.5f * 0.5f - m_tInfo.fCX * 0.5f * 0.5f;
	//		m_tInfo.fY = m_Owner->Get_Info()->fY;
	//		m_fColC.x = m_tInfo.fCX * 0.5f;
	//		m_fColC.y = m_tInfo.fCY;
	//	}
	//	else if (m_TurnDirection == 1) {
	//		m_tInfo.fCX = 256.f;
	//		m_tInfo.fCY = 128.f;
	//		//Set_Size(180.f,83.f);
	//		m_tInfo.fX = m_Owner->Get_Info()->fX + m_Owner->Get_Info()->fCX * 0.5f * 0.5f + m_tInfo.fCX * 0.5f * 0.5f;
	//		m_tInfo.fY = m_Owner->Get_Info()->fY;
	//		m_fColC.x = m_tInfo.fCX * 0.5f;
	//		m_fColC.y = m_tInfo.fCY;
	//	}
	//}
	else if (m_PlayerState == UPSLASH) {
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 256.f;
		//Set_Size(129.f, 151.f);
		m_tInfo.fX = m_Owner->Get_Info()->fX;
		m_tInfo.fY= m_Owner->Get_Info()->fY - m_Owner->Get_Info()->fCY * 0.5f*0.5f - m_tInfo.fCY * 0.5f * 0.5f;
		m_fColC.x = m_tInfo.fCX * 0.5f;
		m_fColC.y = m_tInfo.fCY* 0.25f;

	}
	else if (m_PlayerState == DOWNSLASH) {
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 256.f;
		//Set_Size(129.f, 151.f);
		m_tInfo.fX = m_Owner->Get_Info()->fX;
		m_tInfo.fY = m_Owner->Get_Info()->fY + m_Owner->Get_Info()->fCY * 0.5f * 0.5f + m_tInfo.fCY * 0.5f * 0.5f;
		m_fColC.x = m_tInfo.fCX * 0.5f;
		m_fColC.y = m_tInfo.fCY * 0.25f;
	}

	if (m_PlayerState == SLASH && m_bStart) {

		m_pFrameKey = L"att_eff";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = m_iChange;
		m_tFrame.dwSpeed = 80;
		m_tFrame.dwTime = GetTickCount64();
		m_bStart = false;
	}
	else if (m_PlayerState == UPSLASH && m_bStart) {
		m_pFrameKey = L"top_att_eff";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = m_iChange;
		m_tFrame.dwSpeed = 80;
		m_tFrame.dwTime = GetTickCount64();
		m_bStart = false;
	}
	else if (m_PlayerState == DOWNSLASH && m_bStart) {
		m_pFrameKey = L"down_att_eff";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = m_iChange;
		m_tFrame.dwSpeed = 80;
		m_tFrame.dwTime = GetTickCount64();
		m_bStart = false;
	}

	
	
	//if (m_PlayerState == SLASH) {

	//	if (m_tFrame.iFrameStart == 1) {
	//		if (m_PlayerState == SLASH2) {
	//			m_pFrameKey = L"slash2";
	//			m_tFrame.iFrameStart = 0;
	//			m_tFrame.iFrameEnd = 1;
	//			m_tFrame.iMotion = m_TurnDirection;
	//			m_tFrame.dwSpeed = 40;
	//			m_tFrame.dwTime = GetTickCount64();
	//			m_bStart = false;
	//		}
	//	}
	//}
	//else {
	//	if (m_tFrame.iFrameStart == 1) {
	//		/*if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
	//			Set_Dead();
	//		}*/
	//		Set_Dead();
	//	}
	//}
	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == 1) {
		/*if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
			Set_Dead();
		}*/
		Set_Dead();
	}
	CObj::Update_Rect();
	return 0;
}

void CAttack::Late_Update()
{
	if (!m_bSuccess) {
		
	}
}

void CAttack::Render(HDC hDC)
{
	//INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	//GdiTransparentBlt(hDC,
	//	(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
	//	(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f),
	//	(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
	//	(int)m_tInfo.fCY,
	//	hMemDC,			// 비트맵 이미지를 담고 있는 DC
	//	m_tFrame.iMotion * (int)m_tInfo.fCX, // 비트맵을 출력할 시작 X,Y좌표
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
	//	(int)m_tInfo.fCY,
	//	RGB(0, 0, 0)); // 제거하고자 하는 색상


	//HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
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

	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);
	CObj::Camera_Col_Render_UD(hDC, 7, 7, 7);

	/*HPEN hGreenPen = CreatePen(PS_DOT, 2, RGB(0, 255, 255));
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

void CAttack::Release()
{
}

void CAttack::Collision()
{
	if (m_OneCheck) {
		if (m_CollisionCheck) {
				if (m_CollisionObjID == MONSTER && m_bSuccess) {
				m_AttackSuccess++;
				m_bSuccess = false;
				CObj* effect = CObjFactory<CAttackEffect>::Create(m_tInfo.fX, m_tInfo.fY);
				effect->Set_TurnDir(m_TurnDirection);
				effect->Initialize();
				CObjMgr::Get_Instance()->Add_Object(PEFFECT, effect);
				m_OneCheck = false;

				}
				else if (m_CollisionObjID == PWALL) {
					//(!m_Effect) {
					float fx = 0.f;
					if (m_TurnDirection == TURNLEFT) {
						fx = -m_fColC.x;
					}
					else {
						fx = m_fColC.x;
					}
						m_Effect = CObjFactory<CAttackEffect>::Create(m_tInfo.fX+ fx *0.5f, m_tInfo.fY);
						/*if (m_TurnDirection == TURNLEFT) {
							m_Effect->Set_TurnDir(TURNLEFT);
						}
						else {
							m_Effect->Set_TurnDir(TURNRIGHT);
						}*/
						m_Effect->Set_TurnDir(m_TurnDirection);
						m_Effect->Initialize();
						CObjMgr::Get_Instance()->Add_Object(PEFFECT, m_Effect);
						m_OneCheck = false;
					//}
				}
			}


		}
		
		
	
}
