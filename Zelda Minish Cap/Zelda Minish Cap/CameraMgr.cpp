#include "CameraMgr.h"
#include "SceneMgr.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

CCameraMgr::CCameraMgr():m_eCurrentStage(0), m_Shaking(false), m_ShakingTime(GetTickCount64()), m_ShakingPower(0.f)
{
    ZeroMemory(&m_MapSize, sizeof(m_MapSize));
}

CCameraMgr::~CCameraMgr()
{
}

INFO CCameraMgr::Get_RenderPos(INFO _tObjPos)
{
    _tObjPos.fX -= m_tDiff.fX;
    _tObjPos.fY -= m_tDiff.fY;
	return _tObjPos;
}

LINE CCameraMgr::Get_Line_RenderPos(LINE _tLinePos)
{
    // 카메라가 이동함에 따라 렌더 좌표가 달라진다.
    // 해상도 중심위치와, 카메라 LookAt간의 차이 만큼
    _tLinePos.tLpoint.fX -= m_tLineDiff.tLpoint.fX;
    _tLinePos.tLpoint.fY -= m_tLineDiff.tLpoint.fY;

    _tLinePos.tRpoint.fX -= m_tLineDiff.tRpoint.fX;
    _tLinePos.tRpoint.fY -= m_tLineDiff.tRpoint.fY;

    return _tLinePos;
}

POINT CCameraMgr::Get_Point_RenderPos(POINT _tPointPos)
{
    _tPointPos.x -= m_PointDiff.x;
    _tPointPos.y -= m_PointDiff.y;

    return _tPointPos;
}

void CCameraMgr::Update()
{
	if (m_pTarget) {
		m_tLookPos = *(m_pTarget->Get_Info());
        
        if (m_Shaking) {
            if (m_ShakingTime + 50 < GetTickCount64()) {

                m_tLookPos.fX += m_ShakingPower;
                m_tLookPos.fY -= m_ShakingPower;
                m_ShakingTime = GetTickCount64();
                
            }
            else {
               
                m_tLookPos = *(m_pTarget->Get_Info());
            }
        }
    }
    else {
        return;
    }

    CameraSetting();

    CalDiff();
    

    
    // ground: 1920 x 1280
    // ground: 9448 x 2160
    // 이미지사이즈 : 1920 x 1080 / 윈도우창 800 x 600 일 경우
    //if (400.f >= m_tLookPos.fX) //카메라의 x좌표가 400보다 작다면(왼쪽이라면)
    //{
    //    m_tLookPos.fX = 400.f;
    //    //카메라의 x좌표 = 윈도우창 가로의 반지름
    //}
    //else if (1920.f - WINCX <= m_tLookPos.fX) //카메라의 x좌표가 이미지사이즈의 가로보다 크다면(오른쪽이라면)
    //{
    //    m_tLookPos.fX = 1920.f - WINCX;
    //    //카메라의 x좌표 = 이미지의 가로 - 윈도우창 가로사이즈
    //}

    //if (300.f >= m_tLookPos.fY) //카메라의 y좌표가 300보다 작다면(위쪽이라면)
    //{
    //    m_tLookPos.fY = 300.f;
    //}
    //else if (1280.f - WINCY <= m_tLookPos.fY) //카메라의 y좌표가 이미지사이즈의 세로보다 아래면(아래라면)
    //{
    //    m_tLookPos.fY = 1280.f - WINCY;
    //}
    // 1100 x 700
    //if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE1) {
    //    if (WINCXHALF >= m_tLookPos.fX) //카메라의 x좌표가 400보다 작다면(왼쪽이라면)
    //    {
    //        m_tLookPos.fX = WINCXHALF;
    //        //카메라의 x좌표 = 윈도우창 가로의 반지름
    //    }
    //    else if (9448.f - WINCXHALF <= m_tLookPos.fX) //카메라의 x좌표가 이미지사이즈의 가로보다 크다면(오른쪽이라면)
    //    {
    //        m_tLookPos.fX = 9448.f - WINCXHALF;
    //        //카메라의 x좌표 = 이미지의 가로 - 윈도우창 가로사이즈
    //    }

    //    if (WINCYHALF >= m_tLookPos.fY) //카메라의 y좌표가 300보다 작다면(위쪽이라면)
    //    {
    //        m_tLookPos.fY = WINCYHALF;
    //    }
    //    else if (2160.f - WINCYHALF <= m_tLookPos.fY) //카메라의 y좌표가 이미지사이즈의 세로보다 아래면(아래라면)
    //    {
    //        m_tLookPos.fY = 2160.f - WINCYHALF;
    //    }
    //}
    //else if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE2) {
    //    if (WINCXHALF >= m_tLookPos.fX) //카메라의 x좌표가 400보다 작다면(왼쪽이라면)
    //    {
    //        m_tLookPos.fX = WINCXHALF;
    //        //카메라의 x좌표 = 윈도우창 가로의 반지름
    //    }
    //    else if (4519.f - WINCXHALF  <= m_tLookPos.fX) //카메라의 x좌표가 이미지사이즈의 가로보다 크다면(오른쪽이라면)
    //    {
    //        m_tLookPos.fX = 4519.f - WINCXHALF;
    //        //카메라의 x좌표 = 이미지의 가로 - 윈도우창 가로사이즈
    //    }

    //    if (WINCYHALF >= m_tLookPos.fY) //카메라의 y좌표가 300보다 작다면(위쪽이라면)
    //    {
    //        m_tLookPos.fY = WINCYHALF;
    //    }
    //    else if (2600.f - WINCYHALF <= m_tLookPos.fY) //카메라의 y좌표가 이미지사이즈의 세로보다 아래면(아래라면)
    //    {
    //        m_tLookPos.fY = 2600.f - WINCYHALF;
    //    }
    //}// 맵 크기 4519 x 2600

    //else if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3) {
    //    if (WINCXHALF >= m_tLookPos.fX) //카메라의 x좌표가 400보다 작다면(왼쪽이라면)
    //    {
    //        m_tLookPos.fX = WINCXHALF;
    //        //카메라의 x좌표 = 윈도우창 가로의 반지름
    //    }
    //    else if (3793.f - WINCXHALF <= m_tLookPos.fX) //카메라의 x좌표가 이미지사이즈의 가로보다 크다면(오른쪽이라면)
    //    {
    //        m_tLookPos.fX = 3793.f - WINCXHALF;
    //        //카메라의 x좌표 = 이미지의 가로 - 윈도우창 가로사이즈
    //    }

    //    if (WINCYHALF >= m_tLookPos.fY) //카메라의 y좌표가 300보다 작다면(위쪽이라면)
    //    {
    //        m_tLookPos.fY = WINCYHALF;
    //    }
    //    else if (2200.f - WINCYHALF <= m_tLookPos.fY) //카메라의 y좌표가 이미지사이즈의 세로보다 아래면(아래라면)
    //    {
    //        m_tLookPos.fY = 2200.f - WINCYHALF;
    //    }
    //}// 맵 크기 3793 x 2200

    //else if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE4) {
    //    if (WINCXHALF >= m_tLookPos.fX) //카메라의 x좌표가 400보다 작다면(왼쪽이라면)
    //    {
    //        m_tLookPos.fX = WINCXHALF;
    //        //카메라의 x좌표 = 윈도우창 가로의 반지름
    //    }
    //    else if (7998.f - WINCXHALF <= m_tLookPos.fX) //카메라의 x좌표가 이미지사이즈의 가로보다 크다면(오른쪽이라면)
    //    {
    //        m_tLookPos.fX = 7998.f - WINCXHALF;
    //        //카메라의 x좌표 = 이미지의 가로 - 윈도우창 가로사이즈
    //    }

    //    if (WINCYHALF >= m_tLookPos.fY) //카메라의 y좌표가 300보다 작다면(위쪽이라면)
    //    {
    //        m_tLookPos.fY = WINCYHALF;
    //    }
    //    else if (2160.f - WINCYHALF <= m_tLookPos.fY) //카메라의 y좌표가 이미지사이즈의 세로보다 아래면(아래라면)
    //    {
    //        m_tLookPos.fY = 2160.f - WINCYHALF;
    //    }
    //}// 맵 크기 7998 x 2160

    
	
}

