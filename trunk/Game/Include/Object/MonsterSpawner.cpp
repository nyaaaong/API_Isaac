
#include "MonsterSpawner.h"
#include "Charger.h"
#include "EnemyDie.h"
#include "MonsterBase.h"
#include "../Scene/Scene.h"
#include "../Scene/RoomBase.h"
#include "../Scene/SceneResource.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

CMonsterSpawner* CMonsterSpawner::m_pInst = nullptr;

CMonsterSpawner::CMonsterSpawner()	:
	m_pScene(nullptr)
{
}

CMonsterSpawner::~CMonsterSpawner()
{
}

bool CMonsterSpawner::Init()
{
	return true;
}

void CMonsterSpawner::SetScene(CScene* pCurScene)
{
	m_pScene = pCurScene;
}

void CMonsterSpawner::CreateMonsterPrototype()
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;

		m_pScene->CreatePrototype<CEnemyDie>("EnemyDie1");

		CCharger* pCharger = m_pScene->CreatePrototype<CCharger>("Charger");

		m_vecSize.push_back(pCharger->GetSize());
		m_vecPivot.push_back(pCharger->GetPivot());
		m_vecOffset.push_back(pCharger->GetPivot());
		m_vecName.push_back(pCharger->GetName());
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;

		m_pScene->CreatePrototype<CEnemyDie>("EnemyDie1");

		CCharger* pCharger = m_pScene->CreatePrototype<CCharger>("Charger");

		m_vecSize.push_back(pCharger->GetSize());
		m_vecPivot.push_back(pCharger->GetPivot());
		m_vecOffset.push_back(pCharger->GetPivot());
		m_vecName.push_back(pCharger->GetName());
	}
}

void CMonsterSpawner::CreateMonster()
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;

		CRoomBase* pRoom = dynamic_cast<CRoomBase*>(m_pScene);
		size_t iSize = m_vecName.size();

		for (int i = 0; i < pRoom->GetMonsterCount(); ++i)
		{
			int iIdx = rand() % iSize;

			CreateSpawnLocation(m_vecSize[iIdx], m_vecPivot[iIdx], m_vecOffset[iIdx]); // 랜덤으로 스폰 좌표 생성
			CreateMonster(m_vecName[iIdx]);
		}
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;

		CRoomBase* pRoom = dynamic_cast<CRoomBase*>(m_pScene);
		size_t iSize = m_vecName.size();

		for (int i = 0; i < pRoom->GetMonsterCount(); ++i)
		{
			int iIdx = rand() % iSize;

			CreateSpawnLocation(m_vecSize[iIdx], m_vecPivot[iIdx], m_vecOffset[iIdx]); // 랜덤으로 스폰 좌표 생성
			CreateMonster(m_vecName[iIdx]);
		}
	}
}

void CMonsterSpawner::SetMonsterSpawnLocation(const Vector2& tLocation)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;

		const Vector2	tFieldLT = m_pScene->GetFieldLT();
		const Vector2	tFieldRB = m_pScene->GetFieldRB();

		// 좌측 영역
		const Vector2	tLeftLT = tFieldLT;
		const Vector2	tLeftRB = Vector2(tFieldLT.x + 200.f, tFieldRB.y);

		// 우측 영역
		const Vector2	tRightLT = Vector2(tFieldRB.x - 200.f, tFieldLT.y);
		const Vector2	tRightRB = tFieldRB;

		// 상단 영역
		const Vector2	tTopLT = tFieldLT;
		const Vector2	tTopRB = Vector2(tFieldRB.x, tFieldLT.y + 200.f);

		// 하단 영역
		const Vector2	tBottomLT = Vector2(tFieldRB.x, tFieldLT.y - 200.f);
		const Vector2	tBottomRB = tFieldRB;

		if (tLocation == Vector2::LEFT)
		{
			m_tSpawnLocationLT = tRightLT;
			m_tSpawnLocationRB = tRightRB;
		}

		else if (tLocation == Vector2::RIGHT)
		{
			m_tSpawnLocationLT = tLeftLT;
			m_tSpawnLocationRB = tLeftRB;
		}

		else if (tLocation == Vector2::UP)
		{
			m_tSpawnLocationLT = tBottomLT;
			m_tSpawnLocationRB = tBottomRB;
		}

		else if (tLocation == Vector2::DOWN)
		{
			m_tSpawnLocationLT = tTopLT;
			m_tSpawnLocationRB = tTopRB;
		}
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;

		const Vector2	tFieldLT = m_pScene->GetFieldLT();
		const Vector2	tFieldRB = m_pScene->GetFieldRB();

		// 좌측 영역
		const Vector2	tLeftLT = tFieldLT;
		const Vector2	tLeftRB = Vector2(tFieldLT.x + 200.f, tFieldRB.y);

		// 우측 영역
		const Vector2	tRightLT = Vector2(tFieldRB.x - 200.f, tFieldLT.y);
		const Vector2	tRightRB = tFieldRB;

		// 상단 영역
		const Vector2	tTopLT = tFieldLT;
		const Vector2	tTopRB = Vector2(tFieldRB.x, tFieldLT.y + 200.f);

		// 하단 영역
		const Vector2	tBottomLT = Vector2(tFieldRB.x, tFieldLT.y - 200.f);
		const Vector2	tBottomRB = tFieldRB;

		if (tLocation == Vector2::LEFT)
		{
			m_tSpawnLocationLT = tRightLT;
			m_tSpawnLocationRB = tRightRB;
		}

		else if (tLocation == Vector2::RIGHT)
		{
			m_tSpawnLocationLT = tLeftLT;
			m_tSpawnLocationRB = tLeftRB;
		}

		else if (tLocation == Vector2::UP)
		{
			m_tSpawnLocationLT = tBottomLT;
			m_tSpawnLocationRB = tBottomRB;
		}

		else if (tLocation == Vector2::DOWN)
		{
			m_tSpawnLocationLT = tTopLT;
			m_tSpawnLocationRB = tTopRB;
		}
	}
}

