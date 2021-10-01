#include "Map.h"
#include "MapObj.h"
#include "../PathManager.h"
#include "../Scene/Scene.h"
#include "../Resource/ResourceManager.h"

bool CMap::Init()
{
	m_pBackGround = CResourceManager::GetInst()->FindTexture("BackGround");

	return true;
}

void CMap::Start()
{
}

void CMap::Update(float fTime)
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(fTime);
	}
}

void CMap::PostUpdate(float fTime)
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(fTime);
	}
}

void CMap::Render(HDC hDC)
{
	if (m_pBackGround)
		m_pBackGround->Render(hDC, Vector2(), Vector2(), Vector2(1280.f, 720.f));

	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC);
	}
}

void CMap::Create(EObject eObj, const Vector2& tPos, const Vector2& tObjSize)
{
	Vector2	tActLT = m_pScene->GetActivityLT();
	Vector2	tActRB = m_pScene->GetActivityRB();

	if ((tActLT.x <= tPos.x && tPos.x <= tActRB.x) &&	// 실제 플레이할 공간에서만 설치 가능하게
		(tActLT.y <= tPos.y && tPos.y <= tActRB.y) &&
		(tActLT.x <= tPos.x + tObjSize.x && tPos.x + tObjSize.x <= tActRB.x) &&
		(tActLT.y <= tPos.y + tObjSize.y && tPos.y + tObjSize.y <= tActRB.y))
	{
		std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
		std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->IsObj(tPos, tObjSize)) // 설치한 자리에 다른 오브젝트가 있는 지
				return;
		}

		CMapObj* pMapObj = new CMapObj;

		pMapObj->SetScene(m_pScene);
		pMapObj->SetObject(eObj);
		pMapObj->SetPos(tPos);
		pMapObj->SetSize(tObjSize);

		if (!pMapObj->Init())
		{
			SAFE_DELETE(pMapObj);
			return;
		}

		m_ObjList.push_back(pMapObj);
	}
}

void CMap::Delete(const Vector2& tPos)
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsObj(tPos)) // 설치한 자리에 다른 오브젝트가 있는 지
		{
			SAFE_DELETE((*iter));
			m_ObjList.erase(iter);
			return;
		}
	}
}

void CMap::Clear()
{
	if (!m_pScene)
		return;

	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}

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

	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();
	
	for (int i = 0; i < iSize; ++i)
	{
		(*iter)->Save(pFile);
		++iter;
	}
}

void CMap::Save(const char* cFileName, const std::string& strPath)
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

void CMap::Load(const char* cFileName, const std::string& strPath)
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

CMap::CMap()	:
	m_bEnable(true),
	m_bActive(true),
	m_iRoomNum(1),
	m_pScene(nullptr)
{
}

CMap::~CMap()
{
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}
