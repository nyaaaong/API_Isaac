
#include "Menu.h"
#include "../Input.h"
#include "../Scene/Stage.h"
#include "../Scene/EditorScene.h"
#include "../Scene/SceneManager.h"
#include "../GameManager.h"

void CMenu::GameStart(float fTime)
{
	CSceneManager::GetInst()->CreateScene<CStage>();
}

void CMenu::GameEditor(float fTime)
{
	CSceneManager::GetInst()->CreateScene<CEditorScene>();
}

void CMenu::GameExit(float fTime)
{
	CGameManager::GetInst()->Exit();
}

void CMenu::Start()
{
	CObj::Start();

	CInput::GetInst()->SetCallback<CMenu>("GameStart1", KS_PUSH, this, &CMenu::GameStart);
	CInput::GetInst()->SetCallback<CMenu>("GameStart2", KS_PUSH, this, &CMenu::GameStart);
	CInput::GetInst()->SetCallback<CMenu>("GameEditor", KS_PUSH, this, &CMenu::GameEditor);
	CInput::GetInst()->SetCallback<CMenu>("GameExit", KS_PUSH, this, &CMenu::GameExit);
}

bool CMenu::Init()
{
	if (!CObj::Init())
		return false;	

	CreateAnimation();
	AddAnimation("MainMenu", true, 0.5f);

	return true;
}

void CMenu::Update(float fTime)
{
	CObj::Update(fTime);
}

void CMenu::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CMenu::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CMenu::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CMenu* CMenu::Clone()
{
	return nullptr;
}

CMenu::CMenu()
{
	m_eObjectType = EObjectType::Map;
}

CMenu::CMenu(const CMenu& obj)	:
	CObj(obj)
{
}

CMenu::~CMenu()
{
}
