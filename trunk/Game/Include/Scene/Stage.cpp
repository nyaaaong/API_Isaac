
#include "Stage.h"
#include "SceneResource.h"

bool CStage::Init()
{
	if (!CScene::Init())
		return false;

	LoadAnimationSequence();
	LoadSound();
	LoadBGM();

	CScene::LoadFile("Map.dat");

	CreateObjects();
	CreatePrototypes();

	return true;
}

bool CStage::Update(float fTime)
{
	CScene::Update(fTime);

	/*if (!m_bStart)
	{
		if (m_bFirstRoom)
		{
			SetMap("Room", 0);
		}

		else
		{
			int iRoom = rand() % m_iMaxRoomCount + 1;

			SetMap("Room", iRoom);
		}
	}*/

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
	m_iStage(1),
	m_bStart(false),
	m_bFirstRoom(false)
{
}

CStage::~CStage()
{
}