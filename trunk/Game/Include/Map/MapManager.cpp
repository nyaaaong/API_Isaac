#include "MapManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"

CMapManager* CMapManager::m_pInst = nullptr;

CMapManager::CMapManager()	:
	m_bRoomShuffle(true),
	m_bIsEditor(false),
	m_bIsClear(false)
{
	m_mapSpecialRoomMap.reserve(3);
	m_vecRoomMap.reserve(10);
}

CMapManager::~CMapManager()
{
	{
		size_t iSize = m_vecRoomMap.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			SAFE_DELETE(m_vecRoomMap[i]);
		}

		m_vecRoomMap.clear();
	}

	{
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.begin();
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iterEnd = m_mapSpecialRoomMap.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapSpecialRoomMap.clear();
	}
}

bool CMapManager::Init()
{
	return true;
}

void CMapManager::RoomUpdater()
{
	{
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.begin();
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iterEnd = m_mapSpecialRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!iter->second->IsActive())
			{
				iter = m_mapSpecialRoomMap.erase(iter);
				iterEnd = m_mapSpecialRoomMap.end();
				continue;
			}

			else if (!iter->second->IsEnable())
			{
				++iter;
				continue;
			}

			++iter;
		}
	}

	{
		std::vector<CRoomMap*>::iterator	iter = m_vecRoomMap.begin();
		std::vector<CRoomMap*>::iterator	iterEnd = m_vecRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_vecRoomMap.erase(iter);
				iterEnd = m_vecRoomMap.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			++iter;
		}
	}
}

bool CMapManager::GetClearMap(int iIdx) const
{
	return m_vecRoomMap[iIdx - 1]->m_bIsClear;
}

bool CMapManager::GetClearSpecialMap(ESpecial_RoomType eType) const
{
	std::unordered_map<ESpecial_RoomType, CRoomMap*>::const_iterator	iter = m_mapSpecialRoomMap.find(eType);

	if (iter == m_mapSpecialRoomMap.end())
		return false;

	return iter->second->m_bIsClear;
}

void CMapManager::SetMap(CScene* pCurScene, int iIdx)
{
	size_t iSize = m_vecRoomMap.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecRoomMap[i]->m_bEnable = false;

		if (i == iIdx - 1)
		{
			m_vecRoomMap[i]->m_bEnable = true;

			pCurScene->m_pCurMap = m_vecRoomMap[i];
		}
	}
}

void CMapManager::SetClearMap(int iIdx)
{
	m_vecRoomMap[iIdx - 1]->m_bIsClear = true;
}

void CMapManager::SetSpecialMap(CScene* pCurScene, ESpecial_RoomType eType)
{
	std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.find(eType);

	if (iter == m_mapSpecialRoomMap.end())
		return;

	size_t iSize = m_vecRoomMap.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecRoomMap[i])
			m_vecRoomMap[i]->m_bEnable = false;
	}

	pCurScene->m_pCurMap = iter->second;
	pCurScene->m_pCurMap->m_bEnable = true;
}

void CMapManager::SetSpecialClearMap(ESpecial_RoomType eType)
{
	std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.find(eType);

	if (iter == m_mapSpecialRoomMap.end())
		return;

	iter->second->m_bIsClear = true;
}

void CMapManager::SaveFullPath(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "wb");

	if (!pFile)
		return;

	int	iSize = static_cast<int>(m_vecRoomMap.size());
	fwrite(&iSize, sizeof(int), 1, pFile);

	for (int i = 0; i < iSize; ++i)
	{
		m_vecRoomMap[i]->Save(pFile);
	}

	fclose(pFile);
}

void CMapManager::LoadFullPath(CScene* pCurScene, const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "rb");

	if (!pFile)
		return;

	int	iSize = 0;
	fread(&iSize, sizeof(int), 1, pFile);

	for (int i = 0; i < iSize; ++i)
	{
		CRoomMap* pMap = new CRoomMap;

		pMap->Load(pCurScene, pFile);

		if (!pMap->Init())
		{
			SAFE_DELETE(pMap);
			return;
		}

		if (m_bIsEditor)
		{
			SAFE_DELETE(m_vecRoomMap[i]); // 에디터에서 임시로 추가했던 방들을 제거하고
			m_vecRoomMap[i] = pMap; // 새로 저장한다.
		}

		else
			m_vecRoomMap.push_back(pMap);
	}

	fclose(pFile);

	if (m_bRoomShuffle)
		RoomShuffle();
}

void CMapManager::RoomMapClear()
{
	{
		size_t iSize = m_vecRoomMap.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			SAFE_DELETE(m_vecRoomMap[i]);
		}

		m_vecRoomMap.clear();
	}

	m_vecRoomMap.reserve(10);
}

void CMapManager::CreateRoomMap(CScene* pCurScene, const std::string& strName, int iRoomNum, const Vector2& tPos, const Vector2& tSize)
{
	CRoomMap* pMap = new CRoomMap;

	pMap->SetRoomNumber(iRoomNum);
	pMap->SetPos(tPos);
	pMap->SetSize(tSize);
	pMap->SetName(strName);

	if (!pMap->Init())
	{
		SAFE_DELETE(pMap);
		return;
	}

	m_vecRoomMap.push_back(pMap);
}

void CMapManager::CreateSpecialRoomMap(CScene* pCurScene, ESpecial_RoomType eType, const Vector2& tPos, const Vector2& tSize)
{
	std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.find(eType);

	if (iter != m_mapSpecialRoomMap.end())
		return;

	CRoomMap* pMap = new CRoomMap;

	pMap->SetPos(tPos);
	pMap->SetSize(tSize);
	pMap->SetSpecialRoomMap(true);
	pMap->SetSpecialRoomType(eType);

	if (!pMap->Init())
	{
		SAFE_DELETE(pMap);
		return;
	}

	m_mapSpecialRoomMap.insert(std::make_pair(eType, pMap));
}

void CMapManager::RoomShuffle()
{
	int iSize = static_cast<int>(m_vecRoomMap.size());

	int	Idx1 = 0, Idx2 = 0;
	CRoomMap* pTemp = nullptr;

	for (int i = 0; i < 30; ++i)
	{
		Idx1 = rand() % iSize;
		Idx2 = rand() % iSize;

		pTemp = m_vecRoomMap[Idx1];
		m_vecRoomMap[Idx1] = m_vecRoomMap[Idx2];
		m_vecRoomMap[Idx2] = pTemp;
	}
}
