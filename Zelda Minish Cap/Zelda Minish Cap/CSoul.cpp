#include "CSoul.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CSoul::CSoul():m_Soul(0),m_eCurState(STATE_END),m_ePreState(STATE_END)
{

}

CSoul::~CSoul()
{
	Release();
}

void CSoul::Initialize()
{
	m_tInfo = { 155.f, 120.f, 111.f, 106.f };
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/SoulGage1.bmp", L"SoulGage");

	m_eRender = UI2;

	m_ObjType = PUI;

	m_pFrameKey = L"SoulGage";
	//FramSave(0, 0, 3, 100);
}

int CSoul::Update()
{
	//if (m_Soul == 20) {
	//	FramSave(0, 0, 3, 100);
	//	//175.f, 100.f
	//}
	//else if (m_Soul == 15) {
	//	//175.f, 140.f
	//	FramSave(0, 2, 2, 100);
	//}
	//else if (m_Soul == 10) {
	//	//175.f, 170.f
	//	FramSave(0, 2, 1, 100);
 //  	}
	//else if (m_Soul == 5) {
	//	//179.f, 200.f
	//	FramSave(0, 2, 0, 100);
	//}
	//else if (m_Soul == 0) {
	//	FramSave(1, 1, 3, 100);
	//}

	m_Soul = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Soul();

	Act();
	Montion_Change();
	

	CObj::Move_Frame();
	CObj::Update_Rect();
	return 0;
}

void CSoul::Late_Update()
{
	
}

void CSoul::Render(HDC hDC)
{

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	

	GdiTransparentBlt(hDC,
		(int)(m_tInfo.fX - m_tInfo.fCX * 0.5f), // 복사 받을 위치 X,Y 좌표
		(int)(m_tInfo.fY - m_tInfo.fCY * 0.5f),
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 0)); // 제거하고자 하는 색상
}

void CSoul::Release()
{
}

void CSoul::Collision()
{
}

void CSoul::Montion_Change()
{
	if (m_ePreState != m_eCurState) {
		switch (m_eCurState)
		{
		case CSoul::ZERO:
			FramSave(0, 0, 4, 300);
			break;
		case CSoul::FIVE:
			//179.f, 200.f
			FramSave(0, 2, 0, 300);
			break;
		case CSoul::TEN:
			//175.f, 170.f
			FramSave(0, 2, 1, 300);
			break;
		case CSoul::FIFTEEN:
			//175.f, 140.f
			FramSave(0, 2, 2, 300);
			break;
		case CSoul::TWENTY:
			FramSave(0, 0, 3, 300);
			//175.f, 100.f
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CSoul::Act()
{
	switch (m_Soul)
	{
	case 0:
		m_eCurState = ZERO;
		break;
	case 5:
		m_eCurState = FIVE;
		break;
	case 10:
		m_eCurState = TEN;
		break;
	case 15:
		m_eCurState = FIFTEEN;
		break;
	case 20:
		m_eCurState = TWENTY;
		break;
	default:
		break;
	}
}
