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
    int                 m_Defense;      // ���
    int                 m_life;         // ���� ���� 3�� ������ ����

private:
    INFO                m_JumpRange;
    INFO                m_AttackRange;
    INFO                m_ShockWaveRange;
private:
    PATTERN                 m_PatternCheck;
private:
    int                 m_Rand; // ���� ����
    float                 m_Distance; // �÷��̾�� �Ÿ� ���
    float                 m_Distance2;
private:
    DWORD               m_JumpAttackTime;
    bool                m_JumpCheck;

private:
    int                 m_tempo;    // �������� ���߷��� �̹����� �ʰ� ������ ��쿡 ���
private:
    bool                m_bRun;         // �ٰ� �ִ����� �Ǵ�.
    float               m_fOpposite;    // �ݴ� ������ ƨ��� ��
    bool                m_bEscapeWall;  // �� Ż��
    STATE               m_eJumpState;   // ���� ���� ����

private:
    CObj* m_BossAttack;
    CObj* m_BossWave;
private:
    bool                m_StunCheck;    // ���� ���� ���� ������ ���ؼ�
    int                 m_Attack2Count; // ���� Ƚ�� �� 8�� ���� ����
private:
    vector<CObj*>       m_Barrelvec;    // �ٷ����� ��� �� ����
    int                 m_BarrelTempo;
private:
    DWORD               m_HitTime;      // �´� �ð� ����
    bool                m_bHitCheck;    // �浹 üũ
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

