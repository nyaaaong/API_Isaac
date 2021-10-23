
#include "Room1.h"
#include "Room2.h"
#include "Room4.h"
#include "ItemRoom.h"
#include "StartRoom.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom1::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(1);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_RIGHT, DT_NORMAL);
	SetDoor(DD_BOTTOM, DT_NORMAL);

	return true;
}

void CRoom1::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom1::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_RIGHT:
		MoveRoom<CRoom2>(Vector2::RIGHT);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom4>(Vector2::DOWN);
		break;
	}
}

CRoom1::CRoom1()
{
}

CRoom1::~CRoom1()
{
}
