
#include "Room6.h"
#include "Room7.h"
#include "Room1.h"
#include "Room5.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom6::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(6);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_BOTTOM, DT_NORMAL);
	SetDoor(DD_LEFT, DT_NORMAL);
	SetDoor(DD_RIGHT, DT_NORMAL);

	return true;
}

void CRoom6::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom6::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CRoom7>(Vector2::LEFT);
		break;
	case DD_RIGHT:
		MoveRoom<CRoom5>(Vector2::RIGHT);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom1>(Vector2::DOWN);
		break;
	}
}

CRoom6::CRoom6()
{
}

CRoom6::~CRoom6()
{
}
