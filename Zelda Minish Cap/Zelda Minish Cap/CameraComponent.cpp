#include "CameraComponent.h"
#include "Character.h"

CCameraComponent::CCameraComponent()
{
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::Initialize()
{
}

void CCameraComponent::Update()
{
	if (m_owner == nullptr)
		return;

	float fx = m_owner->Get_Info()->fX;
	float fy = m_owner->Get_Info()->fY;

	if (fx <= 400.f)
		fx = 400.f;
	else if (fx >= 1920 - 400.f)
		fx = 1920 - 400.f;

	if (fy <= 300.f)
		fy = 300.f;
	else if (fy >= 1080 - 300.f)
		fy = 1080 - 300.f;
	
}

void CCameraComponent::Render(HDC hdc)
{
}
