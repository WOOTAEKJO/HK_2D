#pragma once
#include "framework.h"

class CCharacter;

class CComponent
{
public:
	CComponent();
	virtual~CComponent();
public:
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render(HDC hdc) { }

	void SetOwner(CCharacter* owner) { m_owner = owner; }
	CCharacter* Get_Owner() { return m_owner; }

protected:
	CCharacter* m_owner;

};

