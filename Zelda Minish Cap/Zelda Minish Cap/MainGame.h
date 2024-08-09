#pragma once
#include "framework.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();
private:
	HDC m_hDC;

	bool	m_bStop;
};

