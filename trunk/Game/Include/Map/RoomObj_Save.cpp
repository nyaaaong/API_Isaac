
#include "RoomObj.h"

void CRoomObj::Save(FILE* pFile)
{
	fwrite(&m_tPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_tSize, sizeof(Vector2), 1, pFile);

	fwrite(&m_eType, sizeof(EMapObject_Type), 1, pFile);

	fwrite(&m_iZOrder, sizeof(int), 1, pFile);

	if (m_pTexture)
	{
		bool	bTexture = true;
		fwrite(&bTexture, sizeof(bool), 1, pFile);

		m_pTexture->Save(pFile);
	}

	else
	{
		bool	bTexture = false;
		fwrite(&bTexture, sizeof(bool), 1, pFile);
	}
}