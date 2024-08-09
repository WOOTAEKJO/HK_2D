#pragma once
#include "Scene.h"
class CStage4 :
    public CScene
{
public:
    CStage4();
    virtual ~CStage4();
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
private:
};

