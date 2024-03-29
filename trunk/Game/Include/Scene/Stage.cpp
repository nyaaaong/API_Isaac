
#include "Stage.h"
#include "SceneResource.h"
#include "../Map/MapManager.h"
#include "../Object/MonsterSpawner.h"

bool CStage::Init()
{
	if (!CScene::Init())
		return false;

	CMapManager::GetInst()->SetRoomShuffle(true);

	LoadAnimationSequence();
	LoadSound();

	CScene::LoadFile("Map.dat");

	return true;
}

void CStage::Start()
{
	CScene::Start();

	CreatePrototypes();
}

CStage::CStage()	:
	m_pPlayerHUD(nullptr),
	m_iStage(1)
{
}

CStage::~CStage()
{
}