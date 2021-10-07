#include "BossRoom.h"
#include "SceneManager.h"
#include "SceneResource.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Object/BossMonstro.h"
#include "../UI/PlayerHUD.h"

bool CBossRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	CreateSpecialRoomMap<CRoomMap>(ESpecial_RoomType::Boss);
	SetDoor(EDoorDir::DD_RIGHT, true);

	CreatePlayer(Vector2(GetFieldRB().x - 50.f, GetFieldRB().y * 0.5f));

	return true;
}

void CBossRoom::Start()
{
	CRoomBase::Start();

	Vector2	tDoorPos = GetDoorPos(EDoorDir::DD_RIGHT, true);

	// º¸½º bgm
	//GetSceneResource()->LoadSound("BGM", true, "Stage1BGM", "Music/Stage1.ogg");
	//GetSceneResource()->SoundPlay("Stage1BGM");

	//CInput::GetInst()->SetCallback<CBossRoom>("PlayerNextRoom", KS_DOWN, this, &CBossRoom::Next);
}

bool CBossRoom::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CBossRoom::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CBossRoom::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CBossRoom::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

void CBossRoom::CreateMonster()
{
	//Vector2	tPlayerPos = GetPlayer()->GetPos();
	//
	//CSharedPtr<CBossMonstro> pMonstro = CreateObject<CBossMonstro>("Monstro", "Monstro", Vector2(tPlayerPos.x - 600.f, tPlayerPos.y + 20.f));
	//m_pPlayerHUD->SetBossMonster(static_cast<CCharacter*>(pMonstro));
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
