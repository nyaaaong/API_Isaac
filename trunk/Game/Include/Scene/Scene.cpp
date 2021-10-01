
#include "Scene.h"
#include "SceneResource.h"
#include "SceneCollision.h"
#include "Camera.h"
#include "../GameManager.h"
#include "../Map/Map.h"
#include "../Map/MapObj.h"
#include "../Resource/ResourceManager.h"

bool CScene::Init()
{
	GetSceneResource()->SetVolume("BGM", 10);
	GetSceneResource()->SetVolume("Effect", 30);

	Resolution	tRS = CGameManager::GetInst()->GetResolution();

	SetActivityLT(Vector2(140.f, 120.f));	// 활동 구역의 시작 위치
	SetActivityRB(Vector2(tRS.iW - 140.f, tRS.iH - 120.f));	// 활동 구역의 크기

	CreateTextureObject();

	return true;
}

void CScene::SetMap(const std::string& strName, int iRoomNum)
{
	std::list<CMap*>::iterator	iter = m_MapList.begin();
	std::list<CMap*>::iterator	iterEnd = m_MapList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->m_bEnable = false;

		if ((*iter)->GetName() == strName && (*iter)->GetRoomNumber() == iRoomNum)
		{
			(*iter)->m_bEnable = true;
			m_pCurMap = (*iter);
		}
	}
}

CObj* CScene::FindPrototype(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CObj>>::iterator	iter = m_mapPrototype.find(strName);

	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}

CObj* CScene::FindObject(const std::string& strName)
{
	std::list<CSharedPtr<CObj>>::iterator iter = m_ObjList.begin();
	std::list<CSharedPtr<CObj>>::iterator iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
			return (*iter);
	}

	return nullptr;
}

void CScene::SetPlayer(const std::string& strName)
{
	CObj* pPlayer = FindObject(strName);

	SetPlayer(pPlayer);
}

void CScene::SetPlayer(CObj* pPlayer)
{
	if (!pPlayer)
		assert(!("if (!pPlayer)"));

	m_pPlayer = pPlayer;

	std::list<CSharedPtr<CObj>>::iterator	iter = m_ObjList.begin();
	std::list<CSharedPtr<CObj>>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pPlayer)
		{
			m_ObjList.erase(iter);
			return;
		}
	}
}

CSceneResource* CScene::GetSceneResource() const
{
	return m_pResource;
}

CSceneCollision* CScene::GetSceneCollision() const
{
	return m_pCollision;
}

CCamera* CScene::GetCamera() const
{
	return m_pCamera;
}

int CScene::SortY(const void* pSrc, const void* pDest)
{
	CObj* pSrcObj = *(CObj**)pSrc;
	CObj* pDestObj = *(CObj**)pDest;

	float	fSrcY = pSrcObj->GetBottom();
	float	fDestY = pDestObj->GetBottom();

	if (fSrcY < fDestY)
		return -1;

	else if (fSrcY > fDestY)
		return 1;

	return 0;
}

int CScene::SortUIZOrder(const void* pSrc, const void* pDest)
{
	CUIWindow* pSrcObj = *(CUIWindow**)pSrc;
	CUIWindow* pDestObj = *(CUIWindow**)pDest;

	int iSrcZ = pSrcObj->GetZOrder();
	int iDestZ = pDestObj->GetZOrder();

	if (iSrcZ > iDestZ)
		return -1;

	else if (iSrcZ < iDestZ)
		return 1;

	return 0;
}

int CScene::SortObjZOrder(const void* pSrc, const void* pDest)
{
	CObj* pSrcObj = *(CObj**)pSrc;
	CObj* pDestObj = *(CObj**)pDest;

	int iSrcZ = pSrcObj->GetZOrder();
	int iDestZ = pDestObj->GetZOrder();

	if (iSrcZ > iDestZ)
		return -1;

	else if (iSrcZ < iDestZ)
		return 1;

	return 0;
}

bool CScene::Update(float fTime)
{
	if (m_pPlayer)
		m_pPlayer->Update(fTime);

	{
		std::list<CSharedPtr<CObj>>::iterator	iter = m_ObjList.begin();
		std::list<CSharedPtr<CObj>>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->Update(fTime * (*iter)->m_fTimeScale);
			++iter;
		}
	}

	{
		for (int i = 0; i < m_iUICount;)
		{
			if (!m_pArrUI[i]->IsActive())
			{
				--m_iUICount;

				for (int j = i; j < m_iUICount; ++j)
				{
					m_pArrUI[j] = m_pArrUI[j + 1];
				}

				continue;
			}

			else if (!m_pArrUI[i]->GetVisibility())
			{
				++i;
				continue;
			}

			m_pArrUI[i]->Update(fTime);
			++i;
		}
	}

	return true;
}

