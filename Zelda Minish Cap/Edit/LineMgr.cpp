#include "LineMgr.h"
#include "KeyMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr() : m_bIsDraw(false), m_bDelete(false), m_LineID(GROUNDLINE)
{
    ZeroMemory(m_tLintPoint, sizeof(m_tLintPoint));
}


CLineMgr::~CLineMgr()
{
    Release();
}

bool CLineMgr::Collision_Line(float& fX, float* pY)
{
    /*if (m_LineList.empty())
        return false;

    CLine* pTarget = nullptr;

    for (auto& iter : m_LineList)
    {
        if (iter->Get_Info()->tLpoint.fX <= fX &&
            iter->Get_Info()->tRpoint.fX > fX)
            pTarget = iter;
    }

    if (!pTarget)
        return false;


    float   x1 = pTarget->Get_Info()->tLpoint.fX;
    float   x2 = pTarget->Get_Info()->tRpoint.fX;

    float   y1 = pTarget->Get_Info()->tLpoint.fY;
    float   y2 = pTarget->Get_Info()->tRpoint.fY;

    *pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

    return true;*/

    return false;
}

void CLineMgr::Save_Line()
{
    //HANDLE      hFile = CreateFile(L"../Data/Line.dat",      // 파일의 경로
    HANDLE      hFile = CreateFile(m_szFileName,      // 파일의 경로
        GENERIC_WRITE,   // 개방 파일의 모드(GENERIC_READ : 읽기 전용 모드)
        NULL, // 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 열려할 때 허가할 것인가, NULL이면 공유하지 않겠다.
        NULL, // 보안속성, NULL인 경우 기본 보안 상태
        CREATE_ALWAYS,  // 파일 생성 방식, CREATE_ALWAYS : 파일이 없다면 생성, 파일이 있는 경우 덮어 쓰기, OPEN_EXITING : 파일이 있을 경우에만 열기
        FILE_ATTRIBUTE_NORMAL, // 파일 속성 : FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반적인 파일상태 
        NULL); // 생성될 파일의 속성을 제공할 템플릿 파일, 사용하지 않기 때문에 NULL

    if (INVALID_HANDLE_VALUE == hFile)
    {
        MessageBox(g_hWnd, L"개방 실패", _T("실패"), MB_OK);
        return;
    }

    DWORD      dwByte = 0;
    for (size_t i = 0; i < LINE_END; i++) {
        for (auto& iter : m_LineList[i])
        {
            WriteFile(hFile, (iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
        }
    }   // 땅 라인과 벽 라인 때문에 리스트 배열로 구분.

    CloseHandle(hFile);
    MessageBox(g_hWnd, L"저장 성공", _T("성공"), MB_OK);

}

void CLineMgr::Load_Line()
{
    Release();

    //HANDLE      hFile = CreateFile(L"../Data/Line.dat",      // 파일의 경로
    HANDLE      hFile = CreateFile(m_szFileName,      // 파일의 경로
        GENERIC_READ,   // 개방 파일의 모드(GENERIC_READ : 읽기 전용 모드)
        NULL, // 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 열려할 때 허가할 것인가, NULL이면 공유하지 않겠다.
        NULL, // 보안속성, NULL인 경우 기본 보안 상태
        OPEN_EXISTING,  // 파일 생성 방식, CREATE_ALWAYS : 파일이 없다면 생성, 파일이 있는 경우 덮어 쓰기, OPEN_EXITING : 파일이 있을 경우에만 열기
        FILE_ATTRIBUTE_NORMAL, // 파일 속성 : FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반적인 파일상태 
        NULL); // 생성될 파일의 속성을 제공할 템플릿 파일, 사용하지 않기 때문에 NULL

    if (INVALID_HANDLE_VALUE == hFile)
    {
        MessageBox(g_hWnd, L"개방 실패", _T("실패"), MB_OK);
        return;
    }

    DWORD      dwByte = 0;
    LINE      tInfo{};

    while (true)
    {
        ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

        if (0 == dwByte)
            break;

        //m_LineList.push_back(new CLine(tInfo));
        m_TempLine.push_back(new CLine(tInfo));
    }

    CloseHandle(hFile);

    for (auto& iter : m_TempLine) {
        if (iter->Get_Info()->m_LineID==WALLLINE) {
            m_LineList[WALLLINE].push_back(iter);
        }
        else if (iter->Get_Info()->m_LineID==GROUNDLINE) {
            m_LineList[GROUNDLINE].push_back(iter);
            //m_WallLine.push_back(iter);
        }
    }

    /*for_each(m_TempLine.begin(), m_TempLine.end(), CDeleteObj());
    m_TempLine.clear();*/
    m_TempLine.clear();

    MessageBox(g_hWnd, L"불러오기 성공", _T("성공"), MB_OK);
}


void CLineMgr::Initialize()
{
    //// 일자 땅 생성
    //m_tLintPoint[0].fX = -100.f;
    //m_tLintPoint[0].fY = 500.f;

    //m_tLintPoint[1].fX = 300.f;
    //m_tLintPoint[1].fY = 500.f;

    //LINE   tInfo{ m_tLintPoint[0], m_tLintPoint[1] };
    //m_LineList.push_back(new CLine(tInfo));
}

int CLineMgr::Update()
{
    POINT   pt{};

    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScollX();
    pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScollY();

    // 선 그리기
    if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
    {
        if (m_bIsDraw)
        {
            if ((!m_tLintPoint[0].fX) && !(m_tLintPoint[0].fY))
            {
                m_tLintPoint[0].fX = float(pt.x);
                m_tLintPoint[0].fY = float(pt.y);
                //fStraightY = m_tLintPoint[0].fY;
            }
            else {
                m_tLintPoint[1].fX = float(pt.x);
                m_tLintPoint[1].fY = float(pt.y);

                LINE	tInfo{ m_tLintPoint[0], m_tLintPoint[1],m_LineID };
                if (m_LineID == WALLLINE) {
                    m_LineList[WALLLINE].push_back(new CLine(tInfo));
                }
                else if (m_LineID == GROUNDLINE) {
                    m_LineList[GROUNDLINE].push_back(new CLine(tInfo));
                }

                m_tLintPoint[0].fX = m_tLintPoint[1].fX;
                m_tLintPoint[0].fY = m_tLintPoint[1].fY;
            }

            // 쉬프트키 누르면 대각선 그리기
            //else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LSHIFT))
            //{
            //    m_tLintPoint[1].fX = float(pt.x);
            //    m_tLintPoint[1].fY = float(pt.y);
            //    //m_tLintPoint[1].fY = m_tLintPoint[0].fY;

            //    LINE   tInfo{ m_tLintPoint[0], m_tLintPoint[1] };
            //    m_LineList.push_back(new CLine(tInfo));

            //    m_tLintPoint[0].fX = m_tLintPoint[1].fX;
            //    m_tLintPoint[0].fY = m_tLintPoint[1].fY;
            //}
            //// 아니면 일직선 그리기
            //else
            //{
            //    m_tLintPoint[1].fX = float(pt.x);
            //    //m_tLintPoint[1].fY = float(pt.y);
            //    m_tLintPoint[1].fY = m_tLintPoint[0].fY;

            //    LINE   tInfo{ m_tLintPoint[0], m_tLintPoint[1] };
            //    m_LineList.push_back(new CLine(tInfo));

            //    m_tLintPoint[0].fX = m_tLintPoint[1].fX;
            //    m_tLintPoint[0].fY = m_tLintPoint[1].fY;
            //}
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Q')) {
        m_LineID = WALLLINE;
    }
    else if (CKeyMgr::Get_Instance()->Key_Down('W')) {
        m_LineID = GROUNDLINE;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('D'))
    {
        m_bIsDraw = true;
        //m_bDelete = false;

        // 다시 그리기 시작하면 이 점은 시작점이 된다. (이전의 끝 점이 되어선 안됨)
        // 끊어 그리기
        m_tLintPoint[0].fX = NULL;
        m_tLintPoint[0].fY = NULL;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Z')) {

        if (m_LineID == WALLLINE) {
            if (m_LineList[WALLLINE].empty())
                return 0;


            Safe_Delete(m_LineList[WALLLINE].back());
            m_LineList[WALLLINE].pop_back();
            
        }
        else if (m_LineID == GROUNDLINE) {
            if (m_LineList[GROUNDLINE].empty())
                return 0;

            Safe_Delete(m_LineList[GROUNDLINE].back());
            m_LineList[GROUNDLINE].pop_back();
        }
    }
    // 선 지우기
    //if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
    //{
    //    if (m_bDelete)
    //    {
    //        if ((!m_tLintPoint[0].fX) && !(m_tLintPoint[0].fY))
    //        {
    //            m_tLintPoint[0].fX = float(pt.x);
    //            m_tLintPoint[0].fY = float(pt.y);
    //            //fStraightY = m_tLintPoint[0].fY;
    //        }
    //        else
    //        {
    //            m_tLintPoint[1].fX = float(pt.x);
    //            m_tLintPoint[1].fY = float(pt.y);
    //            //m_tLintPoint[1].fY = m_tLintPoint[0].fY;

    //            LINE   tInfo{ m_tLintPoint[0], m_tLintPoint[1] };
    //            //m_LineList.push_back(new CLine(tInfo));
    //            m_LineList.pop_back();

    //            m_tLintPoint[0].fX = m_tLintPoint[1].fX;
    //            m_tLintPoint[0].fY = m_tLintPoint[1].fY;
    //        }
    //    }
    //}

    //if (CKeyMgr::Get_Instance()->Key_Pressing('F'))
    //{
    //    m_bIsDraw = false;
    //    m_bDelete = true;

    //    // 다시 그리기 시작하면 이 점은 시작점이 된다. (이전의 끝 점이 되어선 안됨)
    //    // 끊어 그리기
    //    m_tLintPoint[0].fX = NULL;
    //    m_tLintPoint[0].fY = NULL;
    //}

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
        CScrollMgr::Get_Instance()->Set_ScrollX(20.f);

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
        CScrollMgr::Get_Instance()->Set_ScrollX(-20.f);

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
        CScrollMgr::Get_Instance()->Set_ScrollY(20.f);

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
        CScrollMgr::Get_Instance()->Set_ScrollY(-20.f);

    if (CKeyMgr::Get_Instance()->Key_Down('1')) {
        m_szFileName = L"../Data/Line_1.dat";
        Save_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('2')) {
        m_szFileName = L"../Data/Line_2.dat";
        Save_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('3')) {
        m_szFileName = L"../Data/Line_3.dat";
        Save_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('4')) {
        m_szFileName = L"../Data/Line_4.dat";
        Save_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('5')) {
        m_szFileName = L"../Data/Line_5.dat";
        Save_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('6')) {
        m_szFileName = L"../Data/Line_6.dat";
        Save_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('7')) {
        m_szFileName = L"../Data/Line_7.dat";
        Save_Line();
    }



    if (CKeyMgr::Get_Instance()->Key_Down('a')) {
        m_szFileName = L"../Data/Line_1.dat";
        Load_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('s')) {
        m_szFileName = L"../Data/Line_2.dat";
        Load_Line();
    }
    
    if (CKeyMgr::Get_Instance()->Key_Down('d')) {
        m_szFileName = L"../Data/Line_3.dat";
        Load_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('f')) {
        m_szFileName = L"../Data/Line_4.dat";
        Load_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('g')) {
        m_szFileName = L"../Data/Line_5.dat";
        Load_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('h')) {
        m_szFileName = L"../Data/Line_6.dat";
        Load_Line();
    }
    if (CKeyMgr::Get_Instance()->Key_Down('j')) {
        m_szFileName = L"../Data/Line_7.dat";
        Load_Line();
    }
    

    /*if (CKeyMgr::Get_Instance()->Key_Down('A'))
       Save_Line();

    if (CKeyMgr::Get_Instance()->Key_Down('S'))
       Load_Line();*/

    /*if (CKeyMgr::Get_Instance()->Key_Down('1'))
    {
        m_szFileName = L"../Data/Line_1.dat";
        Save_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('2'))
    {
        m_szFileName = L"../Data/Line_2.dat";
        Save_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('3'))
    {
        m_szFileName = L"../Data/Line_3.dat";
        Save_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('4'))
    {
        m_szFileName = L"../Data/Line_4.dat";
        Save_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Q'))
    {
        m_szFileName = L"../Data/Line_1.dat";
        Load_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('W'))
    {
        m_szFileName = L"../Data/Line_2.dat";
        Load_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('E'))
    {
        m_szFileName = L"../Data/Line_3.dat";
        Load_Line();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('R'))
    {
        m_szFileName = L"../Data/Line_4.dat";
        Load_Line();
    }*/

    return 0;
}

void CLineMgr::Late_Update()
{
}

void CLineMgr::Render(HDC hDC)
{
    


    for (size_t i = 0; i < LINE_END; i++) {
        for (auto& iter : m_LineList[i])
            iter->Render(hDC);
    }

    const TCHAR* szBuff = TEXT("");

    if (m_bIsDraw)
    {
        szBuff = TEXT("선 그리기 on");
        TextOut(hDC, 20, 20, szBuff, lstrlen(szBuff));
    }else if (m_bDelete)
    {
        szBuff = TEXT("선 지우기 on");
        TextOut(hDC, 20, 20, szBuff, lstrlen(szBuff));
    }

    const TCHAR* szType = TEXT("");

    if (m_LineID == WALLLINE) {
        szBuff = TEXT("벽 라인 그리기");
        TextOut(hDC, 40, 40, szBuff, lstrlen(szBuff));
    }
    else if (m_LineID == GROUNDLINE) {
        szBuff = TEXT("땅 라인 그리기");
        TextOut(hDC, 40, 40, szBuff, lstrlen(szBuff));
    }
    


}

void CLineMgr::Release()
{
    for (size_t i = 0; i < LINE_END; i++) {
        for_each(m_LineList[i].begin(), m_LineList[i].end(), CDeleteObj());
        m_LineList[i].clear();
    }

    /*for_each(m_TempLine.begin(), m_TempLine.end(), CDeleteObj());
    m_TempLine.clear();*/
}