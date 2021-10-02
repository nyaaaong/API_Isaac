
#include "StartRoom.h"
#include "../Map/RoomMap.h"
#include "../Object/BackGround.h"

bool CStartRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	CBackGround* pBackGround = CreateObject<CBackGround>("StartRoom_BackGround");
	pBackGround->StartRoom();

	CreateSpecialRoomMap<CRoomMap>(ESpecial_RoomType::Start);

	return true;
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

	return true;
}

bool CStartRoom::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

CStartRoom::CStartRoom()
{
}

CStartRoom::~CStartRoom()
{
}
