
#include "Room9.h"
#include "Room8.h"
#include "BossRoom.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom9::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(9);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::UP);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_TOP, DT_NORMAL);
	SetDoor(DD_LEFT, DT_BOSS);

	return true;
}

void CRoom9::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom9::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_TOP:
		MoveRoom<CRoom8>(Vector2::UP);
		break;
	case DD_LEFT:
		MoveRoom<CBossRoom>(Vector2::LEFT);
		break;
	}
}

CRoom9::CRoom9()
{
}

CRoom9::~CRoom9()
{
}
