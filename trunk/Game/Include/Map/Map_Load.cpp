
#include "RoomMap.h"
#include "RoomMapObj.h"
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
		CRoomMapObj* pRoomMapObj = new CRoomMapObj;

		pRoomMapObj->SetScene(m_pScene);
		pRoomMapObj->Load(pFile);

		if (!pRoomMapObj->Init())
		{
			SAFE_DELETE(pRoomMapObj);
			return;
		}

		m_ObjList.push_back(pRoomMapObj);
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
