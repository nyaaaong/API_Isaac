
#include "ItemRoom.h"
#include "Room1.h"
#include "SceneResource.h"
#include "../Object/ItemRock.h"
#include "../Map/MapManager.h"

CItemRoom::CItemRoom()
{
}

CItemRoom::~CItemRoom()
{
}

bool CItemRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	CMapManager::GetInst()->CreateSpecialRoomMap(this, ESpecial_RoomType::Item);
	CMapManager::GetInst()->SetSpecialMap(this, ESpecial_RoomType::Item);

	Vector2	tFieldRB = GetFieldRB();

	CItemRock* pItemRock = CreateObject<CItemRock>("ItemRock", Vector2(tFieldRB.x * 0.55f, tFieldRB.y * 0.6f), Vector2(81.f, 63.f));

	SetDoor(DD_RIGHT, DT_ITEM);

	CreatePlayer(Vector2::RIGHT);

#ifdef _DEBUG
	m_bClearRoom = true;
#endif // _DEBUG

	return true;
}

void CItemRoom::Start()
{
}

void CItemRoom::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_RIGHT:
		MoveRoom<CRoom1>(Vector2::RIGHT);
		break;
	}
}
