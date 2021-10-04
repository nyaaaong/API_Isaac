
#include "Scene.h"

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