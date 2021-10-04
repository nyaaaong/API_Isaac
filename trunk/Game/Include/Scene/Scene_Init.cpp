
#include "Scene.h"
#include "../Resource/ResourceManager.h"

void CScene::Init_CreateTextureObject()
{
	for (int i = OBJ_ROCK; i < OBJ_MAX; ++i)
	{
		// ���
		TCHAR	cPath[MAX_PATH] = {};
		wsprintf(cPath, TEXT("Room/Object/%d.bmp"), i);

		// �ؽ��ĸ�
		char	cTextureName[32] = "Object";

		// ��ȣ�� ���ڷ�
		char cNum[16] = {};
		sprintf_s(cNum, "%d", i);

		// �ؽ��ĸ� + ����
		strcat_s(cTextureName, cNum);

		CResourceManager::GetInst()->LoadTexture(cTextureName, cPath);
	}

	CResourceManager::GetInst()->LoadTexture("BackGround", TEXT("Room/Room.bmp"));
	CResourceManager::GetInst()->LoadTexture("StartRoom_BackGround", TEXT("Room/Room_Start.bmp"));
}