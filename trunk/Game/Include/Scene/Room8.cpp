
#include "Room8.h"
#include "Room9.h"
#include "StartRoom.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom8::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(8);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::RIGHT);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_RIGHT, DT_NORMAL);
	SetDoor(DD_BOTTOM, DT_NORMAL);

	return true;
}

void CRoom8::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom8::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_RIGHT:
		MoveRoom<CStartRoom>(Vector2::RIGHT);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom9>(Vector2::DOWN);
		break;
	}
}

CRoom8::CRoom8()
{
}

CRoom8::~CRoom8()
{
}
