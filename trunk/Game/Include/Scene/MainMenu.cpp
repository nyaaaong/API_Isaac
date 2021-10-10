
#include "MainMenu.h"
#include "SceneResource.h"
#include "Scene.h"
#include "../Input.h"
#include "../Object/Menu.h"

bool CMainMenu::Init()
{
	if (!CScene::Init())
		return false;

	LoadAnimationSequence();

	GetSceneResource()->SetVolume("BGM", 10);
	GetSceneResource()->LoadSound("BGM", true, "MenuBGM", "Music/Menu.ogg");
	GetSceneResource()->SoundPlay("MenuBGM");

	CMenu* pMainMenu = CreateObject<CMenu>("MainMenu", Vector2(0.f, 0.f), Vector2(1280.f, 720.f));

	return true;
}

void CMainMenu::Start()
{
	CScene::Start();

	CInput::GetInst()->SetShowCursor(true); // 에디터에서 메인화면으로 전환됐을때를 대비해서 마우스를 무조건 보이게 한다.
}

bool CMainMenu::Update(float fTime)
{
	CScene::Update(fTime);

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