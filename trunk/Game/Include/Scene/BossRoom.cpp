
#include "BossRoom.h"
#include "SceneManager.h"
#include "Ending.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CBossRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	CMapManager::GetInst()->CreateSpecialRoomMap(this, ESpecial_RoomType::Boss);
	CMapManager::GetInst()->SetSpecialMap(this, ESpecial_RoomType::Boss);

	SetCurMapType(ESpecial_RoomType::Boss);

	SetDoor(EDoorDir::DD_LEFT, DT_BOSS);
	SetDoor(EDoorDir::DD_TOP, DT_BOSS);
	SetDoor(EDoorDir::DD_RIGHT, DT_BOSS);
	SetDoor(EDoorDir::DD_BOTTOM, DT_BOSS);

	CreatePlayer(Vector2());
	CMonsterSpawner::GetInst()->AddBossSpawnLocation();

	return true;
}

void CBossRoom::Start()
{
	CRoomBase::Start();

	CMonsterSpawner::GetInst()->CreateBossMonster();

	CSceneManager::GetInst()->ChangeMusic(EMusic_Type::Boss);
}

bool CBossRoom::Update(float fTime)
{
	if (!CRoomBase::Update(fTime))
		return false;

	return true;
}

void CBossRoom::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
	case DD_TOP:
	case DD_RIGHT:
	case DD_BOTTOM:
		MoveRoom<CEnding>(Vector2());
		break;
	}
}

CBossRoom::CBossRoom()
{
	m_iBossMonsterCount = 1;
}

CBossRoom::~CBossRoom()
{
}