bool CScene::PostUpdate(float fTime)
{
	if (m_pPlayer)
		m_pPlayer->PostUpdate(fTime);

	{
		std::list<CSharedPtr<CObj>>::iterator	iter = m_ObjList.begin();
		std::list<CSharedPtr<CObj>>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->PostUpdate(fTime * (*iter)->m_fTimeScale);
			++iter;
		}
	}

	{
		for (int i = 0; i < m_iUICount;)
		{
			if (!m_pArrUI[i]->IsActive())
			{
				--m_iUICount;

				for (int j = i; j < m_iUICount; ++j)
				{
					m_pArrUI[j] = m_pArrUI[j + 1];
				}

				continue;
			}

			else if (!m_pArrUI[i]->GetVisibility())
			{
				++i;
				continue;
			}

			m_pArrUI[i]->PostUpdate(fTime);
			++i;
		}
	}

	m_pCamera->Update(fTime);

	{
		std::list<CMap*>::iterator	iter = m_MapList.begin();
		std::list<CMap*>::iterator	iterEnd = m_MapList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_MapList.erase(iter);
				iterEnd = m_MapList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(fTime);
			++iter;
		}
	}

	{
		std::list<CMap*>::iterator	iter = m_MapList.begin();
		std::list<CMap*>::iterator	iterEnd = m_MapList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_MapList.erase(iter);
				iterEnd = m_MapList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(fTime);
			++iter;
		}
	}

	return true;
}

bool CScene::Collision(float fTime)
{
	if (m_pPlayer)
		m_pPlayer->Collision(fTime);

	{
		std::list<CSharedPtr<CObj>>::iterator	iter = m_ObjList.begin();
		std::list<CSharedPtr<CObj>>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->Collision(fTime * (*iter)->m_fTimeScale);
			++iter;
		}
	}

	{
		if (m_iUICount >= 2)
			qsort(m_pArrUI, static_cast<size_t>(m_iUICount), sizeof(CUIWindow*), CScene::SortUIZOrder);

		for (int i = 0; i < m_iUICount;)
		{
			if (!m_pArrUI[i]->IsActive())
			{
				--m_iUICount;

				for (int j = i; j < m_iUICount; ++j)
				{
					m_pArrUI[j] = m_pArrUI[j + 1];
				}

				continue;
			}

			else if (!m_pArrUI[i]->GetVisibility())
			{
				++i;
				continue;
			}

			m_pArrUI[i]->Collision(fTime);
			m_pCollision->AddUIWindow(m_pArrUI[i]);
			++i;
		}
	}

	m_pCollision->Collision(fTime);

	return true;
}

bool CScene::Render(HDC hDC)
{
	{
		std::list<CMap*>::iterator	iter = m_MapList.begin();
		std::list<CMap*>::iterator	iterEnd = m_MapList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_MapList.erase(iter);
				iterEnd = m_MapList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC);
			++iter;
		}
	}

	if (m_pPlayer)
		m_pPlayer->PrevRender();

	{
		std::list<CSharedPtr<CObj>>::iterator	iter = m_ObjList.begin();
		std::list<CSharedPtr<CObj>>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->PrevRender();

			if (!(*iter)->IsCull())
			{
				if (m_iRenderCount == m_iRenderCapacity)
				{
					m_iRenderCapacity *= 2;

					CObj** pArr = new CObj * [m_iRenderCapacity];

					memcpy(pArr, m_pArrRender, sizeof(CObj*) * m_iRenderCount);

					SAFE_DELETE_ARRAY(m_pArrRender);

					m_pArrRender = pArr;
				}

				m_pArrRender[m_iRenderCount] = *iter;
				++m_iRenderCount;
			}

			++iter;
		}
	}

	if (m_iRenderCount == m_iRenderCapacity)
	{
		m_iRenderCapacity *= 2;

		CObj** pArr = new CObj * [m_iRenderCapacity];

		memcpy(pArr, m_pArrRender, sizeof(CObj*) * m_iRenderCount);

		SAFE_DELETE_ARRAY(m_pArrRender);

		m_pArrRender = pArr;
	}

	if (m_pPlayer)
	{
		if (!m_pPlayer->IsCull())
		{
			m_pArrRender[m_iRenderCount] = m_pPlayer;
			++m_iRenderCount;
		}
	}

	qsort(m_pArrRender, static_cast<size_t>(m_iRenderCount), sizeof(CObj*), CScene::SortY);
	qsort(m_pArrRender, static_cast<size_t>(m_iRenderCount), sizeof(CObj*), CScene::SortObjZOrder);

	for (int i = 0; i < m_iRenderCount; ++i)
	{
		m_pArrRender[i]->Render(hDC);
	}

	m_iRenderCount = 0;

	{
		for (int i = 0; i < m_iUICount;)
		{
			if (!m_pArrUI[i]->IsActive())
			{
				--m_iUICount;

				for (int j = i; j < m_iUICount; ++j)
				{
					m_pArrUI[j] = m_pArrUI[j + 1];
				}

				continue;
			}

			++i;
		}

		for (int i = m_iUICount - 1; i >= 0;)
		{
			if (!m_pArrUI[i]->GetVisibility())
			{
				--i;
				continue;
			}

			m_pArrUI[i]->Render(hDC);
			--i;
		}
	}

	return true;
}

