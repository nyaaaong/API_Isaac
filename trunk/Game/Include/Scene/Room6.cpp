
#include "Room6.h"
#include "Room5.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"
#include "../UI/PlayerHUD.h"

bool CRoom6::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(6);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->AddSpawnLocation();

	SetDoor(DD_LEFT, DT_NORMAL);

	return true;
}

void CRoom6::Start()
{
	CRoomBase::Start();

	m_pPlayerHUD->ActiveMinimapRoom(6);

	CMonsterSpawner::GetInst()->CreateMonster();
}

void CRoom6::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CRoom5>(Vector2::LEFT);
		break;
	}
}

CRoom6::CRoom6()
{
}

CRoom6::~CRoom6()
{
}
