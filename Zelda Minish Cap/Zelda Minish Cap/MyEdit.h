#pragma once
#include "Scene.h"
class CMyEdit :
    public CScene
{
public:
    CMyEdit();
    virtual ~CMyEdit();
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
public:
    void Save_Tile();
private:
    void Key_Input();
    
private:
    TILEOPTION m_OptionNum;
    TILEOPTION m_DrawID;
};

