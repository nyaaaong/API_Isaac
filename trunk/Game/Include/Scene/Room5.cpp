
#include "Room5.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom5::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetMap("Room", m_iRoomNum);

	return true;
}

void CRoom5::Start()
{
	CRoomBase::Start();
}

bool CRoom5::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom5::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom5::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom5::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

CRoom5::CRoom5()
{
}

CRoom5::~CRoom5()
{
}
