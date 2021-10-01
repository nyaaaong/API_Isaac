
#include "Stage.h"
#include "../PathManager.h"

void CStage::LoadMap()
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(MAP_PATH);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, "Map.dat");

	CScene::Load(cFullPath);
}