
#include "Room.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

bool CRoom::Init()
{
	if (!CRoomBase::Init())
		return false;

	int	iRand = rand() % m_iMaxRoomCount + 1;

	SetMap("Room", iRand);

	return true;
}

void CRoom::Start()
{
	CRoomBase::Start();

	CInput::GetInst()->SetCallback<CRoom>("PlayerNextRoom", KS_DOWN, this, &CRoom::Next);
}

bool CRoom::Update(float fTime)
{
	CRoomBase::Update(fTime);

	return true;
}

bool CRoom::PostUpdate(float fTime)
{
	CRoomBase::PostUpdate(fTime);

	return true;
}

bool CRoom::Collision(float fTime)
{
	CRoomBase::Collision(fTime);

	return true;
}

bool CRoom::Render(HDC hDC)
{
	CRoomBase::Render(hDC);

	return true;
}

void CRoom::Next(float fTime)
{
	CSceneManager::GetInst()->CreateScene<CRoom>();
}

CRoom::CRoom()
{
}

CRoom::~CRoom()
{
}
