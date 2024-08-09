#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_Instance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilepath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end()) {
		CBitMap* pBmp = new CBitMap;
		pBmp->Load_Bmp(pFilepath);

		m_mapBit.insert({ pImgKey ,pBmp });
	}
	// 찾아서 없으면 이미지 map에다가 추가
}

HDC CBmpMgr::Find_Img(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
	// 찾아서 그 키의 해당하는 객체의 DC를 가져온다.
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
