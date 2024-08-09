#include "Beetle.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CBeetle::CBeetle()
{
}

CBeetle::~CBeetle()
{
    Release();
}

void CBeetle::Initialize()
{
    Set_Size(118.f,384.f);

    m_eRender = GAMEOBJECT;
    m_ObjType = MONSTER;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/idle.bmp", L"beetle_idle");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/death.bmp", L"beetle_death");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/turn.bmp", L"beetle_turn");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/walk.bmp", L"beetle_walk");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/attackinit.bmp", L"beetle_attackinit");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/attack.bmp", L"beetle_attack");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/beetle/attackend.bmp", L"beetle_attackend");


    m_pFrameKey = L"beetle_idle";

    FramSave(0, 5, m_TurnDirection, 200);
}

int CBeetle::Update()
{
    return 0;
}

void CBeetle::Late_Update()
{
}

void CBeetle::Render(HDC hDC)
{
}

void CBeetle::Release()
{
}

void CBeetle::Collision()
{
}

void CBeetle::Act()
{
}

void CBeetle::Motion_Change()
{
}
