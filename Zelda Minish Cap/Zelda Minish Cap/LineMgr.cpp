#include "LineMgr.h"
#include "KeyMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr():m_LineID(LINE_END), m_CollDirCheck(DIR_END)
{
	ZeroMemory(m_tLintPoint, sizeof(m_tLintPoint));
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	Load_Line();
}

int CLineMgr::Update()
{
	//POINT	pt{};

	//GetCursorPos(&pt);
	//ScreenToClient(g_hWnd, &pt);

	////pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScollX();

	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	//{
	//	if ((!m_tLintPoint[0].fX) && !(m_tLintPoint[0].fY))
	//	{
	//		m_tLintPoint[0].fX = float(pt.x);
	//		m_tLintPoint[0].fY = float(pt.y);
	//	}
	//	else
	//	{
	//		m_tLintPoint[1].fX = float(pt.x);
	//		m_tLintPoint[1].fY = float(pt.y);

	//		LINE	tInfo{ m_tLintPoint[0], m_tLintPoint[1] };
	//		m_LineList.push_back(new CLine(tInfo));

	//		m_tLintPoint[0].fX = m_tLintPoint[1].fX;
	//		m_tLintPoint[0].fY = m_tLintPoint[1].fY;
	//	}
	//}

	//if (CKeyMgr::Get_Instance()->Key_Down('S'))
	//	Load_Line();

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
}

void CLineMgr::Release()
{
	for (size_t i = 0; i < LINE_END; i++) {
		for_each(m_LineList[i].begin(), m_LineList[i].end(), CDeleteObj());
		m_LineList[i].clear();
	}
}

bool CLineMgr::CollisionLine_Ground(INFO& _rInfo, float* _pY)
{
	if (m_LineList[GROUNDLINE].empty())
		return false;

	list<CLine*>		TargetList;
	CLine* pTarget = nullptr;
	// ���� �Ʒ��� �ִ� ���� ���� ���� ����
	float	fBottomY = -INFINITY;
	float	fHeight =  _rInfo.fCY * 0.5f;
	//float	fHeight = 0.f;// _rInfo.fCY * 0.5f;

	// Ư�� ������ x�� ���̿� �ִ� ������ ã��
	for (auto& line : m_LineList[GROUNDLINE])
	{
		if (line->Get_Info()->tLpoint.fX <= _rInfo.fX && line->Get_Info()->tRpoint.fX > _rInfo.fX ||
			line->Get_Info()->tRpoint.fX <= _rInfo.fX && line->Get_Info()->tLpoint.fX > _rInfo.fX)
		{
			TargetList.push_back(line);

			// ���⼭ fBaseH�� �ʱ� ���̸� ���� ũ�� �����ϱ���������
			// �߽���ǥ �ٷ� �Ʒ��� ���� ���� ����� �ƴ�.
			if (fBottomY < line->Get_Info()->tLpoint.fY - fHeight)
			{
				fBottomY = line->Get_Info()->tLpoint.fY - fHeight;
				pTarget = line;
			}

			if (fBottomY < line->Get_Info()->tRpoint.fY - fHeight)
			{
				fBottomY = line->Get_Info()->tRpoint.fY - fHeight;
				pTarget = line;
			}
		}
	}

	// �Ʒ��� �ش��ϴ� ������ ������ ����Ʈ�� üũ�Ѵ�.
	if (TargetList.empty())
		return false;

	// ���� ����Ʈ �߿��� ���� ����� ������ ã�� �ɷ�����.
	for (auto& line : TargetList)
	{
		float	x1 = line->Get_Info()->tLpoint.fX;
		float	x2 = line->Get_Info()->tRpoint.fX;

		float	y1 = line->Get_Info()->tLpoint.fY - fHeight;
		float	y2 = line->Get_Info()->tRpoint.fY - fHeight;

		float	fTargetY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fX - x1) + y1;
		float	fPrevTargetY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fPrevX - x1) + y1;

		// �ɷ����� �ڵ�
		if (fTargetY <= fBottomY && fTargetY >= _rInfo.fY)
		{
			fBottomY = fTargetY;

			pTarget = line;
		}

		else if (fPrevTargetY <= fBottomY && fPrevTargetY > fTargetY &&
			(_rInfo.fY > y1 && _rInfo.fY < y2) || (_rInfo.fY > y2 && _rInfo.fY < y1))
		{
			fBottomY = fTargetY;

			pTarget = line;
		}
	}

	if (!pTarget)
		return false;


	//�߰�) Ÿ�� ������ ĳ���� ���̿� ���̰� ũ�� false
	if (abs(pTarget->Get_Info()->tLpoint.fY - _rInfo.fY) > _rInfo.fCY)
		return false;


	float	x1 = pTarget->Get_Info()->tLpoint.fX;
	float	x2 = pTarget->Get_Info()->tRpoint.fX;

	float	y1 = pTarget->Get_Info()->tLpoint.fY - fHeight;
	float	y2 = pTarget->Get_Info()->tRpoint.fY - fHeight;

	// ���� * ��ȯ�� �ʺ� + ���� ���� y��
	*_pY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fX - x1) + y1;

	return true;
}

