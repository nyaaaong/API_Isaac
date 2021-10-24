
#include "Room2.h"
#include "Room1.h"
#include "Room3.h"
#include "StartRoom.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"
#include "../UI/PlayerHUD.h"

bool CRoom2::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(2);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_TOP, DT_NORMAL);
	SetDoor(DD_LEFT, DT_NORMAL);
	SetDoor(DD_RIGHT, DT_NORMAL);

	return true;
}

void CRoom2::Start()
{
	CRoomBase::Start();

	m_pPlayerHUD->ActiveMinimapRoom(2);

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom2::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_TOP:
		MoveRoom<CStartRoom>(Vector2::UP);
		break;
	case DD_LEFT:
		MoveRoom<CRoom1>(Vector2::LEFT);
		break;
	case DD_RIGHT:
		MoveRoom<CRoom3>(Vector2::RIGHT);
		break;
	}
}

CRoom2::CRoom2()
{
}

CRoom2::~CRoom2()
{
}
