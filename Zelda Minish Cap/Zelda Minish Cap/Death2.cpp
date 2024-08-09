#include "Death2.h"
#include "BmpMgr.h"
#include "CameraMgr.h"

CDeath2::CDeath2():m_Distance(0.f)
{
}

CDeath2::~CDeath2()
{
    Release();
}

void CDeath2::Initialize()
{
    m_eRender = BACKGROUND2;

    m_ObjType = STRUCT;

    m_tInfo.fCX = 700.f;
    m_tInfo.fCY = 700.f;

    //m_fColC = { m_tInfo.fCX * 0.5f,m_tInfo.fCY * 0.5f };

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/death3.bmp", L"Boss1_death22");

    

    m_tInfo.fY += m_tInfo.fCY * 0.25f - m_tInfo.fCY * 0.25f * 0.25f + 45.f;
    m_tInfo.fX -= m_tInfo.fCX * 0.15f;

    if (m_TurnDirection == TURNLEFT) {
        
        m_Distance = -1.f;
    }
    else if (m_TurnDirection == TURNRIGHT) {
       
        m_Distance = 1.f;
    }

    m_pFrameKey = L"Boss1_death22";
    FramSave(0, 2, m_TurnDirection, 200);
}

int CDeath2::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd) {
        m_tInfo.fX += m_Distance;
        CObj::Move_Frame();
    }
    
    CObj::Update_Rect();

	return 0;
}

void CDeath2::Late_Update()
{
}

void CDeath2::Render(HDC hDC)
{
    CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CDeath2::Release()
{
}

void CDeath2::Collision()
{
}