bool CLineMgr::CollisionLine_GroundEX(INFO& _rInfo, fPOINT _ColC,CLine* _pTarget, float* _pY)
{
	if (m_LineList[GROUNDLINE].empty())
		return false;

	list<CLine*>		TargetList;
	CLine* pTarget = nullptr;
	// ���� �Ʒ��� �ִ� ���� ���� ���� ����
	float	fBottomY = -INFINITY;
	//float	fHeight = _rInfo.fCY * 0.5f;
	float	fHeight = _ColC.y * 0.5f;
	//float	fHeight = 0.f;// _rInfo.fCY * 0.5f;

	// Ư�� ������ x�� ���̿� �ִ� ������ ã��
	for (auto& line : m_LineList[GROUNDLINE])
	{
		if (line->Get_Info()->tLpoint.fX <= _rInfo.fX && line->Get_Info()->tRpoint.fX > _rInfo.fX ||
			line->Get_Info()->tRpoint.fX <= _rInfo.fX && line->Get_Info()->tLpoint.fX > _rInfo.fX)
		{
			TargetList.push_back(line);

			// ���⼭ fBaseH�� �ʱ� ���̸� ���� ũ�� �����ϱ���������
			// �߽���ǥ �ٷ� �Ʒ��� ���� ���� ����� �ƴ�.
			if (fBottomY < line->Get_Info()->tLpoint.fY - fHeight)
			{
				fBottomY = line->Get_Info()->tLpoint.fY - fHeight;
				pTarget = line;
			}

			if (fBottomY < line->Get_Info()->tRpoint.fY - fHeight)
			{
				fBottomY = line->Get_Info()->tRpoint.fY - fHeight;
				pTarget = line;
			}
		}
	}

	// �Ʒ��� �ش��ϴ� ������ ������ ����Ʈ�� üũ�Ѵ�.
	if (TargetList.empty())
		return false;

	// ���� ����Ʈ �߿��� ���� ����� ������ ã�� �ɷ�����.
	for (auto& line : TargetList)
	{
		float	x1 = line->Get_Info()->tLpoint.fX;
		float	x2 = line->Get_Info()->tRpoint.fX;

		float	y1 = line->Get_Info()->tLpoint.fY - fHeight;
		float	y2 = line->Get_Info()->tRpoint.fY - fHeight;

		float	fTargetY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fX - x1) + y1;
		float	fPrevTargetY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fPrevX - x1) + y1;

		// �ɷ����� �ڵ�
		if (fTargetY <= fBottomY && fTargetY >= _rInfo.fY)
		{
			fBottomY = fTargetY;

			pTarget = line;
		}

		else if (fPrevTargetY <= fBottomY && fPrevTargetY > fTargetY &&
			(_rInfo.fY > y1 && _rInfo.fY < y2) || (_rInfo.fY > y2 && _rInfo.fY < y1))
		{
			fBottomY = fTargetY;

			pTarget = line;
		}
	}

	if (!pTarget)
		return false;


	//�߰�) Ÿ�� ������ ĳ���� ���̿� ���̰� ũ�� false
	if (abs(pTarget->Get_Info()->tLpoint.fY - _rInfo.fY) > _ColC.y)
		return false;


	float	x1 = pTarget->Get_Info()->tLpoint.fX;
	float	x2 = pTarget->Get_Info()->tRpoint.fX;

	float	y1 = pTarget->Get_Info()->tLpoint.fY - fHeight;
	float	y2 = pTarget->Get_Info()->tRpoint.fY - fHeight;

	// ���� * ��ȯ�� �ʺ� + ���� ���� y��
	*_pY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fX - x1) + y1;

	_pTarget->Get_Info()->tLpoint.fX = pTarget->Get_Info()->tLpoint.fX;
	_pTarget->Get_Info()->tRpoint.fX = pTarget->Get_Info()->tRpoint.fX;

	return true;
}

bool CLineMgr::CollisionLine_Wall(RECT& _rInfo, fPOINT* _LP, fPOINT* _RP)
{
	if (m_LineList[WALLLINE].empty()) {
		m_CollDirCheck = DIR_END;
		return false;
	}

	for (auto& iter : m_LineList[WALLLINE]) {
		if (CheckLineIntersection(_rInfo.left, _rInfo.top, _rInfo.right, _rInfo.top, iter->Get_Info()->tLpoint.fX, iter->Get_Info()->tLpoint.fY,
			iter->Get_Info()->tRpoint.fX, iter->Get_Info()->tRpoint.fY)||
			CheckLineIntersection(_rInfo.right, _rInfo.top, _rInfo.right, _rInfo.bottom, iter->Get_Info()->tLpoint.fX, iter->Get_Info()->tLpoint.fY,
			iter->Get_Info()->tRpoint.fX, iter->Get_Info()->tRpoint.fY)||
			CheckLineIntersection(_rInfo.right, _rInfo.bottom, _rInfo.left, _rInfo.bottom, iter->Get_Info()->tLpoint.fX, iter->Get_Info()->tLpoint.fY,
			iter->Get_Info()->tRpoint.fX, iter->Get_Info()->tRpoint.fY)||
			CheckLineIntersection(_rInfo.left, _rInfo.bottom, _rInfo.left, _rInfo.top, iter->Get_Info()->tLpoint.fX, iter->Get_Info()->tLpoint.fY,
			iter->Get_Info()->tRpoint.fX, iter->Get_Info()->tRpoint.fY)) {

			_LP->x = iter->Get_Info()->tLpoint.fX;
			_LP->y = iter->Get_Info()->tLpoint.fY;

			_RP->x = iter->Get_Info()->tRpoint.fX;
			_RP->y = iter->Get_Info()->tRpoint.fY;

			return true;
		}
	}

	m_CollDirCheck = DIR_END;
	return false;
}

