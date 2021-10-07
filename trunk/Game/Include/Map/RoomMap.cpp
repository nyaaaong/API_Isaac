#include "RoomMap.h"
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
			m_pBackGround = CResourceManager::GetInst()->FindTexture("BackGround");
			break;
		}
	}

	else
		m_pBackGround = CResourceManager::GetInst()->FindTexture("BackGround");

	return true;
}

void CRoomMap::Update(float fTime)
{
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(fTime);
	}
}

void CRoomMap::PostUpdate(float fTime)
{
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(fTime);
	}
}

void CRoomMap::Render(HDC hDC)
{
	if (m_pBackGround)
		m_pBackGround->Render(hDC, Vector2(), Vector2(), Vector2(1280.f, 720.f));

	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

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
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_RoomObjList.clear();
}
