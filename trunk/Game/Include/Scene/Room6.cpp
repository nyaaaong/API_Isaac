
#include "Room6.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom6::Init()
{
	if (!CRoomBase::Init())
		return false;

	SetMap("Room", m_iRoomNum);

	return true;
}

void CRoom6::Start()
{
	CRoomBase::Start();
}

bool CRoom6::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom6::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom6::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom6::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

CRoom6::CRoom6()
{
}

CRoom6::~CRoom6()
{
}
