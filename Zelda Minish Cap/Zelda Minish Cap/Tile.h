#pragma once
#include "Obj.h"
class CTile :
    public CObj
{
public:
    CTile();
    virtual~CTile();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Collision() override;
public:
    TILEOPTION			Get_DrawID() { return m_iDrawID; }
    TILEOPTION			Get_Option() { return m_iOption; }

    void		Set_ID(TILEOPTION _iDrawID, TILEOPTION _iOption)
    {
        m_iDrawID = _iDrawID;
        m_iOption = _iOption;
    }
private:
    TILEOPTION m_iDrawID;
    TILEOPTION m_iOption;

    
    
};

