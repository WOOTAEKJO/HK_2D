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
	// 라인과 라인 충돌 체크
	void		Load_Line();
	void		Load_Line(STAGEID _stageid);
public:
	DIRECTION	Get_CollDirCheck() { return m_CollDirCheck; }
private:
	static CLineMgr* m_pInstance;
	//list<CLine*> m_LineList;

	vector<CLine*>          m_TempLine;				// 모든 라인들을 받아오고 분배하는 역할
	vector<CLine*>          m_LineList[LINE_END];	// 벽과 땅 라인 배열

	LINEPOINT				m_tLintPoint[2];

	LINEID					m_LineID;	// 벽인지 땅인지 구분

	DIRECTION				m_CollDirCheck;

};

