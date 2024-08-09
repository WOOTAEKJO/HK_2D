#include "BossTotem.h"
#include "BmpMgr.h"

CBossTotem::CBossTotem()
{
}

CBossTotem::~CBossTotem()
{
	Release();
}

void CBossTotem::Initialize()
{
	Set_Size(84.f,95.f);
}

int CBossTotem::Update()
{
	return 0;
}

void CBossTotem::Late_Update()
{
}

void CBossTotem::Render(HDC hDC)
{
}

void CBossTotem::Release()
{
}

void CBossTotem::Collision()
{
}
