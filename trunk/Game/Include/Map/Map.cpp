#include "Map.h"

bool CMap::Init()
{
	//SetTexture("Map", TEXT("Room/Room.bmp"));
	//SetZOrder(EZOrder::BackGround);

	return true;
}

void CMap::Start()
{
}

void CMap::Update(float fTime)
{
}

void CMap::PostUpdate(float fTime)
{
}

void CMap::PrevRender()
{
}

void CMap::Render(HDC hDC)
{
}

CMap::CMap()	:
	m_pScene(nullptr)
{
	//m_eObjectType = EObjectType::Map;
}

CMap::~CMap()
{
}
