
#include "Room3.h"
#include "Room2.h"
#include "Room5.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"
#include "../UI/PlayerHUD.h"

bool CRoom3::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(3);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_LEFT, DT_NORMAL);
	SetDoor(DD_BOTTOM, DT_NORMAL);

	return true;
}

void CRoom3::Start()
{
	CRoomBase::Start();

	m_pPlayerHUD->ActiveMinimapRoom(3);

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom3::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CRoom2>(Vector2::LEFT);
		break;
	case DD_BOTTOM:
		MoveRoom<CRoom5>(Vector2::DOWN);
		break;
	}
}

CRoom3::CRoom3()
{
}

CRoom3::~CRoom3()
{
}
