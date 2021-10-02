
#include "RoomMap.h"
#include "RoomMapObj.h"
#include "../Scene/Scene.h"

bool CRoomMap::IsSetObj(const Vector2& tPos, const Vector2& tObjSize)
{
	Vector2	tActLT = m_pScene->GetActivityLT();
	Vector2	tActRB = m_pScene->GetActivityRB();

	if ((tActLT.x <= tPos.x && tPos.x <= tActRB.x) &&	// 실제 플레이할 공간에서만 설치 가능하게
		(tActLT.y <= tPos.y && tPos.y <= tActRB.y) &&
		(tActLT.x <= tPos.x + tObjSize.x && tPos.x + tObjSize.x <= tActRB.x) &&
		(tActLT.y <= tPos.y + tObjSize.y && tPos.y + tObjSize.y <= tActRB.y))
	{
		std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
		std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->IsObj(tPos, tObjSize)) // 설치한 자리에 다른 오브젝트가 있는 지
				return false;
		}

		return true;
	}

	return false;
}

void CRoomMap::Create(EObject eObj, const Vector2& tPos, const Vector2& tObjSize)
{
	if (IsSetObj(tPos, tObjSize)) // 설치 가능한 구역이라면
	{
		CRoomMapObj* pRoomMapObj = new CRoomMapObj;

		pRoomMapObj->SetScene(m_pScene);
		pRoomMapObj->SetObject(eObj);
		pRoomMapObj->SetPos(tPos);
		pRoomMapObj->SetSize(tObjSize);

		if (!pRoomMapObj->Init())
		{
			SAFE_DELETE(pRoomMapObj);
			return;
		}

		m_ObjList.push_back(pRoomMapObj);
	}
}

void CRoomMap::Delete(const Vector2& tPos)
{
	std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

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

void CRoomMap::Clear()
{
	if (!m_pScene)
		return;

	std::list<CRoomMapObj*>::iterator	iter = m_ObjList.begin();
	std::list<CRoomMapObj*>::iterator	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_ObjList.clear();
}