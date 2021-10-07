
#include "Room1.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom1::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetMap("Room", m_iRoomNum);
	LoadMapObject();
	CreatePlayer(Vector2::DOWN);

	return true;
}

void CRoom1::Start()
{
	CRoomBase::Start();
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

CRoom1::CRoom1()
{
}

CRoom1::~CRoom1()
{
}
