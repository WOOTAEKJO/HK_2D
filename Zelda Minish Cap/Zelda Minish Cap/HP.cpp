#include "HP.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CHP::CHP():m_bStart(true), m_AnimTurn(false)
{
}

CHP::~CHP()
{
    Release();
}

void CHP::Initialize()
{

	m_eRender = UI;
	m_ObjType = PUI;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HP_INTRO.bmp", L"HP_INTRO");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HP_DESTROY.bmp", L"HP_DESTROY");



	m_pFrameKey = L"HP_INTRO";
	FramSave(0, 5, 0, 200);

	m_Owner = CObjMgr::Get_Instance()->Get_Player();

}

int CHP::Update()
{
	
	if (m_AnimTurn) {
		if (m_eCurState == FULL) {
			m_pFrameKey = L"HP_DESTROY";
			m_eCurState = DESTORY;
		}
		else if (m_eCurState == DESTORY) {
			m_pFrameKey = L"HP_INTRO";
			m_eCurState =FULL;
		}
		m_AnimTurn = false;
	}// 애니메이션 교체

	Motion_Change();

	if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd) {
		CObj::Move_Frame();
	}

	//if (m_tFrame.iFrameStart == 0) {
	//	m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	//	//dynamic_cast<CPlayer*>(m_Owner)->Set_Heal(false);
	//}
	CObj::Update_Rect();
    return 0;
}

void CHP::Late_Update()
{
}

void CHP::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)(m_tInfo.fX - m_tInfo.fCX*0.5f), // 복사 받을 위치 X,Y 좌표
		(int)(m_tInfo.fY - m_tInfo.fCY * 0.5f),
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		m_tFrame.iMotion * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iFrameStart * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 0, 0)); // 제거하고자 하는 색상
}

void CHP::Release()
{
}

void CHP::Motion_Change()
{
	if ((m_ePreState != m_eCurState)) {
		switch (m_eCurState)
		{
		case CHP::FULL:
			FramSave(0, 5, 0, 200);
			break;
		case CHP::DESTORY:
			FramSave(0,6,0, 200);
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
		//m_bChangeM = false;
	}
}

void CHP::Collision()
{
}
