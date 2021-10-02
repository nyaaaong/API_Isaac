
#include "Map.h"
#include "MapObj.h"
#include "../PathManager.h"

void CMap::Save(FILE* pFile)
{
	int	iLength = static_cast<int>(m_strName.length());
	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_strName.c_str(), sizeof(char), iLength, pFile);

	fwrite(&m_tPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_tSize, sizeof(Vector2), 1, pFile);

	fwrite(&m_bEnable, sizeof(bool), 1, pFile);
	fwrite(&m_bActive, sizeof(bool), 1, pFile);

	fwrite(&m_iRoomNum, sizeof(int), 1, pFile);

	int	iSize = static_cast<int>(m_ObjList.size());
	fwrite(&iSize, sizeof(int), 1, pFile);

	std::list<CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (int i = 0; i < iSize; ++i)
	{
		(*iter)->Save(pFile);
		++iter;
	}
}

void CMap::SaveFile(const char* cFileName, const std::string& strPath)
{
	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(cFileName);

	if (pInfo)
		strcpy_s(cFullPath, pInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	SaveFullPath(cFullPath);
}

void CMap::SaveFullPath(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "wb");

	if (!pFile)
		return;

	Save(pFile);

	fclose(pFile);
}