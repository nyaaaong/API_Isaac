
#include "MonsterSpawner.h"
#include "Player.h"
#include "Charger.h"
#include "Pooter.h"
#include "Fly.h"
#include "RedFly.h"
#include "Mother.h"
#include "MotherLeg.h"
#include "MotherDoor.h"
#include "EnemyDie.h"
#include "EnemySmokeSmall.h"
#include "EnemySmokeNormal.h"
#include "MonsterBase.h"
#include "Heart.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/RoomBase.h"
#include "../Scene/SceneResource.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"
#include "../UI/PlayerHUD.h"

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
		if (CMapManager::GetInst()->GetClearMap(iNum))
			return;
	}
	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;
	}

	m_pScene->CreatePrototype<CEnemyDie>("EnemyDieNormal");
	m_pScene->CreatePrototype<CEnemyDie>("EnemyDieFly");

	m_pScene->CreatePrototype<CEnemySmokeSmall>("Smoke1");
	m_pScene->CreatePrototype<CEnemySmokeNormal>("Smoke2");

	CCharger* pCharger = m_pScene->CreatePrototype<CCharger>("Charger");

	m_vecSize.push_back(pCharger->GetSize());
	m_vecPivot.push_back(pCharger->GetPivot());
	m_vecOffset.push_back(pCharger->GetOffset());
	m_vecName.push_back(pCharger->GetName());

	CPooter* pPooter = m_pScene->CreatePrototype<CPooter>("Pooter");

	m_vecSize.push_back(pPooter->GetSize());
	m_vecPivot.push_back(pPooter->GetPivot());
	m_vecOffset.push_back(pPooter->GetOffset());
	m_vecName.push_back(pPooter->GetName());

	CFly* pFly = m_pScene->CreatePrototype<CFly>("Fly");

	m_vecSize.push_back(pFly->GetSize());
	m_vecPivot.push_back(pFly->GetPivot());
	m_vecOffset.push_back(pFly->GetOffset());
	m_vecName.push_back(pFly->GetName());

	CRedFly* pRedFly = m_pScene->CreatePrototype<CRedFly>("RedFly");

	m_vecSize.push_back(pRedFly->GetSize());
	m_vecPivot.push_back(pRedFly->GetPivot());
	m_vecOffset.push_back(pRedFly->GetOffset());
	m_vecName.push_back(pRedFly->GetName());
}

void CMonsterSpawner::CreateBossMonsterPrototype()
{
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (eType == ESpecial_RoomType::Boss)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;

		CMother* pMother = m_pScene->CreatePrototype<CMother>("Mother");
		m_vecBossName.push_back(pMother->GetName());

		m_pScene->CreatePrototype<CMotherLeg>("MotherLeg");
		m_pScene->CreatePrototype<CMotherDoor>("MotherDoor");
	}
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
		if (CMapManager::GetInst()->GetClearMap(iNum))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;
	}

	size_t iSize = m_vecName.size();

	for (int i = 0; i < iMonsterCount; ++i)
	{
		int iIdx = rand() % iSize;

		CreateSpawnLocation(m_vecSize[iIdx], m_vecPivot[iIdx], m_vecOffset[iIdx]); // 랜덤으로 스폰 좌표 생성
		CreateMonster(m_vecName[iIdx]);
	}

	m_pScene->GetSceneResource()->SoundPlay("DoorClose");
}

void CMonsterSpawner::CreateMonster(const Vector2& tPos)
{
	CRoomBase* pRoom = dynamic_cast<CRoomBase*>(m_pScene);

	size_t iSize = m_vecName.size();

	int iIdx = rand() % iSize;

	m_tSpawnPos = tPos;
	CreateMonster(m_vecName[iIdx]);
}

void CMonsterSpawner::CreateBossMonster()
{
	CRoomBase* pRoom = dynamic_cast<CRoomBase*>(m_pScene);
	int iBossMonsterCount = pRoom->GetBossMonsterCount();

	if (!iBossMonsterCount)
		return;

	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(iNum))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;
	}

	size_t iSize = m_vecBossName.size();
	int iIdx = 0;

	for (; iIdx < iSize; ++iIdx)
	{
		if (m_vecBossName[iIdx] == "Mother")
			break;
	}

	CreateBossMonster(m_vecBossName[iIdx]);

	m_pScene->GetSceneResource()->SoundPlay("DoorClose");
}

void CMonsterSpawner::EnemyDieNormal(const Vector2& tPos)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(iNum))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;
	}

	m_pScene->CreateObject<CEnemyDie>("EnemyDieNormal", "EnemyDieNormal", tPos, Vector2(192.f, 192.f));
	m_pScene->GetSceneResource()->SoundPlay("EnemyDie");
	dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount();
	CreateHeart(tPos);
}

void CMonsterSpawner::EnemyDieFly(const Vector2& tPos)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(iNum))
			return;
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;
	}

	CEnemyDie* pDieEffect = m_pScene->CreateObject<CEnemyDie>("EnemyDieFly", "EnemyDieFly", tPos, Vector2(192.f, 192.f));
	pDieEffect->SetEnemyType(EEnemy_Type::Fly);
	m_pScene->GetSceneResource()->SoundPlay("EnemyDie");
	dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount();
	CreateHeart(tPos);
}

