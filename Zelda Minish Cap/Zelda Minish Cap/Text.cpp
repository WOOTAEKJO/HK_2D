#include "Text.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "CameraMgr.h"

CText::CText()
{
}

CText::~CText()
{
	Release();
}

void CText::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_ObjType = STRUCT;

	Set_Size(301.f, 167.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/text1.bmp", L"text");

	m_pFrameKey = L"text";
}

int CText::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CObj::Update_Rect();
	return 0;
}

void CText::Late_Update()
{
}

void CText::Render(HDC hDC)
{
	INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

	CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);

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
	DeleteObject(myBrush);*/

	//const TCHAR* str = TEXT("∫∏Ω∫ ¡ª ¿‚æ∆¡‡");

	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("±º∏≤"));
	HFONT OldFont = (HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, 1);
	TextOutW(hDC, LONG(tRenderPos.fX - m_tInfo.fCX*0.5f+ m_tInfo.fCX * 0.5f-70.f),
		LONG(tRenderPos.fY - m_tInfo.fCY * 0.5f+ m_tInfo.fCY * 0.5f) - 30.f, M_Text, lstrlen(M_Text));

	SelectObject(hDC, OldFont);
	DeleteObject(hFont);
}

void CText::Release()
{
}

void CText::Collision()
{
}
