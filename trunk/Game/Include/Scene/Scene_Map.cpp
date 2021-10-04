
#include "Scene.h"
#include "../Map/RoomMap.h"

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

void CScene::SetSpecialMap(ESpecial_RoomType eType)
{
	std::unordered_map<ESpecial_RoomType, CRoomMap*>::iterator	iter = m_mapSpecialRoomMap.find(eType);

	if (iter == m_mapSpecialRoomMap.end())
		return;

	m_pCurMap = iter->second;
}