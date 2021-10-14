
#include "RoomObj.h"

void CRoomObj::Load(CScene* pCurScene, FILE* pFile)
{
	fread(&m_tPos, sizeof(Vector2), 1, pFile);
	fread(&m_tSize, sizeof(Vector2), 1, pFile);

	fread(&m_eType, sizeof(EMapObject_Type), 1, pFile);

	fread(&m_iZOrder, sizeof(int), 1, pFile);

	bool	bTexture = true;
	fread(&bTexture, sizeof(bool), 1, pFile);

	if (bTexture)
		m_pTexture = CTexture::LoadStatic(pFile, pCurScene);
}