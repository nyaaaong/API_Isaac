
#include "StartRoom.h"
#include "Room1.h"
#include "Room2.h"
#include "SceneManager.h"
#include "SceneResource.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CStartRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	CreateSpecialRoomMap<CRoomMap>(ESpecial_RoomType::Start);

	m_bClearRoom = true;

	SetDoor(DD_RIGHT, false);
	SetDoor(DD_TOP, false);

	CreatePlayer(Vector2::LEFT);

	return true;
}

void CStartRoom::Start()
{
	CRoomBase::Start();

	GetSceneResource()->LoadSound("BGM", true, "Stage1BGM", "Music/Stage1.ogg");
	GetSceneResource()->SoundPlay("Stage1BGM");
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

void CStartRoom::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_TOP:
		MoveRoom<CRoom1>(Vector2::UP);
		break;
	case DD_RIGHT:
		MoveRoom<CRoom2>(Vector2::RIGHT);
		break;
	}
}

CStartRoom::CStartRoom()
{
}

CStartRoom::~CStartRoom()
{
}
