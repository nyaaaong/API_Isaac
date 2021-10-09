
#include "Scene.h"
#include "../PathManager.h"
#include "../Map/RoomMap.h"

void CScene::SaveFullPath(const char* cFullPath)
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

void CScene::SaveFile(const char* cFileName, const std::string& strPath)
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(cFileName);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	SaveFullPath(cFullPath);
}

void CScene::LoadFullPath(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "rb");

	if (!pFile)
		return;

	int	iSize = 0;
	fread(&iSize, sizeof(int), 1, pFile);

	m_vecRoomMap.resize(iSize);

	for (int i = 0; i < iSize; ++i)
	{
		CRoomMap* pMap = new CRoomMap;

		pMap->SetScene(this);
		pMap->Load(pFile);

		if (!pMap->Init())
		{
			SAFE_DELETE(pMap);
			return;
		}

		m_vecRoomMap[i] = pMap;
	}

	fclose(pFile);
}

void CScene::LoadFile(const char* cFileName, const std::string& strPath)
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(strPath);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	LoadFullPath(cFullPath);
}