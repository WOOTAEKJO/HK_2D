#pragma once
#include "Character.h"
class CPlayer :
    public CCharacter
{
public:
    /*enum STATE { IDLE, WALK, ATTACK,TOP_ATTACK,DOWN_ATTACK,JUMP_START,JUMP_REACH,JUMP_FALLING,
        JUMP_LANDING,DASH, HIT, DEAD, STATE_END };*/
    enum STATE{IDLE,DEATH,WALK,RUN,SIT,STUN,
        LOOKDOWN,LOOKDOWN2IDLE,LOOKUP,LOOKUP2IDLE,
        SLASH2,SLASH,UPSLASH,DOWNSLASH,
        DOUBLEJUMP,JUMP,
        JUMPEND,
        WALL,WALLJUMP,
        FALL,
        DASH,DASH2IDLE,
        FOCUS,FOCUS2IDLE,
        FIRE,
        STATE_END};

    enum HPSTATE { FULL, DESTORY, HPSTATE_END};
public:
    CPlayer();
    virtual ~CPlayer();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
    virtual void Act() override;
    virtual void Motion_Change() override;
public:
    void        Wall_Coll_Check();
public:
    void        Attack();
    void        SoulBullet();
    void        Dash();
    void        DownAttack();
    void        Parrying();     // 패링

    void        SkillCheck(STATE _CurState);
public:
    bool        Get_Heal() { return m_HealCheck; }
    void        Set_Heal(bool _b) { m_HealCheck = _b; }
    /*void        Set_TurnMotion(int _n) {
        m_tFrame.iMotion = _n;
        m_TurnDirection = _n;
    }*/
public:
    

private:

    STATE				m_eCurState;
    STATE				m_ePreState;
private:
    int                 m_iCheck;
    bool                m_bOnGround;

private:
    bool                m_HealCheck;
    DWORD               m_HealCheckTime;
private:
    CObj* m_Attack;
    //CObj* m_SoulBullet;
    CObj* m_DashEffect;
    CObj* m_HealEffect;
    CObj* m_StunEffect1;
    CObj* m_StunEffect2;
private:
    DWORD               m_DashTime;
    float               m_fDashMax;
    bool                m_bDash;
    bool                m_bDashCool;
private:
    //map<STATE, FRAME>    m_FramMap;
    float               m_RunReady;
    //bool                m_bRunCheck;
private:
    const TCHAR*              m_PlayerState;
private:
    float               g_fSound; // 사운드 관련
private:
    bool                m_SkillCheck;
private:
    bool                m_bHitCool;
    DWORD               m_HitCoolTime;
    // 피격 당했을 시 몇초 무적 판정
private:
    vector<CObj*> m_HPvec;  // hp ui 벡터를 불러와서 사용하기 위해
private:
    float               m_HitSpeed;     // 피격 당하면 x 좌표로 날아가는 속도

private:
    int                 m_AttackCount; // 상대를 공격한 횟수 -> 소울을 채우려고.
private:
    bool                m_WallCheck; // 벽에 붙었는지를 체크
private:
    int                 m_ATTACKNUM; // 공격 생성 갯수 확인
private:
    bool                m_OneSound;
    bool                m_DashSound;
private:
    OBJID               m_AttackCol;
private:
    bool        m_GMMODE;
private:
    bool        m_bDoubleJumpUnLock;
    bool        m_WallUnLock;
    bool        m_DashUnLock;
public:
    void    Set_DoubleJumpUnLockl() { m_bDoubleJumpUnLock = true; }
    bool    Get_DoubleJumpUnLockl() { return m_bDoubleJumpUnLock; }

    void    Set_WallUnLock() { m_WallUnLock = true; }
    bool    Get_WallUnLock() { return m_WallUnLock; }

    void    Set_DashUnLock() { m_DashUnLock = true; }
    bool    Get_DashUnLock() { return m_DashUnLock; }

    bool    Get_ALLUnLock() {
        if (m_WallUnLock && m_bDoubleJumpUnLock && m_DashUnLock) {
            return true;
        }

        return false;
    
    }

    private:
        bool        m_OneParrying;
};

