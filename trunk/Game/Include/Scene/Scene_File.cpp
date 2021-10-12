
#include "Scene.h"
#include "../PathManager.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

void CScene::SaveFullPath(const char* cFullPath)
{
	if (CMapManager::GetInst()->HasRoomMap())
		return;

	CMapManager::GetInst()->SaveFullPath(cFullPath);
}

void CScene::SaveFile(const char* cFileName, const std::string& strPath)
{
	if (CMapManager::GetInst()->HasRoomMap())
		return;

	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(cFileName);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	SaveFullPath(cFullPath);
}

void CScene::LoadFullPath(const char* cFullPath)
{
	if (CMapManager::GetInst()->HasRoomMap())
		return;

	CMapManager::GetInst()->LoadFullPath(this, cFullPath);
}

void CScene::LoadFile(const char* cFileName, const std::string& strPath)
{
	if (CMapManager::GetInst()->HasRoomMap())
		return;

	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(strPath);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	LoadFullPath(cFullPath);
}