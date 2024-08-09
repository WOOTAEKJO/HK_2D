#include "Character.h"
#include "Component.h"
#include "LineMgr.h"
#include "SoundMgr.h"

float g_fSound_cc = 1.f;

CCharacter::CCharacter():m_bJump(false), m_fJump_Power(0.f), m_fJump_Angle(0.f)
, m_iAdditionJump_MaxCount(0), m_iAdditionJump_Count(0),m_HP(0),m_Soul(0)
{
}

CCharacter::~CCharacter()
{

}

void CCharacter::Jump()
{
	float fY = INFINITY;

	bool bLineCol = CLineMgr::Get_Instance()->CollisionLine_Ground(m_tInfo, &fY);

	if (0.f < (fY)-m_tInfo.fY)
		m_bJump = true;

	if (m_bJump)
	{
		if (bLineCol && (fY < m_tInfo.fY - m_fSpeed_Vertical) && m_fSpeed_Vertical < 0.f)
		{
			m_bJump = false;
			m_tInfo.fY = fY;
			m_iAdditionJump_Count = m_iAdditionJump_MaxCount;
		}
		else
		{
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.044f * G);



		}
	}
	else if (bLineCol)
	{
		
		m_tInfo.fY = fY;
		m_fSpeed_Vertical = 0.f;

	}
	else
	{
		m_tInfo.fY -= m_fSpeed_Vertical;
		m_fSpeed_Vertical -= (0.044f * G);

	}
}

void CCharacter::JumpEX()
{
	float fY = INFINITY;
	CLine m_pTarger;

	bool bLineCol = CLineMgr::Get_Instance()->CollisionLine_GroundEX(m_tInfo,m_fColC, &m_pTarger,&fY);

	if (0.f < (fY)-m_tInfo.fY)
		m_bJump = true;

	if (m_bJump)
	{
		if (bLineCol && (fY < m_tInfo.fY - m_fSpeed_Vertical) && m_fSpeed_Vertical < 0.f)
		{
			m_bJump = false;
			m_tInfo.fY = fY;
			m_iAdditionJump_Count = m_iAdditionJump_MaxCount;
		}
		else
		{
			m_tInfo.fY -= m_fSpeed_Vertical;
			m_fSpeed_Vertical -= (0.044f * G);



		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
		m_fSpeed_Vertical = 0.f;

	}
	else
	{
		m_tInfo.fY -= m_fSpeed_Vertical;
		m_fSpeed_Vertical -= (0.044f * G);

	}
}

void CCharacter::Collision()
{
}
