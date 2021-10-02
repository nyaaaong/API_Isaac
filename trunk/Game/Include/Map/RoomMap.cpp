#include "RoomMap.h"
#include "RoomMapObj.h"
#include "../Resource/ResourceManager.h"

bool CRoomMap::Init()
{
	if (m_bIsSpecial)
	{
		switch (m_eSpecialRoomType)
		{
		case ESpecial_RoomType::Start:
			m_pBackGround = CResourceManager::GetInst()->FindTexture("StartRoom_BackGround");
			break;
		case ESpecial_RoomType::Item:
			break;
		case ESpecial_RoomType::Boss:
			break;
		}
	}

	else
		m_pBackGround = CResourceManager::GetInst()->FindTexture("BackGround");

	return true;
}

void CRoomMap::Start()
{
}

void CRoomMap::Update(float fTime)
{
	std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(fTime);
	}
}

void CRoomMap::PostUpdate(float fTime)
{
	std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(fTime);
	}
}

void CRoomMap::Render(HDC hDC)
{
	if (m_pBackGround)
		m_pBackGround->Render(hDC, Vector2(), Vector2(), Vector2(1280.f, 720.f));

	std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC);
	}
}

CRoomMap::CRoomMap()	:
	m_bEnable(true),
	m_bActive(true),
	m_iRoomNum(0),
	m_pScene(nullptr),
	m_bIsSpecial(false),
	m_eSpecialRoomType(ESpecial_RoomType::Start)
{
}

CRoomMap::~CRoomMap()
{
	std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}