void CScene::CreateTextureObject()
{
	for (int i = OBJ_ROCK; i < OBJ_MAX; ++i)
	{
		// 경로
		TCHAR	cPath[MAX_PATH] = {};
		wsprintf(cPath, TEXT("Room/Object/%d.bmp"), i);

		// 텍스쳐명
		char	cTextureName[32] = "Object";

		// 번호를 문자로
		char cNum[16] = {};
		sprintf_s(cNum, "%d", i);

		// 텍스쳐명 + 숫자
		strcat_s(cTextureName, cNum);

		CResourceManager::GetInst()->LoadTexture(cTextureName, cPath);
	}

	CResourceManager::GetInst()->LoadTexture("BackGround", TEXT("Room/Room.bmp"));
}

void CScene::Save(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "wb");

	if (!pFile)
		return;

	int	iSize = static_cast<int>(m_MapList.size());
	fwrite(&iSize, sizeof(int), 1, pFile);

	std::list<CMap*>::iterator	iter = m_MapList.begin();

	for (int i = 0; i < iSize; ++i)
	{
		(*iter)->Save(pFile);
		++iter;
	}

	fclose(pFile);
}

void CScene::Load(const char* cFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, cFullPath, "rb");

	if (!pFile)
		return;

	{
		std::list<CMap*>::iterator	iter = m_MapList.begin();
		std::list<CMap*>::iterator	iterEnd = m_MapList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE((*iter));
		}

		m_MapList.clear();
	}

	int	iSize = 0;
	fread(&iSize, sizeof(int), 1, pFile);

	for (int i = 0; i < iSize; ++i)
	{
		CMap* pMap = new CMap;

		pMap->SetScene(this);
		pMap->Load(pFile);

		if (!pMap->Init())
		{
			SAFE_DELETE(pMap);
			return;
		}

		pMap->Start();

		m_MapList.push_back(pMap);
	}

	fclose(pFile);
}

CScene::CScene()	:
	m_pCurMap(nullptr)
{
	m_pResource = new CSceneResource;
	m_pCollision = new CSceneCollision;
	m_pCollision->m_pScene = this;

	m_iRenderCount = 0;
	m_iRenderCapacity = 100;
	m_pArrRender = new CObj * [m_iRenderCapacity];

	m_iUICount = 0;
	m_iUICapacity = 10;
	m_pArrUI = new CUIWindow * [m_iUICapacity];

	m_pCamera = new CCamera;
	m_pCamera->Init();
}

CScene::~CScene()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE_ARRAY(m_pArrRender);

	for (int i = 0; i < m_iUICount; ++i)
	{
		SAFE_RELEASE(m_pArrUI[i]);
	}

	{
		std::list<CMap*>::iterator	iter = m_MapList.begin();
		std::list<CMap*>::iterator	iterEnd = m_MapList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE((*iter));
		}

		m_MapList.clear();
	}

	SAFE_DELETE_ARRAY(m_pArrUI);

	m_ObjList.clear();

	m_mapPrototype.clear();

	m_pPlayer = nullptr;

	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pResource);
}
