
#include "MonsterSpawner.h"
#include "Charger.h"
#include "Pooter.h"
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
	}
	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;
	}

	m_pScene->CreatePrototype<CEnemyDie>("EnemyDieNormal");
	m_pScene->CreatePrototype<CEnemyDie>("EnemyDieFly");

	CCharger* pCharger = m_pScene->CreatePrototype<CCharger>("Charger");

	m_vecSize.push_back(pCharger->GetSize());
	m_vecPivot.push_back(pCharger->GetPivot());
	m_vecOffset.push_back(pCharger->GetPivot());
	m_vecName.push_back(pCharger->GetName());

	CPooter* pPooter = m_pScene->CreatePrototype<CPooter>("Pooter");

	m_vecSize.push_back(pPooter->GetSize());
	m_vecPivot.push_back(pPooter->GetPivot());
	m_vecOffset.push_back(pPooter->GetPivot());
	m_vecName.push_back(pPooter->GetName());
}

void CMonsterSpawner::CreateMonster()
{
	CRoomBase* pRoom = dynamic_cast<CRoomBase*>(m_pScene);
	int iMonsterCount = pRoom->GetMonsterCount();

	if (!iMonsterCount)
		return;

	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;
	}

	size_t iSize = m_vecName.size();

	for (int i = 0; i < iMonsterCount; ++i)
	{
		int iIdx = rand() % iSize;

		CreateSpawnLocation(m_vecSize[iIdx], m_vecPivot[iIdx], m_vecOffset[iIdx]); // 랜덤으로 스폰 좌표 생성
		CreateMonster(m_vecName[iIdx]);
	}
}

void CMonsterSpawner::EnemyDieNormal(const Vector2& tPos)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;
	}

	m_pScene->CreateObject<CEnemyDie>("EnemyDieNormal", "EnemyDieNormal", tPos, Vector2(192.f, 192.f));
	m_pScene->GetSceneResource()->SoundPlay("EnemyDie");
	dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount(1);
}

void CMonsterSpawner::EnemyDieFly(const Vector2& tPos)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(m_pScene->GetCurMapType()))
			return;
	}

	CEnemyDie* pDieEffect = m_pScene->CreateObject<CEnemyDie>("EnemyDieFly", "EnemyDieFly", tPos, Vector2(192.f, 192.f));
	pDieEffect->SetEnemyType(EEnemy_Type::Fly);
	m_pScene->GetSceneResource()->SoundPlay("EnemyDie");
	dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount(1);
}

void CMonsterSpawner::CreateSpawnLocation(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset)
{
	int iSpawnCount = static_cast<int>(m_vecSpawnStartPos.size());

	if (iSpawnCount == 0)
		return;

	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;

		Vector2	tPosLT;
		Vector2	tPosRB;
		int	iIdx = 0;

		do
		{
			if (iSpawnCount > 1)
				iIdx = rand() % iSpawnCount;

			int	iStartPosX = static_cast<int>(m_vecSpawnStartPos[iIdx].x);
			int	iStartPosY = static_cast<int>(m_vecSpawnStartPos[iIdx].y);

			int	iEndPosX = static_cast<int>(m_vecSpawnEndPos[iIdx].x);
			int	iEndPosY = static_cast<int>(m_vecSpawnEndPos[iIdx].y);

			int iRandX = rand() % iEndPosX - iStartPosX + iStartPosX;
			int iRandY = rand() % iEndPosY - iStartPosY + iStartPosY;

			m_tSpawnPos.x = static_cast<float>(iRandX);
			m_tSpawnPos.y = static_cast<float>(iRandY);

		} while (!CheckSpawnPossible(tSize, tPivot, tOffset)); // 스폰 배치가 불가능한 지역이면 루프 실행.
	}
}

void CMonsterSpawner::CreateMonster(const std::string& strName)
{
	if (m_tSpawnPos == Vector2())
		return;

	else if (strName == "Charger")
		m_pScene->CreateObject<CCharger>(strName, strName, m_tSpawnPos);

	else if (strName == "Pooter")
		m_pScene->CreateObject<CPooter>(strName, strName, m_tSpawnPos);
}

void CMonsterSpawner::AddSpawnLocation()
{
	int iNum = m_pScene->GetCurMapNumber();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(m_pScene->GetCurMapNumber()))
			return;
	}

	m_vecSpawnStartPos.clear();
	m_vecSpawnEndPos.clear();

	CRoomMap* pCurMap = m_pScene->GetCurrentMap();
	
	std::list<CRoomObj*>::iterator	iter = pCurMap->m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = pCurMap->m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetType() == MT_SPAWN)
		{
			m_vecSpawnStartPos.push_back((*iter)->GetPos());
			m_vecSpawnEndPos.push_back((*iter)->GetPos() + (*iter)->GetSize());
		}
	}
}

bool CMonsterSpawner::CheckSpawnPossible(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset)
{
	if (m_tSpawnPos == Vector2())
		return false;

	CRoomMap* pCurMap = m_pScene->GetCurrentMap();

	Vector2	tMonsterLT = m_tSpawnPos - tSize * tPivot + tOffset;
	Vector2	tMonsterRB = m_tSpawnPos + tSize * tPivot + tOffset;

	if (pCurMap->IsObj(m_pScene, tMonsterLT, tMonsterRB, MT_ROCK) ||
		pCurMap->IsObj(m_pScene, tMonsterLT, tMonsterRB, MT_IRON) ||
		pCurMap->IsObj(m_pScene, tMonsterLT, tMonsterRB, MT_SPIKE) ||
		pCurMap->IsObj(m_pScene, tMonsterLT, tMonsterRB, MT_POOP))
		return false;

	return true;
}
