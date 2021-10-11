
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

	SetAnimationEndNotify<CPlayerTearEffect>("PlayerTearDrop", this, &CPlayerTearEffect::AnimationFinish);
}

void CPlayerTearEffect::AnimationFinish()
{
	Destroy();
}

CPlayerTearEffect* CPlayerTearEffect::Clone()
{
	return new CPlayerTearEffect(*this);
}

CPlayerTearEffect::CPlayerTearEffect()
{
}

CPlayerTearEffect::CPlayerTearEffect(const CPlayerTearEffect& obj) :
	CObj(obj)
{
}

CPlayerTearEffect::~CPlayerTearEffect()
{
}
