#include "Barrel.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "SoundMgr.h"

float B_barrelSound = 1.f;

CBarrel::CBarrel() :m_bMove(false), m_bPlayerAttack(false)
{
}

CBarrel::~CBarrel()
{
    Release();
}

void CBarrel::Initialize()
{
    Set_Size(157.f, 143.f);

    m_eRender = GAMEOBJECT;

    m_ObjType = MBULLET;

    m_fColC = { m_tInfo.fCX * 0.5f,m_tInfo.fCY * 0.5f };

    m_fSpeed = 10.f;

    m_Damage = 2;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/motion/barrel.bmp", L"barrel");

    m_pFrameKey = L"barrel";

    FramSave(0, 7, 0, 200);
}

int CBarrel::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    if (m_bMove) {
        m_tInfo.fY += m_fSpeed;
        if (m_tInfo.fY > 2000.f) {
            CSoundMgr::Get_Instance()->PlaySound(L"B_barrel.wav", BSTRUCTSOUND, B_barrelSound);
            Set_Dead();
        }
    }   

    if (m_bPlayerAttack) {
        if (m_TurnDirection==TURNLEFT) {
            m_tInfo.fX -= m_fSpeed*1.5f;
        }
        else if (m_TurnDirection==TURNRIGHT) {
            m_tInfo.fX += m_fSpeed * 1.5f;
        }
        
        if (m_tInfo.fX <= 0.f || m_tInfo.fX >= 7000.f) {
            
            Set_Dead();
        }
    }

    Collision();

    CObj::Move_Frame();
    CObj::Update_Rect();
    return 0;
}

void CBarrel::Late_Update()
{
}

void CBarrel::Render(HDC hDC)
{

    CObj::Camera_Col_Render_LR(hDC,7,7,7 );

    INFO tRenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo);

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

void CBarrel::Release()
{
}

void CBarrel::Collision()
{
    if (m_CollisionCheck) {
        Set_Dead();
    }
}
