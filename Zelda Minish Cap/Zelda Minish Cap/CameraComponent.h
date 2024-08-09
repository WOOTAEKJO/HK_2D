#pragma once
#include "Component.h"
class CCameraComponent :
    public CComponent
{public:
    CCameraComponent();
    virtual ~CCameraComponent();
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
};

