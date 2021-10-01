#include "Map.h"
#include "MapObj.h"
#include "../Resource/ResourceManager.h"

bool CMap::Init()
{
	m_pBackGround = CResourceManager::GetInst()->FindTexture("BackGround");

	return true;
}

void CMap::Start()
{
}

void CMap::Update(float fTime)
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(fTime);
	}
}

void CMap::PostUpdate(float fTime)
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(fTime);
	}
}

void CMap::Render(HDC hDC)
{
	if (m_pBackGround)
		m_pBackGround->Render(hDC, Vector2(), Vector2(), Vector2(1280.f, 720.f));

	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC);
	}
}

CMap::CMap()	:
	m_bEnable(true),
	m_bActive(true),
	m_iRoomNum(1),
	m_pScene(nullptr)
{
}

CMap::~CMap()
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}
