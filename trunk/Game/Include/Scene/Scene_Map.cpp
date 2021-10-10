
#include "Scene.h"
#include "../Object/Block.h"
#include "../Map/RoomMap.h"
#include "../Map/RoomObj.h"

void CScene::LoadMapObject()
{
	if (!m_pCurMap)
		return;

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