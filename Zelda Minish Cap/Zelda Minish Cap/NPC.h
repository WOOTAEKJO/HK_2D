#pragma once
#include "Character.h"
class CNPC :
    public CCharacter
{
public:
    enum STATE { IDLE, TALK, STATE_END };
public:
    CNPC();
    virtual~CNPC();
public:
    virtual void Initialize() PURE;
    virtual int Update() PURE;
    virtual void Late_Update() PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release() PURE;
    virtual void Collision() PURE;
    virtual void Act() PURE;
    virtual void Motion_Change() PURE;
public:
    void    Create_Text(int _TextNum);
    void    Save_Text();
    
protected:
    STATE				m_eCurState;
    STATE				m_ePreState;
protected:
    bool                m_bTalk;
protected:
    CObj*               m_bTextBox;
protected:
    vector<const TCHAR*> m_Textvec;
protected:
    int                 m_nextTalk;
};

