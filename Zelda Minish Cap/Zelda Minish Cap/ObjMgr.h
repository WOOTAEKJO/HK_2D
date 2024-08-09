#pragma once
#include "framework.h"
#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
public:
	static CObjMgr* Get_Instance() {
		if (!m_Instance) {
			m_Instance = new CObjMgr;
		}
		return m_Instance;
	}
	static void Delete_Instance() {
		if (m_Instance) {
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
public:
	CObj*	Get_Player() { return m_ObjList[PLAYER].front(); }
	vector<CObj*> Get_HP() { return m_HealVec; }	// hp 벡터의 정보를 얻어오려고

	list<CObj*>* Get_ObjList() { return m_ObjList; }

public:
	void Add_Object(OBJID _ID, CObj* pInstance);
	int Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Delete_ID(OBJID _ID);
	void Scene_Delete_Object();
public:
	void	Add_HP_UI(CObj* pInstance);	// hp ui를 벡터에 추가.

private:
	static CObjMgr* m_Instance;

	list<CObj*> m_ObjList[OBJID_END];
	list<CObj*> m_RenderList[RENDER_END];

	vector<CObj*> m_HealVec;	// hp ui를 담아 둘 hp 벡터
};

