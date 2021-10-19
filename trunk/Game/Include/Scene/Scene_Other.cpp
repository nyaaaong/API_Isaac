
#include "Scene.h"
#include "SceneManager.h"
#include "../Object/ObjManager.h"
#include "../GameManager.h"
#include "../Map/RoomMap.h"

void CScene::SetPlayer(CObj* pPlayerHead, CObj* pPlayerBody)
{
	m_pPlayer = pPlayerHead;
	m_pPlayerBody = pPlayerBody;

	std::list<CSharedPtr<CObj>>::iterator	iter = m_ObjList.begin();
	std::list<CSharedPtr<CObj>>::iterator	iterEnd = m_ObjList.end();

	bool	bHeadFind = false;
	bool	bBodyFind = false;

	for (; iter != iterEnd;)
	{
		if (!bHeadFind && *iter == m_pPlayer)
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			bHeadFind = true;
			continue;
		}

		else if (!bBodyFind && *iter == m_pPlayerBody)
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			bBodyFind = true;
			continue;
		}

		if (bHeadFind && bBodyFind)
			return;

		++iter;
	}
}



void CScene::CheckFieldPos(CObj* pCharacter)
{
	if (!pCharacter)
		return;

	if (pCharacter->m_tPos.x - pCharacter->m_tSize.x * pCharacter->m_tPivot.x + pCharacter->m_tOffset.x < m_tFieldLT.x)
	{
		pCharacter->m_tPos.x = m_tFieldLT.x + pCharacter->m_tSize.x * pCharacter->m_tPivot.x - pCharacter->m_tOffset.x;
		pCharacter->CheckFieldPosX(true);
		return;
	}

	if (pCharacter->m_tPos.y - pCharacter->m_tSize.y * pCharacter->m_tPivot.y + pCharacter->m_tOffset.y < m_tFieldLT.y)
	{
		pCharacter->m_tPos.y = m_tFieldLT.y + pCharacter->m_tSize.y * pCharacter->m_tPivot.y - pCharacter->m_tOffset.y;
		pCharacter->CheckFieldPosY(true);
		return;
	}

	if (pCharacter->m_tPos.x + pCharacter->m_tSize.x * pCharacter->m_tPivot.x + pCharacter->m_tOffset.x > m_tFieldRB.x)
	{
		pCharacter->m_tPos.x = m_tFieldRB.x - pCharacter->m_tSize.x * pCharacter->m_tPivot.x - pCharacter->m_tOffset.x;
		pCharacter->CheckFieldPosX(true);
		return;
	}

	if (pCharacter->m_tPos.y + pCharacter->m_tSize.y * pCharacter->m_tPivot.y + pCharacter->m_tOffset.y > m_tFieldRB.y)
	{
		pCharacter->m_tPos.y = m_tFieldRB.y - pCharacter->m_tSize.y * pCharacter->m_tPivot.y - pCharacter->m_tOffset.y;
		pCharacter->CheckFieldPosY(true);
		return;
	}
}

bool CScene::IsObj(const Vector2& tPos, EMapObject_Type eType)
{
	return m_pCurMap->IsObj(this, tPos, eType);
}

bool CScene::IsObj(float x, float y, EMapObject_Type eType)
{
	return m_pCurMap->IsObj(this, x, y, eType);
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

void CScene::SetDebugMode(float fTime)
{
	CSceneManager::GetInst()->SetDebug();
}