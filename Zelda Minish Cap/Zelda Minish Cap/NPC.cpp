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
	const TCHAR* str = TEXT("보스 좀 잡아줘");

	m_Textvec.push_back(L"보스 좀 잡아줘");  // 0
	m_Textvec.push_back(L"고마워");  // 1
	m_Textvec.push_back(L"벌레 처치"); // 2
	m_Textvec.push_back(L"수고했어"); // 3
	m_Textvec.push_back(L"아직 못 들어가"); //4
	m_Textvec.push_back(L"아직이네"); //5
	m_Textvec.push_back(L"이미 얻었네"); //6
	m_Textvec.push_back(L"아직 아니야"); //7
	m_Textvec.push_back(L"강해져서 돌아와"); //8
	m_Textvec.push_back(L"꼭 이겨서 돌아와"); //9
	m_Textvec.push_back(L"벽 점프가 없네.."); //10
	m_Textvec.push_back(L"저기 위에 벌집을 제거해줘"); //11
	m_Textvec.push_back(L"다들 고생했어요"); //12

}
