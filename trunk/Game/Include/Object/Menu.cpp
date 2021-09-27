
#include "Menu.h"
#include "../Input.h"
#include "../Scene/Stage.h"
#include "../Scene/SceneManager.h"
#include "../GameManager.h"

void CMenu::GameStart(float fTime)
{
	CSceneManager::GetInst()->CreateScene<CStage>();
}

void CMenu::GameExit(float fTime)
{
	CGameManager::GetInst()->Exit();
}

void CMenu::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CMenu::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

void CMenu::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CMenu::Start()
{
	CObj::Start();

	CInput::GetInst()->SetCallback<CMenu>("GameStart", KS_PUSH, this, &CMenu::GameStart);
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
	m_eObjectType = EObjectType::BackGround;
}

CMenu::CMenu(const CMenu& obj)	:
	CObj(obj)
{
}

CMenu::~CMenu()
{
}
