
#include "Room3.h"
#include "Room2.h"
#include "BossRoom.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

bool CRoom3::Init()
{
	if (!CRoomBase::Init())
		return false;

	CMapManager::GetInst()->SetMap(this, 3);
	LoadMapObject();

	CreatePlayer(Vector2::DOWN);

	SetDoor(DD_TOP, DT_NORMAL);
	SetDoor(DD_LEFT, DT_NORMAL);

#ifdef _DEBUG
	m_bClearRoom = true;
#endif // _DEBUG

	return true;
}

void CRoom3::Start()
{
	CRoomBase::Start();
}

bool CRoom3::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom3::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom3::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom3::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

void CRoom3::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CBossRoom>(Vector2::LEFT);
		break;
	case DD_TOP:
		MoveRoom<CRoom2>(Vector2::UP);
		break;
	}
}

CRoom3::CRoom3()
{
}

CRoom3::~CRoom3()
{
}
