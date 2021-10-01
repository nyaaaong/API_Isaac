#include "PathManager.h"

CPathManager* CPathManager::m_pInst = nullptr;

bool CPathManager::Init()
{
	TCHAR	cPath[MAX_PATH] = {};

	// ��ü��θ� ���� Ȯ���ڱ��� �� �ҷ��´�.
	GetModuleFileName(0, cPath, MAX_PATH);

	long long iLength = lstrlen(cPath);

	// ��ü ����� �ڿ������� ã�´�
	for (long long i = iLength - 1; i > 0; --i)
	{
		// ��ο��� \�� ã�´�.
		if (cPath[i] == '\\')
		{
			// ����� �ڿ������� ã�� \ ����. �� ���� ���� ����.exe �� �����ؼ�
			// Root ������ �����Ѵ�.
			memset(&cPath[i + 1], 0, sizeof(TCHAR) * (iLength - i - 1));
			break;
		}
	}

	PathInfo* pInfo = new PathInfo;

	lstrcpy(pInfo->cPath, cPath);

#ifdef UNICODE // �����ڵ�

	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, cPath, -1, nullptr, 0, 0, 0);

	// �����ڵ� ���ڿ��� ��Ƽ����Ʈ�� ��ȯ�Ѵ�.
	WideCharToMultiByte(CP_ACP, 0, cPath, -1, pInfo->cPathMultibyte, iConvertLength, 0, 0);

#else	// ��Ƽ����Ʈ
	strcpy_s(pInfo->cPathMultibyte, cPath);
#endif

	m_mapPath.insert(std::make_pair(ROOT_PATH, pInfo));

	AddPath(TEXTURE_PATH, TEXT("Texture\\"));
	AddPath(SOUND_PATH, TEXT("Sound\\"));
	AddPath(MAP_PATH, TEXT("Map\\"));

	return true;
}

bool CPathManager::AddPath(const std::string& strName, const TCHAR* cPath, const std::string& strBaseName)
{
	if (FindPath(strName))
		return false;

	const PathInfo* pBaseInfo = FindPath(strBaseName);

	if (!pBaseInfo)
		return false;

	PathInfo* pInfo = new PathInfo;

	lstrcpy(pInfo->cPath, pBaseInfo->cPath);
	lstrcat(pInfo->cPath, cPath);

#ifdef UNICODE // �����ڵ�

	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, pInfo->cPath, -1, nullptr, 0, 0, 0);

	// �����ڵ� ���ڿ��� ��Ƽ����Ʈ�� ��ȯ�Ѵ�.
	WideCharToMultiByte(CP_ACP, 0, pInfo->cPath, -1, pInfo->cPathMultibyte, iConvertLength, 0, 0);

#else	// ��Ƽ����Ʈ
	strcpy_s(pInfo->cPathMultibyte, cPath);
#endif

	m_mapPath.insert(std::make_pair(strName, pInfo));

	return true;
}

const PathInfo* CPathManager::FindPath(const std::string& strName)
{
	std::unordered_map<std::string, PathInfo*>::iterator	iter = m_mapPath.find(strName);

	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second;
}

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
	std::unordered_map<std::string, PathInfo*>::iterator	iter = m_mapPath.begin();
	std::unordered_map<std::string, PathInfo*>::iterator	iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}
