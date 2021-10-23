
#include "Room4.h"
#include "Room1.h"
#include "ItemRoom.h"
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
	SetDoor(DD_LEFT, DT_ITEM);

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
	case DD_TOP:
		MoveRoom<CRoom1>(Vector2::UP);
		break;
	case DD_LEFT:
		MoveRoom<CItemRoom>(Vector2::LEFT);
		break;
	}
}

CRoom4::CRoom4()
{
}

CRoom4::~CRoom4()
{
}
