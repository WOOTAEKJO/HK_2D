#pragma once
#include "Obj.h"
class CPortal :
    public CObj
{
public:
    CPortal();
    virtual ~CPortal();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    void    Set_NextStageID(SCENEID _StageID) { m_NextStageID = _StageID; }
private:
    SCENEID     m_NextStageID;
    
    // 이 포탈이 가지고 있는 다음 씬
};

