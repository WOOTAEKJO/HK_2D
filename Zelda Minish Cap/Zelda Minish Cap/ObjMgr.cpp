#include "ObjMgr.h"
#include "TileMgr.h"
#include "Collision.h"
#include "SceneMgr.h"

CObjMgr* CObjMgr::m_Instance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID _ID, CObj* pInstance)
{
	if (_ID >= OBJID_END || pInstance == nullptr)
		return;

	m_ObjList[_ID].push_back(pInstance);
}

int CObjMgr::Update()
{
	for (size_t i = 0; i < OBJID_END; i++) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD) {
				Safe_Delete<CObj*>((*iter));
				iter = m_ObjList[i].erase(iter);
			}
			else {
				++iter;
			}
		}
	}
	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJID_END; i++) {
		for (auto& iter:m_ObjList[i]) {
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID eRender = iter->Get_RenderID();
			m_RenderList[eRender].push_back(iter);
		}
	}

	/*list<CObj*> m_WallTtile;
	DIRECTION	m_ColDir = DIR_END;
	m_WallTtile = *(CTileMgr::Get_Instance()->Get_WallTile());
	
		if (CCollisionMgr::Collision_ColliderEx( m_WallTtile, m_ObjList[PLAYER], &m_ColDir)) {
			m_ObjList[PLAYER].front()->Set_Dir(m_ColDir);
		}
		else {
			m_ObjList[PLAYER].front()->Set_Dir(DIR_END);
		}*/
	// �÷��̾�� ���� �浹�� üũ�ϰ� �浹�ϸ� ������ �Ѱ��ְ� �ƴϸ� ������ �ƴ� ������ �Ѱ���
	
	//if (CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER],m_ObjList[PWALL], &m_ColDir)) {
	//	m_ObjList[PLAYER].front()->Set_Dir(m_ColDir);
	//}  
	//else {
	//	m_ObjList[PLAYER].front()->Set_Dir(DIR_END);
	//}// �÷��̾�� �� �浹

	if (CSceneMgr::Get_Instance()->Get_CurScene() != SC_MENU) {
		if (CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[PWALL], COLLIDER)) {

		}
		else {
			m_ObjList[PLAYER].front()->Set_Dir(DIR_END);
			m_ObjList[PLAYER].front()->Set_CollisionCheck(false);
			m_ObjList[PLAYER].front()->Set_CollisionObjID(OBJID_END);
		}
		CCollisionMgr::Collision_ColliderEx(m_ObjList[MONSTER], m_ObjList[PWALL], COLLIDER);
		// ���Ϳ� �� �浹ó��

		CCollisionMgr::Collision_ColliderEx(m_ObjList[PMELEE], m_ObjList[MONSTER], COLLIDER);
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PBULLET], m_ObjList[MONSTER], COLLIDER);
		//CCollisionMgr::Collision_ColliderEx(m_ObjList[MONSTER], m_ObjList[PBULLET]);
		// �÷��̾� ���ݰ� ���� �浹ó��

		CCollisionMgr::Collision_ColliderEx(m_ObjList[PORTAL], m_ObjList[PLAYER], COLLIDER);
		// �÷��̾�� ��Ż �浹ó��

		CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[MONSTER], COLLIDER);
		// �÷��̾�� ���� �浹ó��
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[MBULLET], COLLIDER);
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[MBULLET2], COLLIDER);
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[MMELEE], COLLIDER);
		// �÷��̾�� ���� �Ѿ�, ���� ���� ���� �浹ó��


		CCollisionMgr::Collision_ColliderEx(m_ObjList[MBULLET], m_ObjList[PWALL], COLLIDER);
		CCollisionMgr::Collision_ColliderEx(m_ObjList[MBULLET2], m_ObjList[PWALL], COLLIDER);
		// ���� �Ѿ˰� �� �浹ó��

		CCollisionMgr::Collision_ColliderEx(m_ObjList[PMELEE], m_ObjList[MBULLET], COLLIDER);
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PMELEE], m_ObjList[MMELEE], COLLIDER);
		//�÷��̾� �Ѿ˰� ���� �Ѿ� �浹

		CCollisionMgr::Collision_ColliderEx(m_ObjList[PMELEE], m_ObjList[STRUCT], COLLIDER);
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PBULLET], m_ObjList[STRUCT], COLLIDER);
		// �÷��̾� ���ݰ� ����ü �浹 ó��
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PMELEE], m_ObjList[PWALL], COLLIDER);

		CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[MONSTER], ATTACKRANGE);
		// ���� ���� ���� �÷��̾� �ν�
		CCollisionMgr::Collision_ColliderEx(m_ObjList[PLAYER], m_ObjList[NPC], ATTACKRANGE);
		// npc�� �÷��̾� �ν�

		/*for (int i = 0; i < OBJID_END; i++) {
			for (int j = 0; j < OBJID_END; j++) {
				for (auto& iter1 : m_ObjList[i]) {
					for (auto& iter2 : m_ObjList[j]) {
						if (CCollisionMgr::Collision_ColliderEx(m_ObjList[i], m_ObjList[j])) {

						}else{
							if (i == PLAYER || j == PLAYER) {
								m_ObjList[PLAYER].front()->Set_Dir(DIR_END);
								m_ObjList[PLAYER].front()->Set_CollisionCheck(false);
								m_ObjList[PLAYER].front()->Set_CollisionObjID(OBJID_END);
							}
						}
					}
				}
			}
		}*/
	}
}

void CObjMgr::Render(HDC hDC)
{
	/*for (size_t i = 0; i < OBJID_END; i++) {
		for (auto& iter : m_ObjList[i]) {
			iter->Render(hDC);

			m_RenderList[i].clear();


		}
	}*/

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc) { return pDst->Get_Info()->fY < pSrc->Get_Info()->fY; });

		for (auto& iter : m_RenderList[i])
			iter->Render(hDC);

		m_RenderList[i].clear();
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJID_END; i++) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for (size_t i = 0; i < RENDER_END; ++i)
		m_RenderList[i].clear();

}

void CObjMgr::Delete_ID(OBJID _ID)
{
	for (auto& iter : m_ObjList[_ID]) {
		Safe_Delete(iter);
	}

	m_ObjList[_ID].clear();
}

void CObjMgr::Scene_Delete_Object()
{
	for (size_t i = 0; i < OBJID_END; i++) {
		if (i != PLAYER && i != PUI) {
			/*for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
			m_ObjList[i].clear();*/
			//for_each(m_ObjList[i].begin(), m_ObjList[i].end(), [](CObj* n) {set_de})
			for (auto& iter : m_ObjList[i]) {
				iter->Set_Dead();
			}
		}
	}
}

void CObjMgr::Add_HP_UI(CObj* pInstance)
{
 	if (pInstance == nullptr)
		return;

	//m_ObjList[_ID].push_back(pInstance);
	m_HealVec.push_back(pInstance);

}
