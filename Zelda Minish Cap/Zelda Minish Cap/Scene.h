#pragma once
#include "framework.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;
public:
	void	Stop() { m_bStop = true; }
public:
	void	Set_PlayerPos(float _x, float _y) {
		m_PlayerPos.x = _x;
		m_PlayerPos.y = _y;
	}
	fPOINT	Get_PlayerPos() { return m_PlayerPos; }
protected:
	bool m_bStop;
	DWORD	m_StopTime;

protected:
	fPOINT m_PlayerPos;

	
};

