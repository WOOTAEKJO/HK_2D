#pragma once
#include "Scene.h"

class CObj;

class CStage:
	public CScene
{
public:
	CStage();
	virtual ~CStage();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:

private:
	//bool	m_bStop;
};

