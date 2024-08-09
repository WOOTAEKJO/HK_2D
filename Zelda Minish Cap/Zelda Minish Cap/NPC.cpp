#include "NPC.h"
#include "ObjMgr.h"
#include "Text.h"

CNPC::CNPC() :m_ePreState(STATE_END), m_eCurState(STATE_END), m_bTalk(false),
m_nextTalk(0)
{
}

CNPC::~CNPC()
{
}

void CNPC::Create_Text(int _TextNum)
{
	if (!m_bTextBox) {
		if (m_Textvec[_TextNum]) {
			m_bTextBox = new CText;
			m_bTextBox->Set_Pos(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
			dynamic_cast<CText*>(m_bTextBox)->Set_Text(m_Textvec[_TextNum]);
			m_bTextBox->Initialize();
			CObjMgr::Get_Instance()->Add_Object(STRUCT, m_bTextBox);
		}
	}
}

void CNPC::Save_Text()
{
	const TCHAR* str = TEXT("���� �� �����");

	m_Textvec.push_back(L"���� �� �����");  // 0
	m_Textvec.push_back(L"����");  // 1
	m_Textvec.push_back(L"���� óġ"); // 2
	m_Textvec.push_back(L"�����߾�"); // 3
	m_Textvec.push_back(L"���� �� ��"); //4
	m_Textvec.push_back(L"�����̳�"); //5
	m_Textvec.push_back(L"�̹� �����"); //6
	m_Textvec.push_back(L"���� �ƴϾ�"); //7
	m_Textvec.push_back(L"�������� ���ƿ�"); //8
	m_Textvec.push_back(L"�� �̰ܼ� ���ƿ�"); //9
	m_Textvec.push_back(L"�� ������ ����.."); //10
	m_Textvec.push_back(L"���� ���� ������ ��������"); //11
	m_Textvec.push_back(L"�ٵ� ����߾��"); //12

}
