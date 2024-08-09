#include "Collision.h"
#include "Player.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, (Dst->Get_Rect()), (Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}


}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float fX = 0.f, fY = 0.f;
	DIRECTION m_Dir = DIR_END;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				// ���� �浹
				if (fX > fY)
				{
					// �� �浹
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						Dst->Set_PosY(-fY);
					}
					// �� �浹
					else
					{
						Dst->Set_PosY(fY);
					}
				}
				// �¿� �浹
				else
				{
					// �� �浹
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						Dst->Set_PosX(-fX);
					}
					// �� �浹
					else
					{
						Dst->Set_PosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* _pX, float* _pY)
{
	float		fWidth = fabs(_Dst->Get_Info()->fX - _Src->Get_Info()->fX);
	float		fHeight = fabs(_Dst->Get_Info()->fY - _Src->Get_Info()->fY);

	float		fRadiusX = (_Dst->Get_Info()->fCX + _Src->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (_Dst->Get_Info()->fCY + _Src->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::Collision_ColliderEx(list<CObj*> _Dst, list<CObj*> _Src, int _n)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst : _Dst)
	{
		  for (auto & Src : _Src)
  		{
			  if (_n == COLLIDER) {
				  if (Check_Collider(Dst, Src, &fX, &fY, _n))
				  {
						  // ���� �浹
						  if (fX > fY)
						  {
							  // �� �浹
							  if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
							  {

								  if ((Dst->Get_ObjID() == PLAYER || Dst->Get_ObjID() == MONSTER) &&
									  Src->Get_ObjID() == PWALL) {
									  Dst->Set_PosY(-fY);
								  }
								  /*if (Dst->Get_ObjID() == PLAYER && (Dst->Get_ObjID() == MONSTER || Dst->Get_ObjID() == MBULLET)) {
									  dynamic_cast<CPlayer*>(Dst)->Set_MonsterColCheck();
								  }*/


								  Dst->Set_CollisionCheck(true);	// �浹 ����
								  Dst->Set_CollisionObjID(Src->Get_ObjID());	// �浹�� ������Ʈ
								  Dst->Set_CollisionPos(Src->Get_Info()->fX, Src->Get_Info()->fY); // �浹�� ������Ʈ ���� ��ǥ
								  Dst->Set_HitDamage(Src->Get_Damage());	// ��� �浹ü�� �������� ����
								  Dst->Set_Dir(UP);	// �浹 ����
								  // �ؿ� �ִ� ��

								  Src->Set_CollisionCheck(true);
								  Src->Set_CollisionObjID(Dst->Get_ObjID());
								  Src->Set_CollisionPos(Dst->Get_Info()->fX, Dst->Get_Info()->fY);
								  Src->Set_HitDamage(Dst->Get_Damage());
								  Src->Set_Dir(DOWN);
								  // ���� �ִ� ��
								  //*_ColDir = UP;

							  }
							  // �� �浹
							  else
							  {
								  if ((Dst->Get_ObjID() == PLAYER || Dst->Get_ObjID() == MONSTER) &&
									  Src->Get_ObjID() == PWALL) {
									  Dst->Set_PosY(fY);
								  }
								  /*if (Dst->Get_ObjID() == PLAYER && (Dst->Get_ObjID() == MONSTER || Dst->Get_ObjID() == MBULLET)) {
									  dynamic_cast<CPlayer*>(Dst)->Set_MonsterColCheck();
								  }*/
								  Dst->Set_CollisionCheck(true);
								  Dst->Set_CollisionObjID(Src->Get_ObjID());
								  Dst->Set_CollisionPos(Src->Get_Info()->fX, Src->Get_Info()->fY);
								  Dst->Set_HitDamage(Src->Get_Damage());
								  Dst->Set_Dir(DOWN);	// ���� �ִ� ��

								  Src->Set_CollisionCheck(true);
								  Src->Set_CollisionObjID(Dst->Get_ObjID());
								  Src->Set_CollisionPos(Dst->Get_Info()->fX, Dst->Get_Info()->fY);
								  Src->Set_HitDamage(Dst->Get_Damage());
								  Src->Set_Dir(UP); // �ؿ� �ִ� ��
								  //*_ColDir = DOWN;
								  return true;
							  }
						  }
						  // �¿� �浹
						  else
						  {
							  // �� �浹
							  if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
							  {

								  if ((Dst->Get_ObjID() == PLAYER || Dst->Get_ObjID() == MONSTER) &&
									  Src->Get_ObjID() == PWALL) {
									  Dst->Set_PosX(-fX);
								  }
								  /*if (Dst->Get_ObjID() == PLAYER && (Dst->Get_ObjID() == MONSTER || Dst->Get_ObjID() == MBULLET)) {
									  dynamic_cast<CPlayer*>(Dst)->Set_MonsterColCheck();
								  }*/
								  Dst->Set_CollisionCheck(true);
								  Dst->Set_CollisionObjID(Src->Get_ObjID());
								  Dst->Set_CollisionPos(Src->Get_Info()->fX, Src->Get_Info()->fY);
								  Dst->Set_HitDamage(Src->Get_Damage());
								  Dst->Set_Dir(RIGHT);

								  Src->Set_CollisionCheck(true);
								  Src->Set_CollisionObjID(Dst->Get_ObjID());
								  Src->Set_CollisionPos(Dst->Get_Info()->fX, Dst->Get_Info()->fY);
								  Src->Set_HitDamage(Dst->Get_Damage());
								  Src->Set_Dir(LEFT);
								  //*_ColDir = LEFT;
								  return true;
							  }
							  // �� �浹
							  else
							  {

								  if ((Dst->Get_ObjID() == PLAYER || Dst->Get_ObjID() == MONSTER) &&
									  Src->Get_ObjID() == PWALL) {
									  Dst->Set_PosX(+fX);
								  }	// �÷��̾ ���Ͱ� ���� �浹�ϸ� �з� ���� �� �����̴� ��ó�� ����
								  //if (Dst->Get_ObjID() == PLAYER && (Dst->Get_ObjID() == MONSTER || Dst->Get_ObjID() == MBULLET)) {
								  //	dynamic_cast<CPlayer*>(Dst)->Set_MonsterColCheck();
								  //}  // �÷��̾� ���Ϳ� ���� �Ѿ˿� ������ �ǰ�����
								  Dst->Set_CollisionCheck(true);
								  Dst->Set_CollisionObjID(Src->Get_ObjID());
								  Dst->Set_CollisionPos(Src->Get_Info()->fX, Src->Get_Info()->fY);
								  Dst->Set_HitDamage(Src->Get_Damage());
								  Dst->Set_Dir(LEFT);

								  Src->Set_CollisionCheck(true);
								  Src->Set_CollisionObjID(Dst->Get_ObjID());
								  Src->Set_CollisionPos(Dst->Get_Info()->fX, Dst->Get_Info()->fY);
								  Src->Set_HitDamage(Dst->Get_Damage());
								  Src->Set_Dir(RIGHT);
								  //*_ColDir = RIGHT;
								  return true;
							  }
						  }
					  
				  }
				  else {
					  //return false;
				  }
			  }else if (_n == ATTACKRANGE) {
				  if (Check_Collider(Dst, Src, &fX, &fY, _n)) {
					  // ���� �浹
					  if (fX > fY)
					  {
						  // �� �浹
						  if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
						  {
							  Dst->Set_ATTR_Check(true);
							  Dst->Set_ATTR_ObjID(Src->Get_ObjID());

							  Src->Set_ATTR_Check(true);
							  Src->Set_ATTR_ObjID(Dst->Get_ObjID());

							  return true;
						  }
						  // �� �浹
						  else
						  {
							  Dst->Set_ATTR_Check(true);
							  Dst->Set_ATTR_ObjID(Src->Get_ObjID());

							  Src->Set_ATTR_Check(true);
							  Src->Set_ATTR_ObjID(Dst->Get_ObjID());
							  return true;
						  }
					  }
					  // �¿� �浹
					  else
					  {
						  // �� �浹
						  if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
						  {
							  Dst->Set_ATTR_Check(true);
							  Dst->Set_ATTR_ObjID(Src->Get_ObjID());

							  Src->Set_ATTR_Check(true);
							  Src->Set_ATTR_ObjID(Dst->Get_ObjID());
							  return true;
						  }
						  // �� �浹
						  else
						  {
							  Dst->Set_ATTR_Check(true);
							  Dst->Set_ATTR_ObjID(Src->Get_ObjID());

							  Src->Set_ATTR_Check(true);
							  Src->Set_ATTR_ObjID(Dst->Get_ObjID());
							  return true;
						  }
					  }
				  }
				  else {
					  Dst->Set_ATTR_Check(false);
					  Dst->Set_ATTR_ObjID(OBJID_END);

					  Src->Set_ATTR_Check(false);
					  Src->Set_ATTR_ObjID(OBJID_END);
				  }
			  }
		}
	}
	return false;
}

bool CCollisionMgr::Check_Collider(CObj* _Dst, CObj* _Src, float* _pX, float* _pY, int _n)
{
	float		fWidth = fabs(_Dst->Get_Info()->fX - _Src->Get_Info()->fX);
	float		fHeight = fabs(_Dst->Get_Info()->fY - _Src->Get_Info()->fY);
	float		fRadiusX = 0.f;
	float		fRadiusY = 0.f;
	if (_n == COLLIDER) {
		fRadiusX = (_Dst->Get_ColC()->x + _Src->Get_ColC()->x) * 0.5f;
		fRadiusY = (_Dst->Get_ColC()->y + _Src->Get_ColC()->y) * 0.5f;
	}
	else if (_n == ATTACKRANGE) {
		fRadiusX = (_Dst->Get_ATTRC()->x + _Src->Get_ATTRC()->x) * 0.5f;
		fRadiusY = (_Dst->Get_ATTRC()->y + _Src->Get_ATTRC()->y) * 0.5f;
	}

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float	fWidth = abs(_Dst->Get_Info()->fX - _Src->Get_Info()->fX);
	float	fHeight = _Dst->Get_Info()->fY - _Src->Get_Info()->fY;

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_Dst->Get_Info()->fCX + _Src->Get_Info()->fCX) * 0.5f;

	return fDiagonal <= fRadius;
}

void CCollisionMgr::Set_Info(CObj *&_Dst, CObj *&_Src, DIRECTION _Dst_Dir, DIRECTION _Src_Dir)
{
	_Dst->Set_CollisionCheck(true);	// �浹 ����
	_Dst->Set_CollisionObjID(_Src->Get_ObjID());	// �浹�� ������Ʈ
	_Dst->Set_HitDamage(_Src->Get_Damage());	// ��� �浹ü�� �������� ����
	_Dst->Set_Dir(_Dst_Dir);	// �浹 ����
	// �ؿ� �ִ� ��

	_Src->Set_CollisionCheck(true);
	_Src->Set_CollisionObjID(_Dst->Get_ObjID());
	_Src->Set_HitDamage(_Dst->Get_Damage());
	_Src->Set_Dir(_Src_Dir);
}

