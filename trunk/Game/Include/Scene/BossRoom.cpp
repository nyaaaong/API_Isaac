
#include "BossRoom.h"
#include "Room3.h"
#include "SceneManager.h"
#include "SceneResource.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../Object/BossMonstro.h"
#include "../Object/MonsterSpawner.h"
#include "../UI/PlayerHUD.h"

bool CBossRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	m_iMonsterCount = 1;

	CMapManager::GetInst()->CreateSpecialRoomMap(this, ESpecial_RoomType::Boss);
	CMapManager::GetInst()->SetSpecialMap(this, ESpecial_RoomType::Boss);

	SetCurMapType(ESpecial_RoomType::Boss);

	SetDoor(EDoorDir::DD_RIGHT, DT_BOSS);
	SetDoor(EDoorDir::DD_BOTTOM, DT_BOSS);

	CreatePlayer(Vector2::RIGHT);
	//CMonsterSpawner::GetInst()->SetMonsterSpawnLocation(Vector2::LEFT);

	return true;
}

void CBossRoom::Start()
{
	CRoomBase::Start();

	// º¸½º bgm
	//GetSceneResource()->LoadSound("BGM", true, "Stage1BGM", "Music/Stage1.ogg");
	//GetSceneResource()->SoundPlay("Stage1BGM");

	//CInput::GetInst()->SetCallback<CBossRoom>("PlayerNextRoom", KS_DOWN, this, &CBossRoom::Next);
}

void CBossRoom::CreateMonster()
{
	Vector2	tDoorPos = GetDoorPos(EDoorDir::DD_RIGHT, DT_BOSS);

	//Vector2	tPlayerPos = GetPlayer()->GetPos();
	//
	//CSharedPtr<CBossMonstro> pMonstro = CreateObject<CBossMonstro>("Monstro", "Monstro", Vector2(tPlayerPos.x - 600.f, tPlayerPos.y + 20.f));
	//m_pPlayerHUD->SetBossMonster(static_cast<CCharacter*>(pMonstro));
}

void CBossRoom::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_RIGHT:
		MoveRoom<CRoom3>(Vector2::RIGHT);
		break;
	case DD_BOTTOM:
		//MoveRoom<CRoom3>(Vector2::RIGHT);
		break;
	}
}

void CBossRoom::Next(float fTime)
{
	//CSceneManager::GetInst()->CreateScene<CEnding>();
}

CBossRoom::CBossRoom()
{
}

CBossRoom::~CBossRoom()
{
}
