#pragma once
#include "framework.h"


class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize()	PURE;
	virtual int Update()		PURE;
	virtual void Late_Update()	PURE;
	virtual void Render(HDC hDC)		PURE;
	virtual void Release()		PURE;
	virtual void Collision() PURE;
public:
	RECT*			Get_Rect() { return &m_tRect; }
	INFO*			Get_Info() { return &m_tInfo; }

	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void			Set_Size(float _fCX, float _fCY) {

		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}

	
	void			Set_Dead() { m_bDead = true; }
	void			Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	void			Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void			Set_PosX(float _fX) { m_tInfo.fX += _fX; }

	bool			Get_Dead() { return m_bDead; }

	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	RENDERID		Get_RenderID() { return m_eRender; }

	void			SetOwner(CObj* _owner) { m_Owner = _owner; }
	CObj*			GetOwner() { return m_Owner; }

	float			Get_Angle() { return m_fAngle; }
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
public:
	RECT			Get_Collider() { return m_tCollider; }
	fPOINT*			Get_ColC() { return &m_fColC; }

	RECT			Get_AttackRange() { return m_AttackRange; }
	fPOINT* Get_ATTRC() { return &m_fATTRC; }
public:
	void			Set_CollisionCheck(bool _b) { m_CollisionCheck = _b; }	// �浹�ߴٴ� ���� �˷���.
	bool			Get_CollisionCheck() { return m_CollisionCheck; }

	void			Set_Dir(DIRECTION eDir) { m_eDir = eDir; }		//�浹 ����
	DIRECTION		Get_Dir() { return m_eDir; }

	void			Set_CollisionObjID(OBJID _ObjID) { m_CollisionObjID = _ObjID; }	// �浹�� ������Ʈ
	OBJID			Get_CollisionObjID() { return m_CollisionObjID; }
	// � Ÿ���� ������Ʈ�� �浹�ߴ����� �˷���.

	void			Set_CollisionPos(float _fx, float _fy) { m_CollisionPos = { _fx ,_fy }; }
	fPOINT			Get_CollisionPos() { return m_CollisionPos; }		// �浹�� ������Ʈ ��ǥ
public:
	OBJID			Get_ObjID() { return m_ObjType; }
public:
	void			Set_ATTR_Check(bool _b) { m_ATTR_Check = _b; }			// �ν� ���� ����
	bool			Get_ATTR_Check() { return m_ATTR_Check; }

	void			Set_ATTR_ObjID(OBJID _ObjID){m_ATTR_ObjID= _ObjID; }
	OBJID			Get_ATTR_ObjID() { return m_ATTR_ObjID; }
public:
	void			Set_Speed(float _n) { m_fSpeed = _n; }
	void			Set_TurnDir(int _Dir) { m_TurnDirection = _Dir; }
	int				Get_TurnDir() { return m_TurnDirection; }
public:
	int		Get_Damage() { return m_Damage; }
	void	Set_HitDamage(int _Damage) { m_HitDamage = _Damage; }
protected:
	void		Update_Rect();
	void		Move_Frame();
	void        FramSave(int _start, int _end, int _turnDir, int _dwspeed);
protected:
	void		Camera_Col_Render_LR(HDC hDC, int _R, int _G, int _B);
	void		Camera_Col_Render_UD(HDC hDC, int _R, int _G, int _B);
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	
	FRAME		m_tFrame;
	RENDERID	m_eRender;

	CObj* m_pTarget;

	CObj* m_Owner;

	float		m_fSpeed;
	float		m_fAccel;
	float		m_fSpeed_Vertical;	// ���� ����

	float		m_fAngle;

	bool		m_bDead;	
	//bool		m_bTurnDirection;	// ���� ��ȯ ���� -> ��� ���� �Ǵ� ������ ����

	int			m_TurnDirection;	// ���� ��ȯ ���� -> ��� ���� �Ǵ� ������ ���� 0�� ������, 1�� ����

	const TCHAR* m_pFrameKey;		// ������ Ű����
	//const TCHAR* m_pPreFramKey;		// �� ������ Ű����

protected:
	RECT		m_tCollider;		// �浹 ó�� �ݶ��̴�
	fPOINT		m_fColC;			// �ݶ��̴� ũ��

protected:
	RECT        m_AttackRange;	// ���� ����
	fPOINT		m_fATTRC;		// �ν� ���� ũ��

	bool		m_ATTR_Check;	// �ν� ���� �浹 ����
	OBJID		m_ATTR_ObjID;	// �ν� ���� �浹 obj
protected:
	bool		m_bChangeM;			// ��� �ٲ�

protected:
	//�浹 �˷���
	bool                m_CollisionCheck;	// �浹 ����
	OBJID				m_CollisionObjID;	// �浹 obj
	DIRECTION			m_eDir;				// �浹 ���� üũ
	fPOINT				m_CollisionPos;		// �浹ü ��ǥ
protected:
	OBJID				m_ObjType;			// obj Ÿ��

protected:
	int					m_Damage;
	int					m_HitDamage;
protected:
	
			
};

