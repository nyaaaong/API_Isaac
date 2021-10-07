
#include "RoomMap.h"
#include "RoomObj.h"
#include "../PathManager.h"

void CRoomMap::Load(FILE* pFile)
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
		CRoomObj* pRoomObj = new CRoomObj;

		pRoomObj->SetScene(m_pScene);
		pRoomObj->Load(pFile);

		if (!pRoomObj->Init())
		{
			SAFE_DELETE(pRoomObj);
			return;
		}

		m_RoomObjList.push_back(pRoomObj);
	}
}

void CRoomMap::LoadFile(const char* cFileName, const std::string& strPath)
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(cFileName);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	LoadFullPath(cFullPath);
}

void CRoomMap::LoadFullPath(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "rb");

	if (!pFile)
		return;

	Load(pFile);

	fclose(pFile);
}
