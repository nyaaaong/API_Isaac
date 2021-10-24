
#include "Ending.h"
#include "SceneResource.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "../GameManager.h"
#include "../Object/EndingScreen.h"

CEnding::CEnding()	:
	m_pScreen(nullptr)
{
}

CEnding::~CEnding()
{
}

bool CEnding::Init()
{
	if (!CScene::Init())
		return false;

	m_pScreen = CreateObject<CEndingScreen>("EndingScreen", Vector2(), Vector2(1280.f, 720.f));

	return true;
}