
#include "RoomBase.h"
#include "SceneResource.h"
#include "../GameManager.h"
#include "../Object/Door.h"

bool CRoomBase::Init()
{
	if (!CStage::Init())
		return false;

	Resolution	tRS = CGameManager::GetInst()->GetResolution();
	Vector2	tScreenLT = GetFieldLT();
	Vector2	tScreenRB = GetFieldRB();

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

			switch (j)
			{
			case DD_LEFT:
				m_vecDoor[i][j]->SetPos(tScreenLT.x, tRS.iH * 0.5f);
				m_vecDoor[i][j]->SetOffset(-50.f, 0.f);
				break;
			case DD_TOP:
				m_vecDoor[i][j]->SetPos(tRS.iW * 0.5f, tScreenLT.y);
				m_vecDoor[i][j]->SetOffset(0.f, -50.f);
				break;
			case DD_RIGHT:
				m_vecDoor[i][j]->SetPos(tScreenRB.x, tRS.iH * 0.5f);
				m_vecDoor[i][j]->SetOffset(50.f, 0.f);
				break;
			case DD_BOTTOM:
				m_vecDoor[i][j]->SetPos(tRS.iW * 0.5f, tScreenRB.y);
				m_vecDoor[i][j]->SetOffset(0.f, 50.f);
				break;
			}
		}
	}

	m_iRoomNum = rand() % m_iMaxRoomCount;

	size_t	iSize = m_vecRoomNum.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecRoomNum[i] == m_iRoomNum)
		{
			m_iRoomNum = rand() % m_iMaxRoomCount;
			i = 0;
			continue;
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

const Vector2& CRoomBase::GetDoorPos(EDoorDir eDoorDir, bool bIsBossDoor)
{
	if (!bIsBossDoor)
		return m_vecDoor[DT_NORMAL][eDoorDir]->GetPos();

	else
		return m_vecDoor[DT_BOSS][eDoorDir]->GetPos();
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
	m_bClearRoom(false),
	m_iRoomNum(0)
{
	m_vecDoor.resize(DT_MAX);

	m_vecDoor[0].resize(DD_MAX);
	m_vecDoor[1].resize(DD_MAX);

	m_vecRoomNum.reserve(3);
}

CRoomBase::~CRoomBase()
{
}
