
#include "Scene.h"
#include "SceneResource.h"
#include "SceneCollision.h"
#include "Camera.h"
#include "../GameManager.h"
#include "../Map/RoomMap.h"

bool CScene::Init()
{
	GetSceneResource()->SetVolume("BGM", 10);
	GetSceneResource()->SetVolume("Effect", 30);

	Resolution	tRS = CGameManager::GetInst()->GetResolution();

	SetFieldLT(Vector2(140.f, 120.f));	// 활동 구역의 시작 위치
	SetFieldRB(Vector2(tRS.iW - 140.f, tRS.iH - 120.f));	// 활동 구역의 크기

	Init_CreateTextureObject();

	return true;
}

void CScene::Start()
{
	m_bStart = true;
}

bool CScene::Update(float fTime)
{
	if (m_pPlayer)
		m_pPlayer->Update(fTime);

	if (m_pPlayerBody)
		m_pPlayerBody->Update(fTime);

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

			else if (!(*iter)->IsEnable())
			{
				++iter;
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

			else if (!m_pArrUI[i]->IsEnable())
			{
				++i;
				continue;
			}

			m_pArrUI[i]->Update(fTime);
			++i;
		}
	}

	if (m_mapSpecialRoomMap.size() != 0)
	{
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.begin();
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iterEnd = m_mapSpecialRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!iter->second->IsActive())
			{
				iter = m_mapSpecialRoomMap.erase(iter);
				iterEnd = m_mapSpecialRoomMap.end();
				continue;
			}

			else if (!iter->second->IsEnable())
			{
				++iter;
				continue;
			}

			iter->second->Update(fTime);
			++iter;
		}
	}

	else
	{
		std::vector<CRoomMap*>::iterator	iter = m_vecRoomMap.begin();
		std::vector<CRoomMap*>::iterator	iterEnd = m_vecRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_vecRoomMap.erase(iter);
				iterEnd = m_vecRoomMap.end();
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

	return true;}

bool CScene::PostUpdate(float fTime)
{
	if (m_pPlayer)
		m_pPlayer->PostUpdate(fTime);

	if (m_pPlayerBody)
		m_pPlayerBody->PostUpdate(fTime);

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

			else if (!(*iter)->IsEnable())
			{
				++iter;
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

			else if (!m_pArrUI[i]->IsEnable())
			{
				++i;
				continue;
			}

			m_pArrUI[i]->PostUpdate(fTime);
			++i;
		}
	}

	m_pCamera->Update(fTime);


	if (m_mapSpecialRoomMap.size() != 0)
	{
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.begin();
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iterEnd = m_mapSpecialRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!iter->second->IsActive())
			{
				iter = m_mapSpecialRoomMap.erase(iter);
				iterEnd = m_mapSpecialRoomMap.end();
				continue;
			}

			else if (!iter->second->IsEnable())
			{
				++iter;
				continue;
			}

			iter->second->PostUpdate(fTime);
			++iter;
		}
	}

	else
	{
		std::vector<CRoomMap*>::iterator	iter = m_vecRoomMap.begin();
		std::vector<CRoomMap*>::iterator	iterEnd = m_vecRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_vecRoomMap.erase(iter);
				iterEnd = m_vecRoomMap.end();
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

	return true;}

bool CScene::Collision(float fTime)
{
	if (m_pPlayer)
		m_pPlayer->Collision(fTime);

	if (m_pPlayerBody)
		m_pPlayerBody->Collision(fTime);

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
			if (!(*iter)->IsEnable())
			{
				++iter;
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

			else if (!m_pArrUI[i]->IsEnable())
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

	return true;}

bool CScene::Render(HDC hDC)
{
	if (m_mapSpecialRoomMap.size() != 0)
	{
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.begin();
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iterEnd = m_mapSpecialRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!iter->second->IsActive())
			{
				iter = m_mapSpecialRoomMap.erase(iter);
				iterEnd = m_mapSpecialRoomMap.end();
				continue;
			}

			else if (!iter->second->IsEnable())
			{
				++iter;
				continue;
			}

			iter->second->Render(hDC);
			++iter;
		}
	}

	else
	{
		std::vector<CRoomMap*>::iterator	iter = m_vecRoomMap.begin();
		std::vector<CRoomMap*>::iterator	iterEnd = m_vecRoomMap.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_vecRoomMap.erase(iter);
				iterEnd = m_vecRoomMap.end();
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

	if (m_pPlayerBody)
		m_pPlayerBody->PrevRender();

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
			
			else if (!(*iter)->IsEnable())
			{
				++iter;
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

	if (m_pPlayerBody)
	{
		if (!m_pPlayerBody->IsCull())
		{
			m_pArrRender[m_iRenderCount] = m_pPlayerBody;
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

CScene::CScene()	:
	m_pCurMap(nullptr),
	m_bStart(false)
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

	m_vecRoomMap.reserve(20);
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
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.begin();
		std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iterEnd = m_mapSpecialRoomMap.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapSpecialRoomMap.clear();
	}

	{
		size_t iSize = m_vecRoomMap.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			SAFE_DELETE(m_vecRoomMap[i]);
		}

		m_vecRoomMap.clear();
	}

	SAFE_DELETE_ARRAY(m_pArrUI);

	m_ObjList.clear();

	m_mapPrototype.clear();

	m_pPlayer = nullptr;

	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pResource);
}
