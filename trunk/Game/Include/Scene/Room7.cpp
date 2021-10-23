
#include "Room7.h"
#include "Room5.h"
#include "Room8.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom7::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(7);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::RIGHT);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_TOP, DT_NORMAL);
	SetDoor(DD_LEFT, DT_NORMAL);

	return true;
}

void CRoom7::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom7::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_TOP:
		MoveRoom<CRoom5>(Vector2::UP);
		break;
	case DD_LEFT:
		MoveRoom<CRoom8>(Vector2::LEFT);
		break;
	}
}

CRoom7::CRoom7()
{
}

CRoom7::~CRoom7()
{
}
