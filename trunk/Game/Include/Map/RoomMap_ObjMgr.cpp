
#include "RoomMap.h"
#include "RoomObj.h"
#include "../Scene/Scene.h"

bool CRoomMap::IsObj(CScene* pCurScene, const Vector2& tPos, EMapObject_Type eType)
{
	std::list<CRoomObj*>::const_iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::const_iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetType() == eType)
		{
			if ((*iter)->IsObj(pCurScene, tPos))
				return true;
		}
	}

	return false;
}

bool CRoomMap::IsObj(CScene* pCurScene, const Vector2& tStartPos, const Vector2& tEndPos, EMapObject_Type eType)
{
	std::list<CRoomObj*>::const_iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::const_iterator	iterEnd = m_RoomObjList.end();

	Vector2	tPos = tStartPos;

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetType() == eType)
		{
			do
			{
				if ((*iter)->IsObj(pCurScene, tPos))
					return true;

				tPos += tEndPos * 0.1f;

			} while (tPos == tEndPos);
		}
	}

	return false;
}

bool CRoomMap::IsObj(CScene* pCurScene, float x, float y, EMapObject_Type eType)
{
    return IsObj(pCurScene, Vector2(x, y), eType);
}

bool CRoomMap::IsSetObj(CScene* pCurScene, const Vector2& tPos, const Vector2& tObjSize)
{
	Vector2	tActLT = pCurScene->GetFieldLT();
	Vector2	tActRB = pCurScene->GetFieldRB();

	if ((tActLT.x <= tPos.x && tPos.x <= tActRB.x) &&	// 실제 플레이할 공간에서만 설치 가능하게
		(tActLT.y <= tPos.y && tPos.y <= tActRB.y) &&
		(tActLT.x <= tPos.x + tObjSize.x && tPos.x + tObjSize.x <= tActRB.x) &&
		(tActLT.y <= tPos.y + tObjSize.y && tPos.y + tObjSize.y <= tActRB.y))
	{
		std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
		std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->IsObj(pCurScene, tPos, tObjSize)) // 설치한 자리에 다른 오브젝트가 있는 지
				return false;
		}

		return true;
	}

	return false;
}

void CRoomMap::Create(CScene* pCurScene, EMapObject_Type eObj, const Vector2& tPos, const Vector2& tObjSize)
{
	if (eObj == MT_SPAWN || IsSetObj(pCurScene, tPos, tObjSize)) // 설치 가능한 구역이라면
	{
		CRoomObj* pRoomObj = new CRoomObj;

		pRoomObj->SetObject(eObj);
		pRoomObj->SetPos(tPos);
		pRoomObj->SetSize(tObjSize);

		if (!pRoomObj->Init())
		{
			SAFE_DELETE(pRoomObj);
			return;
		}

		m_RoomObjList.push_back(pRoomObj);
	}
}

void CRoomMap::Delete(CScene* pCurScene, const Vector2& tPos)
{
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsObj(pCurScene, tPos) && (*iter)->GetType() != MT_SPAWN) // 설치한 자리에 다른 오브젝트가 있는 지
		{
			SAFE_DELETE((*iter));
			m_RoomObjList.erase(iter);
			return;
		}
	}
}

void CRoomMap::DeleteSpawn(CScene* pCurScene, const Vector2& tPos)
{
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsObj(pCurScene, tPos) && (*iter)->GetType() == MT_SPAWN) // 설치한 자리에 다른 오브젝트가 있는 지
		{
			SAFE_DELETE((*iter));
			m_RoomObjList.erase(iter);
			return;
		}
	}
}

void CRoomMap::Clear()
{
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_RoomObjList.clear();
}

CRoomObj* CRoomMap::GetRoomObj(CScene* pCurScene, const Vector2& tPos) const
{
	std::list<CRoomObj*>::const_iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::const_iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsObj(pCurScene, tPos))
			return *iter;
	}

	return nullptr;
}