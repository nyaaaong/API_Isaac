
#include "Room7.h"
#include "Room6.h"
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

	SetDoor(DD_RIGHT, DT_NORMAL);

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
	case DD_RIGHT:
		MoveRoom<CRoom6>(Vector2::RIGHT);
		break;
	}
}

CRoom7::CRoom7()
{
}

CRoom7::~CRoom7()
{
}
