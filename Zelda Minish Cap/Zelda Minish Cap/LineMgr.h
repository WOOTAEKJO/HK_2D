#pragma once
#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();
public:
	static CLineMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
public:
	bool		CollisionLine_Ground(INFO& _rInfo, float* _pY);
	bool		CollisionLine_GroundEX(INFO& _rInfo, fPOINT _ColC,CLine* _pTarget, float* _pY);
	bool		CollisionLine_Wall(RECT& _rInfo,fPOINT* _LP, fPOINT* _RP);
	bool		CheckLineIntersection(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3, float _x4, float _y4);
	// ���ΰ� ���� �浹 üũ
	void		Load_Line();
	void		Load_Line(STAGEID _stageid);
public:
	DIRECTION	Get_CollDirCheck() { return m_CollDirCheck; }
private:
	static CLineMgr* m_pInstance;
	//list<CLine*> m_LineList;

	vector<CLine*>          m_TempLine;				// ��� ���ε��� �޾ƿ��� �й��ϴ� ����
	vector<CLine*>          m_LineList[LINE_END];	// ���� �� ���� �迭

	LINEPOINT				m_tLintPoint[2];

	LINEID					m_LineID;	// ������ ������ ����

	DIRECTION				m_CollDirCheck;

};

