#pragma once
#include "Character.h"

class CFalseKnight :
    public CCharacter
{
public:
    enum STATE{IDLE,
                READY,
                TURN,
                RUN,
                HIT,
                ATTACK,ATTACK2,ATTACKEND,ATTACKINIT,
                JUMP, JUMPATTACK1, JUMPATTACK2, JUMPATTACK3, JUMPATTACKINIT, JUMPEND, JUMPINIT,
                FRONTJUMP,BACKJUMP,
                STUNOPEN, STUNROLL, STUNROLLEND,STUNCLOSE,
                DEATH,DEATH2,
                STATE_END};

    enum PATTERN{PATTERN1, PATTERN2, PATTERN3, PATTERN_END};
public:
    CFalseKnight();
    virtual ~CFalseKnight();
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
    void    Pattern();
    float    Distance();
public:
    void    JumpAttack();
    void    WaveAttack();
    void    Death();
    void    Barrel();
private:

    STATE				m_eCurState;
    STATE				m_ePreState;
    
private:
    int                 m_Defense;      // 방어
    int                 m_life;         // 스턴 패턴 3번 먹으면 죽음

private:
    INFO                m_JumpRange;
    INFO                m_AttackRange;
    INFO                m_ShockWaveRange;
private:
    PATTERN                 m_PatternCheck;
private:
    int                 m_Rand; // 랜덤 패턴
    float                 m_Distance; // 플레이어와 거리 계산
    float                 m_Distance2;
private:
    DWORD               m_JumpAttackTime;
    bool                m_JumpCheck;

private:
    int                 m_tempo;    // 프레임을 늦추려고 이미지가 늦게 나오는 경우에 사용
private:
    bool                m_bRun;         // 뛰고 있는지를 판단.
    float               m_fOpposite;    // 반대 쪽으로 튕기는 힘
    bool                m_bEscapeWall;  // 벽 탈출
    STATE               m_eJumpState;   // 다음 점프 상태

private:
    CObj* m_BossAttack;
    CObj* m_BossWave;
private:
    bool                m_StunCheck;    // 스턴 상태 이후 패턴을 위해서
    int                 m_Attack2Count; // 공격 횟수 총 8번 내려 찍음
private:
    vector<CObj*>       m_Barrelvec;    // 바렐들을 담아 둘 벡터
    int                 m_BarrelTempo;
private:
    DWORD               m_HitTime;      // 맞는 시간 설정
    bool                m_bHitCheck;    // 충돌 체크
private:
    bool                m_bReady;
private:
    list<CObj*>         m_Wall;
    bool                m_OneSound;
private:
    bool                m_StunHit;
private:
    CObj* m_StunEffect;
};