void CMonsterSpawner::EnemyDie1(const Vector2& tPos)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;

		m_pScene->CreateObject<CEnemyDie>("EnemyDie1", "EnemyDie1", tPos, Vector2(192.f, 192.f));
		m_pScene->GetSceneResource()->SoundPlay("EnemyDie");
		dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount(1);
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;

		m_pScene->CreateObject<CEnemyDie>("EnemyDie1", "EnemyDie1", tPos, Vector2(192.f, 192.f));
		m_pScene->GetSceneResource()->SoundPlay("EnemyDie");
		dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount(1);
	}
}

void CMonsterSpawner::CreateSpawnLocation(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;

		Vector2	tPosLT;
		Vector2	tPosRB;

		do
		{
			int	iLTX = static_cast<int>(m_tSpawnLocationLT.x);
			int	iLTY = static_cast<int>(m_tSpawnLocationLT.y);

			int	iRBX = static_cast<int>(m_tSpawnLocationRB.x);
			int	iRBY = static_cast<int>(m_tSpawnLocationRB.y);

			int iX = 0;
			int iY = 0;

			if (iRBX != 0)
				int iX = rand() % iRBX - iLTX + 1 + iLTX;

			if (iRBY != 0)
				int iY = rand() % iRBY - iLTY + 1 + iLTY;

			m_tSpawnLocation.x = static_cast<float>(iX);
			m_tSpawnLocation.y = static_cast<float>(iY);

			tPosLT = m_tSpawnLocation - tSize * tPivot + tOffset;
			tPosRB = m_tSpawnLocation + tSize * tPivot + tOffset;

		} while (m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_IRON) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_IRON) ||
			m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_ROCK) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_ROCK) ||
			m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_POOP) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_POOP) ||
			m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_SPIKE) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_SPIKE));
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;

		Vector2	tPosLT;
		Vector2	tPosRB;

		do
		{
			int	iLTX = static_cast<int>(m_tSpawnLocationLT.x);
			int	iLTY = static_cast<int>(m_tSpawnLocationLT.y);

			int	iRBX = static_cast<int>(m_tSpawnLocationRB.x);
			int	iRBY = static_cast<int>(m_tSpawnLocationRB.y);

			int iX = 0;
			int iY = 0;

			if (iRBX != 0)
				int iX = rand() % iRBX - iLTX + 1 + iLTX;

			if (iRBY != 0)
				int iY = rand() % iRBY - iLTY + 1 + iLTY;

			m_tSpawnLocation.x = static_cast<float>(iX);
			m_tSpawnLocation.y = static_cast<float>(iY);

			tPosLT = m_tSpawnLocation - tSize * tPivot + tOffset;
			tPosRB = m_tSpawnLocation + tSize * tPivot + tOffset;

		} while (m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_IRON) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_IRON) ||
			m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_ROCK) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_ROCK) ||
			m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_POOP) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_POOP) ||
			m_pScene->GetCurrentMap()->IsObj(tPosLT, MT_SPIKE) ||
			m_pScene->GetCurrentMap()->IsObj(tPosRB, MT_SPIKE));
	}
}

void CMonsterSpawner::CreateMonster(const std::string& strName)
{
	if (strName == "Charger")
		m_pScene->CreateObject<CCharger>(strName, strName, m_tSpawnLocation);
}
