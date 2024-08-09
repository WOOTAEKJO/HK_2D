#include "Hive.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "CameraMgr.h"

float H_fSound = 1.f;

CHive::CHive():m_HP(0), m_HitCheck(false)
{
}

CHive::~CHive()
{
    Release();
}

void CHive::Initialize()
{
    Set_Size(254.f, 470.f);

    m_fColC = {m_tInfo.fCX,m_tInfo.fCY};

    m_eRender = GAMEOBJECT;

    m_ObjType = STRUCT;

    m_HP = 20;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/hive/hive.bmp", L"hive");

    m_pFrameKey = L"hive";

    FramSave(0, 0, 0, 0);
}

int CHive::Update()
{
    if (m_bDead) {
       
        return OBJ_DEAD;
    }

    if (m_HitCheck) {
        m_CollisionCheck = false;
        m_CollisionObjID = OBJID_END;
        m_HitCheck = false;
        CCameraMgr::Get_Instance()->ShakingEnd();
    }

    Collision();

    CObj::Update_Rect();
    return 0;
}

void CHive::Late_Update()
{
    if (m_HP <= 0) {
        CCameraMgr::Get_Instance()->ShakingEnd();
        Set_Dead();
    }
}

void CHive::Render(HDC hDC)
{
    CObj::Camera_Col_Render_LR(hDC, 7, 7, 7);
}

void CHive::Release()
{
}

void CHive::Collision()
{
    if (m_CollisionCheck) {
        if (!m_HitCheck) {
            if (m_CollisionObjID == PMELEE || m_CollisionObjID == PBULLET) {
                m_HP -= m_HitDamage;
                m_HitCheck = true;
                if (m_HP <= 0) {
                    CCameraMgr::Get_Instance()->ShakingStart(10.f);
                }
                else if(m_HP <=2){
                    CSoundMgr::Get_Instance()->PlaySoundW(L"H_hive_hit.wav", STRUCTSOUND, H_fSound);
                    CSoundMgr::Get_Instance()->PlaySoundW(L"H_hive_death.wav", STRUCTSOUND, H_fSound);
                }
                else {
                    CSoundMgr::Get_Instance()->PlaySoundW(L"H_hive_hit.wav", STRUCTSOUND, H_fSound);
                    CCameraMgr::Get_Instance()->ShakingStart(10.f);
                }
            }
        }
    }
}
