#pragma once
#include "Scene.h"
class CStage7 :
    public CScene
{
public:
    CStage7();
    virtual ~CStage7();
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
private:
};

