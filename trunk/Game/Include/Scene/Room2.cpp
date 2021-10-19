
#include "Room2.h"
#include "Room3.h"
#include "StartRoom.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom2::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(2);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_LEFT, DT_NORMAL);
	SetDoor(DD_BOTTOM, DT_NORMAL);

	return true;
}

void CRoom2::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
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
