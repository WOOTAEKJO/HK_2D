#pragma once
#include "Obj.h"
#include "State.h"
#include "ObjMgr.h"

template<typename T, typename T2>
class Actor:public CObj
{
public:
	Actor() {}
	~Actor() {}
public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

private:
	T2				m_eState;
	IState<T, T2>* m_States[99];
};
