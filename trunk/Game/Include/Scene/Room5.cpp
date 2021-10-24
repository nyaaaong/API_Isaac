
#include "Room5.h"
#include "Room3.h"
#include "Room6.h"
#include "Room7.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"
#include "../UI/PlayerHUD.h"

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
	SetDoor(DD_TOP, DT_NORMAL);
	SetDoor(DD_RIGHT, DT_NORMAL);

	return true;
}

void CRoom5::Start()
{
	CRoomBase::Start();

	m_pPlayerHUD->ActiveMinimapRoom(5);

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom5::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_TOP:
		MoveRoom<CRoom3>(Vector2::UP);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom7>(Vector2::DOWN);
		break;
	case DD_RIGHT:
		MoveRoom<CRoom6>(Vector2::RIGHT);
		break;
	}
}

CRoom5::CRoom5()
{
}

CRoom5::~CRoom5()
{
}
