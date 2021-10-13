
#include "Room1.h"
#include "ItemRoom.h"
#include "StartRoom.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CRoom1::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetCurMapNumber(1);

	CMapManager::GetInst()->SetMap(this, GetCurMapNumber());
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);
	CMonsterSpawner::GetInst()->SetMonsterSpawnLocation(Vector2::UP);

	SetDoor(DD_LEFT, DT_ITEM);
	SetDoor(DD_BOTTOM, DT_NORMAL);

	return true;
}

void CRoom1::Start()
{
	CRoomBase::Start();

	m_iMonsterCount = 3;
	CMonsterSpawner::GetInst()->CreateMonster();
}

bool CRoom1::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom1::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom1::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom1::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

void CRoom1::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		MoveRoom<CItemRoom>(Vector2::LEFT);
		break;
	case DD_BOTTOM:
		MoveRoom<CStartRoom>(Vector2::DOWN);
		break;
	}
}

CRoom1::CRoom1()
{
}

CRoom1::~CRoom1()
{
}
