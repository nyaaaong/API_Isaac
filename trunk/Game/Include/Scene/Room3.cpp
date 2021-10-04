
#include "Room3.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom3::Init()
{
	if (!CRoomBase::Init())
		return false;

	return true;
}

void CRoom3::Start()
{
	CRoomBase::Start();
}

bool CRoom3::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom3::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom3::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom3::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

CRoom3::CRoom3()
{
}

CRoom3::~CRoom3()
{
}
