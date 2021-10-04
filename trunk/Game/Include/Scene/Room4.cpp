
#include "Room4.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom4::Init()
{
	if (!CRoomBase::Init())
		return false;

	return true;
}

void CRoom4::Start()
{
	CRoomBase::Start();
}

bool CRoom4::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom4::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom4::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom4::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

CRoom4::CRoom4()
{
}

CRoom4::~CRoom4()
{
}
