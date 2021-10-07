
#include "RoomMap.h"
#include "RoomObj.h"
#include "../Scene/Scene.h"

bool CRoomMap::IsSetObj(const Vector2& tPos, const Vector2& tObjSize)
{
	Vector2	tActLT = m_pScene->GetFieldLT();
	Vector2	tActRB = m_pScene->GetFieldRB();

	if ((tActLT.x <= tPos.x && tPos.x <= tActRB.x) &&	// ���� �÷����� ���������� ��ġ �����ϰ�
		(tActLT.y <= tPos.y && tPos.y <= tActRB.y) &&
		(tActLT.x <= tPos.x + tObjSize.x && tPos.x + tObjSize.x <= tActRB.x) &&
		(tActLT.y <= tPos.y + tObjSize.y && tPos.y + tObjSize.y <= tActRB.y))
	{
		std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
		std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->IsObj(tPos, tObjSize)) // ��ġ�� �ڸ��� �ٸ� ������Ʈ�� �ִ� ��
				return false;
		}

		return true;
	}

	return false;
}

void CRoomMap::Create(EObject eObj, const Vector2& tPos, const Vector2& tObjSize)
{
	if (IsSetObj(tPos, tObjSize)) // ��ġ ������ �����̶��
	{
		CRoomObj* pRoomObj = new CRoomObj;

		pRoomObj->SetScene(m_pScene);
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

void CRoomMap::Delete(const Vector2& tPos)
{
	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsObj(tPos)) // ��ġ�� �ڸ��� �ٸ� ������Ʈ�� �ִ� ��
		{
			SAFE_DELETE((*iter));
			m_RoomObjList.erase(iter);
			return;
		}
	}
}

void CRoomMap::Clear()
{
	if (!m_pScene)
		return;

	std::list<CRoomObj*>::iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_RoomObjList.clear();
}

CRoomObj* CRoomMap::GetRoomObj(const Vector2& tPos) const
{
	std::list<CRoomObj*>::const_iterator	iter = m_RoomObjList.begin();
	std::list<CRoomObj*>::const_iterator	iterEnd = m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsObj(tPos))
			return *iter;
	}

	return nullptr;
}