void CCameraMgr::CameraSetting()
{
    if (WINCXHALF >= m_tLookPos.fX) //카메라의 x좌표가 400보다 작다면(왼쪽이라면)
    {
        m_tLookPos.fX = WINCXHALF;
        //카메라의 x좌표 = 윈도우창 가로의 반지름
    }
    else if (m_MapSize.x - WINCXHALF <= m_tLookPos.fX) //카메라의 x좌표가 이미지사이즈의 가로보다 크다면(오른쪽이라면)
    {
        m_tLookPos.fX = m_MapSize.x - WINCXHALF;
        //카메라의 x좌표 = 이미지의 가로 - 윈도우창 가로사이즈
    }

    if (WINCYHALF >= m_tLookPos.fY) //카메라의 y좌표가 300보다 작다면(위쪽이라면)
    {
        m_tLookPos.fY = WINCYHALF;
    }
    else if (m_MapSize.y - WINCYHALF <= m_tLookPos.fY) //카메라의 y좌표가 이미지사이즈의 세로보다 아래면(아래라면)
    {
        m_tLookPos.fY = m_MapSize.y - WINCYHALF;
    }
}

void CCameraMgr::CalDiff()
{
	float fx = (float)(WINCX * 0.5f);
	float fy = (float)(WINCY * 0.5f);

	m_tDiff.fX = m_tLookPos.fX - fx;
	m_tDiff.fY = m_tLookPos.fY - fy;

    m_tLineDiff.tLpoint.fX = m_tLookPos.fX - fx;
    m_tLineDiff.tLpoint.fY = m_tLookPos.fY - fy;

    m_tLineDiff.tRpoint.fX = m_tLookPos.fX - fx;
    m_tLineDiff.tRpoint.fY = m_tLookPos.fY - fy;

    m_PointDiff.x = m_tLookPos.fX - fx;
    m_PointDiff.y = m_tLookPos.fY - fy;

}
