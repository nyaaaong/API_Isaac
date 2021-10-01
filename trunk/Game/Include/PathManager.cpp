#include "PathManager.h"

CPathManager* CPathManager::m_pInst = nullptr;

bool CPathManager::Init()
{
	TCHAR	cPath[MAX_PATH] = {};

	// 전체경로를 현재 확장자까지 쭉 불러온다.
	GetModuleFileName(0, cPath, MAX_PATH);

	long long iLength = lstrlen(cPath);

	// 전체 경로의 뒤에서부터 찾는다
	for (long long i = iLength - 1; i > 0; --i)
	{
		// 경로에서 \를 찾는다.
		if (cPath[i] == '\\')
		{
			// 경로의 뒤에서부터 찾은 \ 다음. 즉 현재 실행 파일.exe 만 제거해서
			// Root 폴더를 지정한다.
			memset(&cPath[i + 1], 0, sizeof(TCHAR) * (iLength - i - 1));
			break;
		}
	}

	PathInfo* pInfo = new PathInfo;

	lstrcpy(pInfo->cPath, cPath);

#ifdef UNICODE // 유니코드

	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, cPath, -1, nullptr, 0, 0, 0);

	// 유니코드 문자열을 멀티바이트로 전환한다.
	WideCharToMultiByte(CP_ACP, 0, cPath, -1, pInfo->cPathMultibyte, iConvertLength, 0, 0);

#else	// 멀티바이트
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

#ifdef UNICODE // 유니코드

	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, pInfo->cPath, -1, nullptr, 0, 0, 0);

	// 유니코드 문자열을 멀티바이트로 전환한다.
	WideCharToMultiByte(CP_ACP, 0, pInfo->cPath, -1, pInfo->cPathMultibyte, iConvertLength, 0, 0);

#else	// 멀티바이트
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
