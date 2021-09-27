
#include "MainMenu.h"
#include "SceneResource.h"
#include "../Object/Menu.h"
#include "Scene.h"

bool CMainMenu::Init()
{
	if (!CScene::Init())
		return false;

	LoadAnimationSequence();

	GetSceneResource()->LoadSound("BGM", true, "MenuBGM", "Music/Menu.ogg");
	GetSceneResource()->SoundPlay("MenuBGM");

	CMenu* pMainMenu = CreateObject<CMenu>("MainMenu", Vector2(0.f, 0.f), Vector2(1280.f, 720.f));

	return true;
}

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::LoadAnimationSequence()
{
	GetSceneResource()->CreateAnimationSequence("MainMenu", "MainMenu", TEXT("UI/Main.bmp"));

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("MainMenu", 0.f, i * 720.f, 1280.f, 720.f);
	}
}