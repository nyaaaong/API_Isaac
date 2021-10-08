
#include "Scene.h"
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

void CScene::SetPlayerPos(const Vector2& tPos)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPos  = tPos;
	m_pPlayerBody->m_tPos = tPos;

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos = m_pPlayerBody->m_tPos;
}

void CScene::SetPlayerPos(float x, float y)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPos = Vector2(x, y);
	m_pPlayerBody->m_tPos = Vector2(x, y);

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos = m_pPlayerBody->m_tPos;
}

void CScene::SetPlayerPosX(float x)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPrevPos.x = m_pPlayer->m_tPos.x;
	m_pPlayerBody->m_tPrevPos.x = m_pPlayer->m_tPos.x;

	m_pPlayer->m_tPos.x = x;
	m_pPlayerBody->m_tPos.x = x;

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos.x = m_pPlayerBody->m_tPos.x;
}

void CScene::SetPlayerPosY(float y)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPrevPos.y = m_pPlayer->m_tPos.y;
	m_pPlayerBody->m_tPrevPos.y = m_pPlayer->m_tPos.y;

	m_pPlayer->m_tPos.y = y;
	m_pPlayerBody->m_tPos.y = y;

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos.y = m_pPlayerBody->m_tPos.y;
}

void CScene::SetPlayerMove(const Vector2& tPos)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPrevPos = m_pPlayer->m_tPos;
	m_pPlayerBody->m_tPrevPos = m_pPlayerBody->m_tPos;

	m_pPlayer->m_tPos += tPos;
	m_pPlayerBody->m_tPos += tPos;

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos = m_pPlayerBody->m_tPos;
}

void CScene::SetPlayerMove(float x, float y)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;
	
	m_pPlayer->m_tPrevPos = m_pPlayer->m_tPos;
	m_pPlayerBody->m_tPrevPos = m_pPlayerBody->m_tPos;

	m_pPlayer->m_tPos += Vector2(x, y);
	m_pPlayerBody->m_tPos += Vector2(x, y);

	m_pPlayer->m_tVelocity += Vector2(x, y);
	m_pPlayerBody->m_tVelocity += Vector2(x, y);

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos = m_pPlayerBody->m_tPos;
}

void CScene::SetPlayerMoveX(float x)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPrevPos.x = m_pPlayer->m_tPos.x;
	m_pPlayerBody->m_tPrevPos.x = m_pPlayer->m_tPos.x;

	m_pPlayer->m_tPos.x += x;
	m_pPlayerBody->m_tPos.x += x;

	m_pPlayer->m_tVelocity.x += x;
	m_pPlayerBody->m_tVelocity.x += x;

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos.x = m_pPlayerBody->m_tPos.x;
}

void CScene::SetPlayerMoveY(float y)
{
	if (!m_pPlayer || !m_pPlayerBody)
		return;

	m_pPlayer->m_tPrevPos.y = m_pPlayer->m_tPos.y;
	m_pPlayerBody->m_tPrevPos.y = m_pPlayer->m_tPos.y;

	m_pPlayer->m_tPos.y += y;
	m_pPlayerBody->m_tPos.y += y;

	m_pPlayer->m_tVelocity.y += y;
	m_pPlayerBody->m_tVelocity.y += y;

	CheckFieldPos(m_pPlayerBody);
	m_pPlayer->m_tPos.y = m_pPlayerBody->m_tPos.y;
}

bool CScene::CheckFieldPos(CObj* pCharacter)
{
	if (!pCharacter)
		return false;

	if (pCharacter->m_tPos.x - pCharacter->m_tSize.x * pCharacter->m_tPivot.x + pCharacter->m_tOffset.x < m_tFieldLT.x)
	{
		pCharacter->m_tPos.x = m_tFieldLT.x + pCharacter->m_tSize.x * pCharacter->m_tPivot.x - pCharacter->m_tOffset.x;
		return true;
	}

	else if (pCharacter->m_tPos.y - pCharacter->m_tSize.y * pCharacter->m_tPivot.y + pCharacter->m_tOffset.y < m_tFieldLT.y)
	{
		pCharacter->m_tPos.y = m_tFieldLT.y + pCharacter->m_tSize.y * pCharacter->m_tPivot.y - pCharacter->m_tOffset.y;
		return true;
	}

	else if (pCharacter->m_tPos.x + pCharacter->m_tSize.x * pCharacter->m_tPivot.x + pCharacter->m_tOffset.x > m_tFieldRB.x)
	{
		pCharacter->m_tPos.x = m_tFieldRB.x - pCharacter->m_tSize.x * pCharacter->m_tPivot.x - pCharacter->m_tOffset.x;
		return true;
	}

	else if (pCharacter->m_tPos.y + pCharacter->m_tSize.y * pCharacter->m_tPivot.y + pCharacter->m_tOffset.y > m_tFieldRB.y)
	{
		pCharacter->m_tPos.y = m_tFieldRB.y - pCharacter->m_tSize.y * pCharacter->m_tPivot.y - pCharacter->m_tOffset.y;
		return true;
	}

	return false;
}

bool CScene::IsObj(const Vector2& tPos)
{
	return m_pCurMap->IsObj(tPos);
}

bool CScene::IsObj(float x, float y)
{
	return m_pCurMap->IsObj(x, y);
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