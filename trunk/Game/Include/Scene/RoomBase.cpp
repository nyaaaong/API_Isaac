
#include "RoomBase.h"
#include "SceneResource.h"
#include "../Object/Door.h"

bool CRoomBase::Init()
{
	if (!CStage::Init())
		return false;

	for (int i = 0; i < DT_MAX; ++i)
	{
		std::vector<CDoor*>	vecData;

		m_vecDoor.push_back(vecData);

		for (int j = 0; j < DD_MAX; ++j)
		{
			m_vecDoor[i][j] = CreateObject<CDoor>("Door");
			m_vecDoor[i][j]->SetDoorType(static_cast<EDoorType>(i));
			m_vecDoor[i][j]->SetDoorDir(static_cast<EDoorDir>(j));
			m_vecDoor[i][j]->Enable(false);
		}
	}

	return true;
}

void CRoomBase::CreateMonster()
{

}

void CRoomBase::Start()
{
	CStage::Start(); 
	CreateMonster();
}

bool CRoomBase::Update(float fTime)
{
	CStage::Update(fTime);

	return true;
}

bool CRoomBase::PostUpdate(float fTime)
{
	CStage::PostUpdate(fTime);

	return true;
}

bool CRoomBase::Collision(float fTime)
{
	CStage::Collision(fTime);

	return true;
}

bool CRoomBase::Render(HDC hDC)
{
	CStage::Render(hDC);

	return true;
}

void CRoomBase::SetDoor(EDoorDir eDoorDir, bool bIsBossDoor)
{
	if (!bIsBossDoor)
		m_vecDoor[DT_NORMAL][eDoorDir]->Enable(true);
	
	else
		m_vecDoor[DT_BOSS][eDoorDir]->Enable(true);
}

void CRoomBase::DoorFunc(EDoorDir eDoorDir)
{
	switch (eDoorDir)
	{
	case DD_LEFT:
		break;
	case DD_TOP:
		break;
	case DD_RIGHT:
		break;
	case DD_BOTTOM:
		break;
	}
}

CRoomBase::CRoomBase()	:
	m_bClearRoom(false)
{
	m_vecDoor.resize(DT_MAX);

	m_vecDoor[0].resize(DD_MAX);
	m_vecDoor[1].resize(DD_MAX);
}

CRoomBase::~CRoomBase()
{
}
