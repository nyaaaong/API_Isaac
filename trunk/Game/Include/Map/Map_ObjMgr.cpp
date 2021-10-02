
#include "Map.h"
#include "MapObj.h"
#include "../Scene/Scene.h"

bool CMap::IsSetObj(const Vector2& tPos, const Vector2& tObjSize)
{
	Vector2	tActLT = m_pScene->GetActivityLT();
	Vector2	tActRB = m_pScene->GetActivityRB();

	if ((tActLT.x <= tPos.x && tPos.x <= tActRB.x) &&	// ���� �÷����� ���������� ��ġ �����ϰ�
		(tActLT.y <= tPos.y && tPos.y <= tActRB.y) &&
		(tActLT.x <= tPos.x + tObjSize.x && tPos.x + tObjSize.x <= tActRB.x) &&
		(tActLT.y <= tPos.y + tObjSize.y && tPos.y + tObjSize.y <= tActRB.y))
	{
		std::list<CMapObj*>::iterator	iter = m_ObjList.begin();
		std::list<CMapObj*>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->IsObj(tPos, tObjSize)) // ��ġ�� �ڸ��� �ٸ� ������Ʈ�� �ִ� ��
				return false;
		}

		return true;
	}

	return false;
}

void CMap::Create(EObject eObj, const Vector2& tPos, const Vector2& tObjSize)
{
	if (IsSetObj(tPos, tObjSize)) // ��ġ ������ �����̶��
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
		if ((*iter)->IsObj(tPos)) // ��ġ�� �ڸ��� �ٸ� ������Ʈ�� �ִ� ��
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