
#include "Room2.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom2::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetMap("Room", m_iRoomNum);
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);

	SetDoor(DD_LEFT, false);
	SetDoor(DD_BOTTOM, false);

	return true;
}

void CRoom2::Start()
{
	CRoomBase::Start();
}

bool CRoom2::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom2::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom2::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom2::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

CRoom2::CRoom2()
{
}

CRoom2::~CRoom2()
{
}
