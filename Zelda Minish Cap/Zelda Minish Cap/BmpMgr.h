#pragma once
#include "BitMap.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();
public:
	static CBmpMgr* Get_Instance() {
		if (!m_Instance) {
			m_Instance = new CBmpMgr;
		}
		return m_Instance;
	}
	static void Delete_Instance() {
		if (m_Instance) {
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
public:
	void Insert_Bmp(const TCHAR* pFilepath, const TCHAR* pImgKey);
	HDC Find_Img(const TCHAR* pImgKey);
	/*Gdiplus::Bitmap* Find_Img(const TCHAR* pImgKey);
	CBitMap* Find_CBitMap(const TCHAR* pImaKey);*/
	void Release();
private:
	static CBmpMgr* m_Instance;

	map<const TCHAR*, CBitMap*> m_mapBit;
};

