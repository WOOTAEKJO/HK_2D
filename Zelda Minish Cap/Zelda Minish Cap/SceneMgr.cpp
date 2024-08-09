#include "SceneMgr.h"
#include "MyEdit.h"
#include "Stage.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "Stage7.h"
#include "KeyMgr.h"
#include "Menu.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr(): m_eCurScene(SC_LOGO), m_ePreScene(SC_END), m_pScene(nullptr), m_eCurStage(STAGEID_END),
m_SavePreScene(SC_END)
{
	
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	m_eCurScene = eScene;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			//m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;
		case SC_STAGE1:
			m_pScene = new CStage;
			break;
		case SC_STAGE2:
			m_pScene = new CStage2;
			break;
		case SC_STAGE3:
			m_pScene = new CStage3;
			break;
		case SC_STAGE4:
			m_pScene = new CStage4;
			break;
		case SC_STAGE5:
			m_pScene = new CStage5;
			break;
		case SC_STAGE6:
			m_pScene = new CStage6;
			break;
		case SC_STAGE7:
			m_pScene = new CStage7;
			break;
		}

		if (!m_pScene)
			return;
		
		if (m_eCurScene != SC_MENU) {
			if (!m_StagePlayerPos.empty()) {
				for (auto& iter : m_StagePlayerPos) {
					if (iter.first == m_eCurScene) {
						if (iter.second.m_ePrSt == m_ePreScene) {
							m_pScene->Set_PlayerPos(iter.second.m_Px, iter.second.m_Py);
						}
					}
				}
			}
		}

		m_pScene->Initialize();
		m_SavePreScene = m_ePreScene;
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
	CKeyMgr::Get_Instance()->Key_LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::SceneStop()
{
	m_pScene->Stop();
}

void CSceneMgr::Add_StagePlayerPos(SCENEID _eCurScene, SCENEID _ePreScene, float _x, float _y)
{
	POS _pos = { _ePreScene,_x,_y };
	m_StagePlayerPos.insert({ _eCurScene,_pos });

}

