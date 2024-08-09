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
	// ã�Ƽ� ������ �̹��� map���ٰ� �߰�
}

HDC CBmpMgr::Find_Img(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
	// ã�Ƽ� �� Ű�� �ش��ϴ� ��ü�� DC�� �����´�.
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
