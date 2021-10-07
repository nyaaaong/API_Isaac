
#include "Scene.h"
#include "../Object/Block.h"
#include "../Map/RoomMap.h"
#include "../Map/RoomObj.h"

void CScene::SetMap(const std::string& strName, int iRoomNum)
{
	size_t iSize = m_vecRoomMap.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecRoomMap[i]->m_bEnable = false;

		if (m_vecRoomMap[i]->GetRoomNumber() == iRoomNum)
		{
			m_pCurMap = m_vecRoomMap[i];
			m_pCurMap->m_bEnable = true;
			m_pCurMap->SetScene(this);
		}
	}
}

void CScene::LoadMapObject()
{
	Vector2	tObjPos, tObjSize;
	EMapObject_Type	eObjType;

	std::list<CRoomObj*>::iterator	iter = m_pCurMap->m_RoomObjList.begin();
	std::list<CRoomObj*>::iterator	iterEnd = m_pCurMap->m_RoomObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		tObjPos = (*iter)->GetPos();
		tObjSize = (*iter)->GetSize();
		eObjType = (*iter)->GetType();

		CBlock* pBlock = CreateObject<CBlock>("MapObject", tObjPos, tObjSize);

		if (!pBlock)
			assert(!"if (!pBlock)");

		pBlock->m_eType = eObjType;
	}
}

void CScene::SetSpecialMap(ESpecial_RoomType eType)
{
	std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.find(eType);

	if (iter == m_mapSpecialRoomMap.end())
		return;

	m_pCurMap = iter->second;
}