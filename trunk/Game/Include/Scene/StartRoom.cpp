
#include "StartRoom.h"
#include "Room2.h"
#include "SceneManager.h"
#include "SceneResource.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

bool CStartRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	m_iMonsterCount = 0;

	CMapManager::GetInst()->CreateSpecialRoomMap(this, ESpecial_RoomType::Start);
	CMapManager::GetInst()->SetSpecialMap(this, ESpecial_RoomType::Start);

	SetCurMapType(ESpecial_RoomType::Start);
	CMapManager::GetInst()->SetSpecialClearMap(GetCurMapType());

	SetDoor(DD_BOTTOM, DT_NORMAL);

	CreatePlayer(Vector2());

	return true;
}

void CStartRoom::Start()
{
	CRoomBase::Start();

	CSceneManager::GetInst()->MusicStart();
}

void CStartRoom::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_BOTTOM:
		MoveRoom<CRoom2>(Vector2::DOWN);
		break;
	}
}

CStartRoom::CStartRoom()
{
}

CStartRoom::~CStartRoom()
{
}
