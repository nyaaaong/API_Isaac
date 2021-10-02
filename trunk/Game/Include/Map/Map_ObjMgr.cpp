
#include "Map.h"
#include "MapObj.h"
#include "../Scene/Scene.h"

bool CMap::IsSetObj(const Vector2& tPos, const Vector2& tObjSize)
{
	Vector2	tActLT = m_pScene->GetActivityLT();
	Vector2	tActRB = m_pScene->GetActivityRB();

	if ((tActLT.x <= tPos.x && tPos.x <= tActRB.x) &&	// 실제 플레이할 공간에서만 설치 가능하게
		(tActLT.y <= tPos.y && tPos.y <= tActRB.y) &&
		(tActLT.x <= tPos.x + tObjSize.x && tPos.x + tObjSize.x <= tActRB.x) &&
		(tActLT.y <= tPos.y + tObjSize.y && tPos.y + tObjSize.y <= tActRB.y))
	{
		std::list<CMapObj*>::iterator	iter = m_ObjList.begin();
		std::list<CMapObj*>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->IsObj(tPos, tObjSize)) // 설치한 자리에 다른 오브젝트가 있는 지
				return false;
		}

		return true;
	}

	return false;
}

void CMap::Create(EObject eObj, const Vector2& tPos, const Vector2& tObjSize)
{
	if (IsSetObj(tPos, tObjSize)) // 설치 가능한 구역이라면
	{
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
	std::list<CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CMapObj*>::iterator	iterEnd = m_ObjList.end();

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

	std::list<CMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}