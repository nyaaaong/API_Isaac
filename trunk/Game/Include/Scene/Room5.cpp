
#include "Room5.h"
#include "Room6.h"
#include "Room4.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom5::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(5);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::LEFT);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_BOTTOM, DT_NORMAL);
	SetDoor(DD_LEFT, DT_NORMAL);

	return true;
}

void CRoom5::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom5::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CRoom6>(Vector2::LEFT);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom4>(Vector2::DOWN);
		break;
	}
}

CRoom5::CRoom5()
{
}

CRoom5::~CRoom5()
{
}
