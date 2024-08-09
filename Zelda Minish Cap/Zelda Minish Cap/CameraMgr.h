#pragma once

#include "framework.h"
#include "Obj.h"
#include "Line.h"

class CCameraMgr
{
private:
	CCameraMgr();
	~CCameraMgr();
public:
	static CCameraMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCameraMgr;
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
	void      Set_LookPos(int _iX, int _iY) { m_tLookPos.fX = (float)_iX, m_tLookPos.fY = (float)_iY; }
	void      Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	INFO      Get_RenderPos(INFO _tObjPos);

	INFO      Get_LookPos() { return m_tLookPos; }

	LINE      Get_Line_RenderPos(LINE _tLinePos);

	POINT      Get_Point_RenderPos(POINT _tPointPos);
public:
	void	Update();
public:
	void	ShakingStart(float _Power) {
		m_Shaking = true;
		m_ShakingPower = _Power;
	}
	void	ShakingEnd() { m_Shaking = false; }
public:
	void	Set_MapSize(float _x, float _y) { m_MapSize = { _x ,_y }; }
public:
	void	CameraSetting();
private:
	void    CalDiff();
private:
	static CCameraMgr* m_pInstance;

private:
	INFO   m_tLookPos;         // 카메라가 보는 위치
	CObj* m_pTarget;      // 카메라 타겟 오브젝트
	INFO   m_tDiff;         // 해상도 중심위치와, 카메라 LookAt간의 차이 값

	/*LINE    m_tLineDiff;
	POINT   m_PointDiff;*/
	LINE    m_tLineDiff;
	POINT   m_PointDiff;
private:
	int		m_eCurrentStage;
private:
	bool	m_Shaking;
	float   m_ShakingPower;
	DWORD	m_ShakingTime;

private:
	fPOINT	m_MapSize;
};

