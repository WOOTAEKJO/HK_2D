#include "TileMgr.h"
#include "ObjFactory.h"
#include "ScrollMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {

			float	fX = (float)(TILECX >> 1) + (TILECX * j);
			float	fY = (float)(TILECY >> 1) + (TILECY * i);

			CObj* pObj = CObjFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pObj);
		}
	}
}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile) {
		iter->Update();
	}
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile) {
		iter->Late_Update();
	}
}

void CTileMgr::Render(HDC hDC)
{
	int iCullX = (int)abs(CScrollMgr::Get_Instance()->Get_ScollX() / TILECX);
	int iCullY = (int)abs(CScrollMgr::Get_Instance()->Get_ScollY() / TILECY);

	int	iMaxX = iCullX + WINCX / TILECX + 2;
	int	iMaxY = iCullY + WINCY / TILECY + 2;

	for (int i = iCullY; i < iMaxY; ++i)
	{
		for (int j = iCullX; j < iMaxX; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || size_t(iIndex) >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

	WCHAR _text[100];
	_stprintf_s(_text, L" tile x : %f, tile y : %f", m_vecTile.back()->Get_Info()->fX, m_vecTile.back()->Get_Info()->fY);
	TextOutW(hDC, 0, 60, _text, lstrlen(_text));
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](CObj* n) {
		
		if (n) {
			delete n;
			n = nullptr;
		}
		});

	m_vecTile.clear();

	for_each(m_WallTile.begin(), m_WallTile.end(), [](CObj* n) {

		if (n) {
			delete n;
			n = nullptr;
		}
		});
	m_WallTile.clear();
}

void CTileMgr::Picking_Tile(POINT pt, TILEOPTION _iDrawID, TILEOPTION _iOption)
{
	int		x = pt.x / TILECX;
	int		y = pt.y / TILECY;

	int		iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_ID(_iDrawID, _iOption);
}

void CTileMgr::Save_Tile()
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, (iter->Get_Info()), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Tile Save", L"성공", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	INFO	tInfo{};
	TILEOPTION		iDrawID = NON;
	TILEOPTION	iOption = NON;
	DWORD	dwByte = 0;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(TILEOPTION), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(TILEOPTION), &dwByte, NULL);

		if (0 == dwByte)
			break;

		if (iDrawID == WALL) {
			CObj* _Obj= CObjFactory<CTile>::Create(tInfo.fX, tInfo.fY);
			dynamic_cast<CTile*>(_Obj)->Set_ID(iDrawID, iOption);
			m_WallTile.push_back(_Obj);
		}

			CObj* pObj = CObjFactory<CTile>::Create(tInfo.fX, tInfo.fY);
			dynamic_cast<CTile*>(pObj)->Set_ID(iDrawID, iOption);
			m_vecTile.push_back(pObj);
		
		
			
		

		
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
}