bool CLineMgr::CheckLineIntersection(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3, float _x4, float _y4)
{
	float den = (_x1 - _x2) * (_y3 - _y4) - (_y1 - _y2)*(_x3 - _x4);
	if (den == 0)
		return false;	//������ �����ϰų� ��ġ

	float t = ((_x1 - _x3) * (_y3 - _y4) - (_y1 - _y3) * (_x3 - _x4)) / den;
	float u = -((_x1 - _x2) * (_y1 - _y3) - (_y1 - _y2) * (_x1 - _x3)) / den;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
		return true;	// �� ������ �����ϴ� ���

	return false;	// �� ������ �������� �ʴ� ���
}

void CLineMgr::Load_Line()
{
	Release();

	//HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ������ ���
	//	GENERIC_READ,	// ���� ������ ���(GENERIC_READ : �б� ���� ���)
	//	NULL, // �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� �㰡�� ���ΰ�, NULL�̸� �������� �ʰڴ�.
	//	NULL, // ���ȼӼ�, NULL�� ��� �⺻ ���� ����
	//	OPEN_EXISTING,  // ���� ���� ���, CREATE_ALWAYS : ������ ���ٸ� ����, ������ �ִ� ��� ���� ����, OPEN_EXITING : ������ ���� ��쿡�� ����
	//	FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� : FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ����� ���ϻ��� 
	//	NULL); // ������ ������ �Ӽ��� ������ ���ø� ����, ������� �ʱ� ������ NULL

	//if (INVALID_HANDLE_VALUE == hFile)
	//{
	//	MessageBox(g_hWnd, L"���� ����", _T("����"), MB_OK);
	//	return;
	//}

	//DWORD		dwByte = 0;
	//LINE		tInfo{};

	//while (true)
	//{
	//	ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

	//	if (0 == dwByte)
	//		break;

	//	m_LineList.push_back(new CLine(tInfo));
	//}

	//CloseHandle(hFile);
	//MessageBox(g_hWnd, L"�ҷ����� ����", _T("����"), MB_OK);
}

void CLineMgr::Load_Line(STAGEID _stageid)
{
	Release();


	const TCHAR* szFileNmae = L"";

	if (_stageid == STAGE1) {
		szFileNmae= L"../Data/Line_1.dat";
	}
	else if (_stageid == STAGE2) {

		szFileNmae = L"../Data/Line_2.dat";

	}else if (_stageid == STAGE3) {

		szFileNmae = L"../Data/Line_3.dat";
	}
	else if (_stageid == STAGE4) {
		szFileNmae = L"../Data/Line_4.dat";
	}
	else if (_stageid == STAGE5) {
		szFileNmae = L"../Data/Line_5.dat";
	}
	else if (_stageid == STAGE6) {
		szFileNmae = L"../Data/Line_6.dat";
	}
	else if (_stageid == STAGE7) {
		szFileNmae = L"../Data/Line_7.dat";
	}


	//HANDLE      hFile = CreateFile(L"../Data/Line.dat",      // ������ ���
	HANDLE      hFile = CreateFile(szFileNmae,      // ������ ���
		GENERIC_READ,   // ���� ������ ���(GENERIC_READ : �б� ���� ���)
		NULL, // �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� �㰡�� ���ΰ�, NULL�̸� �������� �ʰڴ�.
		NULL, // ���ȼӼ�, NULL�� ��� �⺻ ���� ����
		OPEN_EXISTING,  // ���� ���� ���, CREATE_ALWAYS : ������ ���ٸ� ����, ������ �ִ� ��� ���� ����, OPEN_EXITING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� : FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ����� ���ϻ��� 
		NULL); // ������ ������ �Ӽ��� ������ ���ø� ����, ������� �ʱ� ������ NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"���� ����", _T("����"), MB_OK);
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
		if (iter->Get_Info()->m_LineID == WALLLINE) {
			m_LineList[WALLLINE].push_back(iter);
		}
		else if (iter->Get_Info()->m_LineID == GROUNDLINE) {
			m_LineList[GROUNDLINE].push_back(iter);
			//m_WallLine.push_back(iter);
		}
	}

	/*for_each(m_TempLine.begin(), m_TempLine.end(), CDeleteObj());
	m_TempLine.clear();*/
	m_TempLine.clear();

	//MessageBox(g_hWnd, L"�ҷ����� ����", _T("����"), MB_OK);
}

