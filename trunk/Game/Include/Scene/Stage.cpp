
#include "Stage.h"
#include "SceneResource.h"

bool CStage::Init()
{
	if (!CScene::Init())
		return false;

	LoadAnimationSequence();
	LoadSound();
	LoadBGM();
	LoadMap();

	CreateObjects();
	CreatePrototypes();

	return true;
}

bool CStage::Update(float fTime)
{
	CScene::Update(fTime);

	return true;
}

bool CStage::PostUpdate(float fTime)
{
	CScene::PostUpdate(fTime);

	return true;
}

bool CStage::Collision(float fTime)
{
	CScene::Collision(fTime);

	return true;
}

bool CStage::Render(HDC hDC)
{
	CScene::Render(hDC);

	return true;
}

CStage::CStage()	:
	m_pPlayerHUD(nullptr),
	m_iStage(1)
{
}

CStage::~CStage()
{
}