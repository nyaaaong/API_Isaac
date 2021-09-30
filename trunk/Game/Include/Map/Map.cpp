#include "Map.h"
#include "MapObj.h"
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
	m_tObjSize = tObjSize;

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
		pMapObj->SetSize(m_tObjSize);

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
	std::list<class CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<class CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}

CMap::CMap()	:
	m_bEnable(true),
	m_bActive(true),
	m_iRoomNum(1),
	m_eObject(OBJ_ROCK),
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
