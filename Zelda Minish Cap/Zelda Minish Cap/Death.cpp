#include "Death.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "SoundMgr.h"

float B_DeathSound = 1.f;

CDeath::CDeath():m_Start(true)
{
}

CDeath::~CDeath()
{
    Release();
}

void CDeath::Initialize()
{
    m_eRender = BACKGROUND;

    m_ObjType = STRUCT;

    m_tInfo.fCX = 1400.f;
    m_tInfo.fCY = 1400.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/death1.bmp", L"Boss1_death");

    m_pFrameKey = L"Boss1_death";
    FramSave(0, 2, m_TurnDirection, 200);

    m_tInfo.fY += m_tInfo.fCY * 0.25f- m_tInfo.fCY * 0.25f*0.5f+20.f;
}

int CDeath::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    if (m_Start) {
        CSoundMgr::Get_Instance()->PlaySound(L"B_death.wav", BOSS_VOICE, B_DeathSound);
        m_Start = false;
    }

    if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd) {
        CObj::Move_Frame();
    }

    CObj::Update_Rect();
    return 0;
}

void CDeath::Late_Update()
{
}

void CDeath::Render(HDC hDC)
{
    CObj::Camera_Col_Render_LR(hDC,7,7,7);
}

void CDeath::Release()
{
}

void CDeath::Collision()
{
}
