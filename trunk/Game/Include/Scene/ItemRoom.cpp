
#include "ItemRoom.h"
#include "Room4.h"
#include "SceneResource.h"
#include "../Object/ItemRock.h"
#include "../Object/ItemGlasses.h"
#include "../Map/MapManager.h"
#include "../UI/PlayerHUD.h"

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

	m_iMonsterCount = 0;

	CMapManager::GetInst()->CreateSpecialRoomMap(this, ESpecial_RoomType::Item);
	CMapManager::GetInst()->SetSpecialMap(this, ESpecial_RoomType::Item);

	Vector2	tFieldRB = GetFieldRB();

	CItemRock* pItemRock = CreateObject<CItemRock>("ItemRock", Vector2(tFieldRB.x * 0.55f, tFieldRB.y * 0.6f), Vector2(81.f, 63.f));

	Vector2	tRockPos = pItemRock->GetPos();
	CItemGlasses* pItem = CreateObject<CItemGlasses>("ItemGlasses", Vector2(tRockPos.x - 5.f, tRockPos.y - 40.f), Vector2(96.f, 96.f));
	
	pItemRock->SetItem(pItem);

	SetDoor(DD_RIGHT, DT_ITEM);

	CreatePlayer(Vector2::RIGHT);

	SetCurMapType(ESpecial_RoomType::Item);
	CMapManager::GetInst()->SetSpecialClearMap(GetCurMapType());

	return true;
}

void CItemRoom::Start()
{
	CRoomBase::Start();

	m_pPlayerHUD->ActiveMinimapRoom(10);
}

void CItemRoom::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_RIGHT:
		MoveRoom<CRoom4>(Vector2::RIGHT);
		break;
	}
}
