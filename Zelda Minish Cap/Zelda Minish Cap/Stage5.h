#pragma once
#include "Scene.h"
class CStage5 :
    public CScene
{
public:
    CStage5();
    virtual ~CStage5();
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
private:
};

