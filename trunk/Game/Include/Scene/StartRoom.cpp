
#include "StartRoom.h"
#include "Room.h"
#include "SceneManager.h"
#include "SceneResource.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CStartRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	CreateSpecialRoomMap<CRoomMap>(ESpecial_RoomType::Start);

	return true;
}

void CStartRoom::Start()
{
	CRoomBase::Start();

	GetSceneResource()->LoadSound("BGM", true, "Stage1BGM", "Music/Stage1.ogg");
	GetSceneResource()->SoundPlay("Stage1BGM");

	CInput::GetInst()->SetCallback<CStartRoom>("PlayerNextRoom", KS_DOWN, this, &CStartRoom::Next);
}

bool CStartRoom::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CStartRoom::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CStartRoom::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;}

bool CStartRoom::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

void CStartRoom::Next(float fTime)
{
	CSceneManager::GetInst()->CreateScene<CRoom>();
}

CStartRoom::CStartRoom()
{
}

CStartRoom::~CStartRoom()
{
}