void CMonsterSpawner::CreateSpawnLocation(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset)
{
	int iSpawnCount = static_cast<int>(m_vecSpawnStartPos.size());

	if (iSpawnCount == 0)
		return;

	int iNum = m_pScene->GetCurMapNumber();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(iNum))
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

			int iRandX = rand() % (iEndPosX - iStartPosX + 1) + iStartPosX;
			int iRandY = rand() % (iEndPosY - iStartPosY + 1) + iStartPosY;

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

	else if (strName == "Fly")
		m_pScene->CreateObject<CFly>(strName, strName, m_tSpawnPos);

	else if (strName == "RedFly")
		m_pScene->CreateObject<CRedFly>(strName, strName, m_tSpawnPos);

	m_pScene->CreateObject<CEnemySmokeSmall>("Smoke1", "Smoke1", m_tSpawnPos, Vector2(144.f, 144.f));
}

void CMonsterSpawner::CreateBossMonster(const std::string& strName)
{
	CMother* pMother = nullptr;

	if (m_tSpawnPos == Vector2())
		return;

	else if (strName == "Mother")
	{
		pMother = m_pScene->CreateObject<CMother>(strName, strName, m_tSpawnPos);

		CMotherLeg* pLeg = dynamic_cast<CMotherLeg*>(m_pScene->CreateObject<CMotherLeg>("MotherLeg", "MotherLeg", m_tSpawnPos));

		CMotherDoor* pDoor[DD_MAX] = {};

		pDoor[DD_LEFT] = dynamic_cast<CMotherDoor*>(m_pScene->CreateObject<CMotherDoor>("MotherDoor", "MotherDoor", m_tSpawnPos));
		pDoor[DD_TOP] = dynamic_cast<CMotherDoor*>(m_pScene->CreateObject<CMotherDoor>("MotherDoor", "MotherDoor", m_tSpawnPos));
		pDoor[DD_RIGHT] = dynamic_cast<CMotherDoor*>(m_pScene->CreateObject<CMotherDoor>("MotherDoor", "MotherDoor", m_tSpawnPos));
		pDoor[DD_BOTTOM] = dynamic_cast<CMotherDoor*>(m_pScene->CreateObject<CMotherDoor>("MotherDoor", "MotherDoor", m_tSpawnPos));

		pMother->SetPart(pLeg, pDoor);

		pLeg->SetMother(pMother);

		pDoor[DD_LEFT]->SetMother(pMother);
		pDoor[DD_LEFT]->SetDoorDir(DD_LEFT);

		pDoor[DD_TOP]->SetMother(pMother);
		pDoor[DD_TOP]->SetDoorDir(DD_TOP);

		pDoor[DD_RIGHT]->SetMother(pMother);
		pDoor[DD_RIGHT]->SetDoorDir(DD_RIGHT);
		
		pDoor[DD_BOTTOM]->SetMother(pMother);
		pDoor[DD_BOTTOM]->SetDoorDir(DD_BOTTOM);
	}

	CPlayerHUD* pHUD = dynamic_cast<CStage*>(m_pScene)->GetPlayerHUD();
	pHUD->SetBossMonster(pMother);
	dynamic_cast<CPlayer*>(m_pScene->GetPlayer())->SetBoss(pMother);
}

void CMonsterSpawner::AddSpawnLocation()
{
	int iNum = m_pScene->GetCurMapNumber();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(iNum))
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

void CMonsterSpawner::AddBossSpawnLocation()
{
	int iNum = m_pScene->GetCurMapNumber();

	if (iNum != -1)
	{
		if (CMapManager::GetInst()->GetClearMap(iNum))
			return;
	}

	float	fResX = static_cast<float>(CGameManager::GetInst()->GetResolution().iW);
	float	fResY = static_cast<float>(CGameManager::GetInst()->GetResolution().iH);

	m_tSpawnPos = Vector2(fResX * 0.5f, fResY * 0.5f);
}

void CMonsterSpawner::CreateSmoke(const Vector2& tPos)
{
	m_pScene->CreateObject<CEnemySmokeNormal>("Smoke2", "Smoke2", tPos, Vector2(288.f, 288.f));
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

void CMonsterSpawner::CreateHeart(const Vector2& tPos)
{
	float	fPercent = rand() % 10000 / 100.f;

	if (fPercent > 20.f)
		return;

	m_pScene->GetSceneResource()->SoundPlay("HeartDrop");

	CHeart*	pHeart = m_pScene->CreateObject<CHeart>("Heart", "Heart", tPos, Vector2(96.f, 96.f));
	pHeart->SetPlayer(dynamic_cast<CPlayer*>(m_pScene->GetPlayer()));

	fPercent = rand() % 10000 * 100.f;

	if (fPercent < 10.f)
		pHeart->SetHeartType(EHeart_Type::Double);

	else if (fPercent < 30.f)
		pHeart->SetHeartType(EHeart_Type::Normal);
}
