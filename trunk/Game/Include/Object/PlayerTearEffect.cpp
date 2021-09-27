
#include "PlayerTearEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

bool CPlayerTearEffect::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);

	CreateAnimation();
	AddAnimation("PlayerTearDrop", false, 0.3f);

	SetAnimationEndNotify<CPlayerTearEffect>("PlayerTearDrop", this, &CPlayerTearEffect::AnimationFinish);

	return true;
}

void CPlayerTearEffect::Start()
{
	CObj::Start();
}

void CPlayerTearEffect::AnimationFinish()
{
	Destroy();
}

void CPlayerTearEffect::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CPlayerTearEffect::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

void CPlayerTearEffect::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CPlayerTearEffect::Update(float fTime)
{
	CObj::Update(fTime);
}

void CPlayerTearEffect::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CPlayerTearEffect::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CPlayerTearEffect::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CPlayerTearEffect* CPlayerTearEffect::Clone()
{
	return new CPlayerTearEffect(*this);
}

CPlayerTearEffect::CPlayerTearEffect()
{
	m_eObjectType = EObjectType::Effect;
}

CPlayerTearEffect::CPlayerTearEffect(const CPlayerTearEffect& obj) :
	CObj(obj)
{
}

CPlayerTearEffect::~CPlayerTearEffect()
{
}
