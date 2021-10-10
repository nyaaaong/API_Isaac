
#include "Room2.h"
#include "Room3.h"
#include "StartRoom.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

bool CRoom2::Init()
{
	if (!CRoomBase::Init())
		return false;

	CMapManager::GetInst()->SetMap(this, 2);
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);

	SetDoor(DD_LEFT, false);
	SetDoor(DD_BOTTOM, false);

#ifdef _DEBUG
	m_bClearRoom = true;
#endif // _DEBUG

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

void CRoom2::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CStartRoom>(Vector2::LEFT);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom3>(Vector2::DOWN);
		break;
	}
}

CRoom2::CRoom2()
{
}

CRoom2::~CRoom2()
{
}
