#pragma once
#include "Scene.h"
#include "framework.h"

typedef struct Pos
{
	SCENEID m_ePrSt;
	float	m_Px;
	float	m_Py;
}POS;

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void		Scene_Change(SCENEID eScene);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
public:
	fPOINT GetCameraPos() { return _cameraPos; }
	void SetCameraPos(fPOINT pos) { _cameraPos = pos; }
private:
	fPOINT _cameraPos = { WINCX, WINCY };
public:
	SCENEID	Get_CurScene() { return m_eCurScene; }
	SCENEID	Get_SavePreScene() { return m_SavePreScene; }
public:
	void	Set_StageID(STAGEID _stageid) { m_eCurStage = _stageid; }
public:
	void	SceneStop();
public:
	void	Add_StagePlayerPos(SCENEID _eCurScene, SCENEID _ePreScene, float _x, float _y);
public:
	fPOINT	Get_PLPos() { return m_pScene->Get_PlayerPos(); }
private:
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;

	STAGEID					m_eCurStage;

	multimap<SCENEID,POS>		m_StagePlayerPos;
	
	SCENEID					m_SavePreScene;
};
