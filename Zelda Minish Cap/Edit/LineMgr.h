#pragma once
#include "Line.h"
#include "WallLine.h"
#include "GroundLine.h"
#include "ScrollMgr.h"


class CLineMgr
{
private:
    CLineMgr();
    ~CLineMgr();

public:
    bool      Collision_Line(float& fX, float* pY);
    void      Save_Line();
    void      Load_Line();

    void      Draw_Line();

public:
    void      Initialize();
    int         Update();
    void      Late_Update();
    void      Render(HDC hDC);
    void      Release();
public:
    static CLineMgr* Get_Instance()
    {
        if (!m_pInstance)
        {
            m_pInstance = new CLineMgr;
        }

        return m_pInstance;
    }
    static void      Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    //list<CLine*>         m_LineList[LINE_END];  // 총 라인 리스트
    vector<CLine*>          m_TempLine;
    vector<CLine*>          m_LineList[LINE_END];
    //vector<CWallLine*>       m_WallLine;
    //vector<CGroundLine*>     m_GroundLine;
    LINEPOINT            m_tLintPoint[2];

    static CLineMgr* m_pInstance;


private:
    bool   m_bIsDraw;  // 직선그리기
    bool   m_bDelete; // 라인 삭제

    LINEID      m_LineID;

    const TCHAR* m_szFileName;
};

