
#include "EndingScreen.h"
#include "../Scene/SceneManager.h"

CEndingScreen::CEndingScreen()
{
}

CEndingScreen::CEndingScreen(const CEndingScreen& obj)	:
	CObj(obj)
{
}

CEndingScreen::~CEndingScreen()
{
}

void CEndingScreen::Start()
{
	CObj::Start();

	CSceneManager::GetInst()->ChangeMusic(EMusic_Type::Ending);
}

bool CEndingScreen::Init()
{
	if (!CObj::Init())
		return false;

	SetTexture("Ending", TEXT("Ending/Ending.bmp"));

	return true;
}
