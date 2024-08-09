#pragma once
#include "framework.h"
class CBitMap
{
public:
	CBitMap();
	~CBitMap();
public:
	HDC			Get_MemDC() { return m_hMemDC; }

	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release();

	//Gdiplus::Bitmap* Get_Image() { return m_hBitMap; }
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldBmp;

	/*Gdiplus::Bitmap* m_hBitMap;
	Gdiplus::Bitmap* m_hOldBmp;*/

};

