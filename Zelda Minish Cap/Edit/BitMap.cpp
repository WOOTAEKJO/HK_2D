#include "BitMap.h"

CBitMap::CBitMap()
{
}

CBitMap::~CBitMap()
{
	Release();
}

void CBitMap::Load_Bmp(const TCHAR* pFilePath)
{
	HDC hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

	/*m_hBitMap = Gdiplus::Bitmap::FromFile(pFilePath);
	m_hOldBmp = (Gdiplus::Bitmap*)SelectObject(m_hMemDC, m_hBitMap);*/
}

void CBitMap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
