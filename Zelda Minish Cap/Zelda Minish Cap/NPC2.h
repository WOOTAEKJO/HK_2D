#pragma once
#include "NPC.h"
class CNPC2 :
    public CNPC
{
public:
    CNPC2();
    virtual~CNPC2();
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
    void    ATTR_Check();
    void    Next_Text(int _NextNum,SCENEID _StageID);
private:
    DWORD   m_Cool;
    bool    m_OneSound;
};

