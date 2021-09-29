#include "Map.h"
#include "../Scene/Scene.h"
#include "../Object/BackGround.h"

bool CMap::Init()
{
	m_pScene->CreateObject<CBackGround>("BackGround");

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
	m_pScene(nullptr),
	m_iZOrder(0),
	m_bEnable(true),
	m_bActive(true),
	m_iRoomNum(1),
	m_eObject(OBJ_ROCK)
{
}

CMap::~CMap()
{
}
