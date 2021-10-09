
#include "RoomMap.h"
#include "RoomObj.h"
#include "../PathManager.h"

void CRoomMap::Save(FILE* pFile)
{
	int	iLength = static_cast<int>(m_strName.length());
	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_strName.c_str(), sizeof(char), iLength, pFile);

	fwrite(&m_tPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_tSize, sizeof(Vector2), 1, pFile);

	fwrite(&m_bEnable, sizeof(bool), 1, pFile);
	fwrite(&m_bActive, sizeof(bool), 1, pFile);

	fwrite(&m_iRoomNum, sizeof(int), 1, pFile);

	int	iSize = static_cast<int>(m_RoomObjList.size());
	fwrite(&iSize, sizeof(int), 1, pFile);

	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (int i = 0; i < iSize; ++i)
	{
		(*iter)->Save(pFile);
		++iter;
	}
}

void CRoomMap::SaveFile(const char* cFileName, const std::string& strPath)
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(cFileName);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	SaveFullPath(cFullPath);
}

void CRoomMap::SaveFullPath(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "wb");

	if (!pFile)
		return;

	Save(pFile);

	fclose(pFile);
}