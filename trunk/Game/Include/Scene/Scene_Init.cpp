
#include "Scene.h"
#include "../Resource/ResourceManager.h"

void CScene::Init_CreateTextureObject()
{
	for (int i = MT_ROCK; i < MT_SPAWN; ++i)
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

	CResourceManager::GetInst()->LoadTexture("Rock_0", TEXT("Room/Object/Rock/0.bmp"));

	CResourceManager::GetInst()->LoadTexture("Poop_3", TEXT("Room/Object/Poop/3.bmp"));
	CResourceManager::GetInst()->LoadTexture("Poop_2", TEXT("Room/Object/Poop/2.bmp"));
	CResourceManager::GetInst()->LoadTexture("Poop_1", TEXT("Room/Object/Poop/1.bmp"));
	CResourceManager::GetInst()->LoadTexture("Poop_0", TEXT("Room/Object/Poop/0.bmp"));
}