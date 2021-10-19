
#include "Room4.h"
#include "Room1.h"
#include "Room5.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom4::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(4);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::LEFT);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_TOP, DT_NORMAL);
	SetDoor(DD_LEFT, DT_NORMAL);

	return true;
}

void CRoom4::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom4::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CRoom1>(Vector2::LEFT);
		break;
	case DD_TOP:
		MoveRoom<CRoom5>(Vector2::UP);
		break;
	}
}

CRoom4::CRoom4()
{
}

CRoom4::~CRoom4()
{
}
