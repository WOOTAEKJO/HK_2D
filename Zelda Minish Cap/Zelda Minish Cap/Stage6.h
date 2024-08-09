#pragma once
#include "Scene.h"
class CStage6 :
    public CScene
{
public:
    CStage6();
    virtual ~CStage6();
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
private:
};

