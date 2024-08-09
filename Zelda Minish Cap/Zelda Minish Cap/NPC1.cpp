#include "NPC1.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Text.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

float N1_Sound = 1.f;

CNPC1::CNPC1()
{
}

CNPC1::~CNPC1()
{
    Release();
}

void CNPC1::Initialize()
{
    Save_Text();

    Set_Size(113.f,160.f);

    m_fColC = { m_tInfo.fCX,m_tInfo.fCY };
    m_fATTRC = { m_tInfo.fCX * 3.f,m_tInfo.fCY };

    m_eRender = GAMEOBJECT;

    m_Owner = CObjMgr::Get_Instance()->Get_Player();

    m_ObjType = NPC;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/npc1_idle1.bmp", L"npc1_idle");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/npc1_talk1.bmp", L"npc1_talk");

    m_pFrameKey = L"npc1_idle";

    FramSave(0, 5, m_TurnDirection, 200);
}

int CNPC1::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    m_Owner = CObjMgr::Get_Instance()->Get_Player();

    if (CKeyMgr::Get_Instance()->Key_Down('L')) {
        m_pFrameKey = L"npc1_talk";
        m_eCurState = TALK;
    }


    Jump();

    Collision();

    Act();
    Motion_Change();

    ATTR_Check();

    CObj::Move_Frame();
    CObj::Update_Rect();
    return 0;
}

void CNPC1::Late_Update()
{
    if (m_Owner->Get_Info()->fX<m_tInfo.fX) {
        Set_TurnMotion(TURNLEFT);
    }
    else if(m_Owner->Get_Info()->fX > m_tInfo.fX){
        Set_TurnMotion(TURNRIGHT);
    }

    if (m_bTextBox) {
        if (m_bTextBox->Get_Dead())
            m_bTextBox = nullptr;
    }
    
}

void CNPC1::Render(HDC hDC)
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
    DeleteObject(myBrush);

    WCHAR _text1[100];
    _stprintf_s(_text1, L"hp: %dt\t atr: %d\t atro: %d", m_HP, m_ATTR_Check, m_ATTR_ObjID);
    TextOutW(hDC, LONG(tRenderPos.fX - m_fColC.x * 0.5f), LONG(tRenderPos.fY - m_fColC.y * 0.5f) - 30.f, _text1, lstrlen(_text1));*/

}

void CNPC1::Release()
{

}

void CNPC1::Collision()
{
    if (m_CollisionCheck) {
        
    }
}

void CNPC1::Act()
{
    switch (m_eCurState)
    {
    case CNPC1::IDLE:
        break;
    case CNPC1::TALK:
        CSoundMgr::Get_Instance()->PlaySound(L"N1_talk.wav", NPC_SOUND, N1_Sound*0.5f);
        if (m_bTalk) {

            if (CSceneMgr::Get_Instance()->Get_SavePreScene() == SC_STAGE4) {
                Create_Text(12);
            }
            else {
                Create_Text(0);
            }
            
        }
        else {
            m_pFrameKey = L"npc1_idle";
            m_eCurState = IDLE;
            if (m_bTextBox) {
                m_bTextBox->Set_Dead();
            }
        }
        break;
    default:
        break;
    }
}

void CNPC1::Motion_Change()
{
    if (m_ePreState != m_eCurState) {

        switch (m_eCurState)
        {
        case CNPC1::IDLE:
            FramSave(0, 5, m_TurnDirection, 200);
            break;
        case CNPC1::TALK:
            FramSave(0, 5, m_TurnDirection, 200);
            break;
        default:
            break;
        }
        CSoundMgr::Get_Instance()->StopSound(NPC_SOUND);
        m_ePreState = m_eCurState;
    }
}

void CNPC1::ATTR_Check()
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
