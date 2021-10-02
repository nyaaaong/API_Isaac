
#include "Map.h"
#include "MapObj.h"
#include "../PathManager.h"

void CMap::Load(FILE* pFile)
{
	int	iLength = 0;
	fread(&iLength, sizeof(int), 1, pFile);

	char	cName[64] = {};
	fread(cName, sizeof(char), iLength, pFile);
	m_strName = cName;

	fread(&m_tPos, sizeof(Vector2), 1, pFile);
	fread(&m_tSize, sizeof(Vector2), 1, pFile);

	fread(&m_bEnable, sizeof(bool), 1, pFile);
	fread(&m_bActive, sizeof(bool), 1, pFile);

	fread(&m_iRoomNum, sizeof(int), 1, pFile);

	int	iSize = 0;
	fread(&iSize, sizeof(int), 1, pFile);

	for (int i = 0; i < iSize; ++i)
	{
		CMapObj* pMapObj = new CMapObj;

		pMapObj->SetScene(m_pScene);
		pMapObj->Load(pFile);

		if (!pMapObj->Init())
		{
			SAFE_DELETE(pMapObj);
			return;
		}

		m_ObjList.push_back(pMapObj);
	}
}

void CMap::LoadFile(const char* cFileName, const std::string& strPath)
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(cFileName);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	LoadFullPath(cFullPath);
}

void CMap::LoadFullPath(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "rb");

	if (!pFile)
		return;

	Load(pFile);

	fclose(pFile);
}
