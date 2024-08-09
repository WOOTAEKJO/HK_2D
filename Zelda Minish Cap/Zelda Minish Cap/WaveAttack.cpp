#include "WaveAttack.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

float B_waveSound = 1.f;

CWaveAttack::CWaveAttack() :m_BossState(STATE_END), m_Distance(0.f), m_Start(true)
{
}

CWaveAttack::~CWaveAttack()
{
	Release();
}

void CWaveAttack::Initialize()
{
	m_eRender = EFFECT;

	m_ObjType = MBULLET2;

	m_tInfo.fCX = 375.625f;
	m_tInfo.fCY = 434.f;

	m_fColC = { m_tInfo.fCX*0.25f,m_tInfo.fCY*0.05f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/effect/wave2.bmp", L"wave");

	if (m_TurnDirection == TURNLEFT) {
		m_tInfo.fX = m_Owner->Get_Info()->fX - m_Owner->Get_Info()->fCX * 0.25f;
		m_tInfo.fY = m_Owner->Get_Info()->fY + m_Owner->Get_Info()->fCY * 0.002f - 50.f;
		m_Distance = -14.f;
	}
	else if (m_TurnDirection == TURNRIGHT) {
		m_tInfo.fX = m_Owner->Get_Info()->fX + m_Owner->Get_Info()->fCX * 0.25f;
		m_tInfo.fY = m_Owner->Get_Info()->fY + m_Owner->Get_Info()->fCY * 0.002f - 50.f;
		m_Distance = 14.f;
	}

	m_pFrameKey = L"wave";
	FramSave(0, 15, m_TurnDirection, 50);
}

int CWaveAttack::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_Start) {
		CSoundMgr::Get_Instance()->PlaySound(L"B_attack.wav", BOSS_ATTACK2, B_waveSound);
		m_Start = false;
	}

	if (m_tInfo.fCX-100.f >= m_fColC.x) {
		m_fColC.x += 3.f;
	}
	if (m_tInfo.fCY-100.f>= m_fColC.y) {
		m_fColC.y += 3.f;
	}

	m_tInfo.fX += m_Distance;

	CObj::Move_Frame();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd) {
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd - 2;
	}
	//CObj::Update_Rect();
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	/*m_tCollider.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f)*0.25f);
	m_tCollider.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tCollider.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f) * 0.25f);
	m_tCollider.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));*/

	m_tCollider.left = LONG(m_tInfo.fX - (m_fColC.x * 0.15f));
	m_tCollider.top = LONG(m_tInfo.fY - (m_fColC.y * 0.15f));
	m_tCollider.right = LONG(m_tInfo.fX + (m_fColC.x * 0.15f));
	m_tCollider.bottom = LONG(m_tInfo.fY + (m_fColC.y * 0.15f));

	Collision();
	return 0;
}

void CWaveAttack::Late_Update()
{
	
}

void CWaveAttack::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	//CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	if (m_TurnDirection == TURNRIGHT)
	{
		GdiTransparentBlt(hDC,
			(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
			(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f),
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)(m_tInfo.fCX),		// 출력할 비트맵의 가로, 세로 사이즈
			(int)(m_tInfo.fCY),
			RGB(7, 7, 7)); // 제거하고자 하는 색상
	}
	else if (m_TurnDirection == TURNLEFT)
	{
		GdiTransparentBlt(hDC,
			(int)(tRenderPos.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
			(int)(tRenderPos.fY - m_tInfo.fCY * 0.5f),
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			(m_tFrame.iFrameEnd - m_tFrame.iFrameStart) * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)(m_tInfo.fCX ),		// 출력할 비트맵의 가로, 세로 사이즈
			(int)(m_tInfo.fCY ),
			RGB(7, 7, 7)); // 제거하고자 하는 색상
	}

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

void CWaveAttack::Release()
{
}

void CWaveAttack::Collision()
{
	if (m_CollisionCheck) {
		if (m_CollisionObjID == PWALL) {
			Set_Dead();
		}
	}
}
