
#include "RoomBase.h"
#include "SceneResource.h"
#include "../GameManager.h"
#include "../Object/Door.h"
#include "../Object/MonsterSpawner.h"
#include "../Map/MapManager.h"

bool CRoomBase::Init()
{
	if (!CStage::Init())
		return false;

	CreateDoor();

	CMonsterSpawner::GetInst()->SetScene(this);

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

	int iNum = GetCurMapNumber();
	ESpecial_RoomType	eType = GetCurMapType();

	if (iNum != -1)
	{
		if (!CMapManager::GetInst()->GetClearMap(iNum) && m_iMonsterCount == 0)
			CMapManager::GetInst()->SetClearMap(iNum);
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(GetCurMapType()))
			CMapManager::GetInst()->SetSpecialClearMap(GetCurMapType());

		CMapManager::GetInst()->SetSpecialClearMap(eType);
	}

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

void CRoomBase::SetDoor(EDoorDir eDoorDir, EDoorType eDoorType)
{
	m_vecDoor[eDoorType][eDoorDir]->Enable(true);
}

const Vector2& CRoomBase::GetDoorPos(EDoorDir eDoorDir, EDoorType eDoorType)
{
	return m_vecDoor[eDoorType][eDoorDir]->GetPos();
}

void CRoomBase::CreateDoor()
{
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
}

void CRoomBase::DoorFunc(EDoorDir eDoorDir)
{
}

CRoomBase::CRoomBase()	:
	m_iMonsterCount(0)
{
	m_vecDoor.resize(DT_MAX);

	for (int i = 0; i < DT_MAX; ++i)
	{
		m_vecDoor[i].resize(DD_MAX);
	}
}

CRoomBase::~CRoomBase()
{
}
