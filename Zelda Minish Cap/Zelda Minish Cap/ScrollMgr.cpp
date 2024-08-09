#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;


	if (WINCX - STAGE1X > m_fScrollX)
		m_fScrollX = WINCX - STAGE1X;

	if (WINCY - STAGE1Y - 300 > m_fScrollY)
		m_fScrollY = WINCY - STAGE1Y - 300;
	// stage2 4519 x 2600
	//stage1 9448 x 2160
}
