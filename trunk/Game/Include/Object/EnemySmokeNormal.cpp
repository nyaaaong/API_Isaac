
#include "EnemySmokeNormal.h"

CEnemySmokeNormal::CEnemySmokeNormal()
{
}

CEnemySmokeNormal::CEnemySmokeNormal(const CEnemySmokeNormal& obj) :
	CObj(obj)
{
}

CEnemySmokeNormal::~CEnemySmokeNormal()
{
}

bool CEnemySmokeNormal::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);

	AddAnimation("Smoke2", false, 0.4f);

	return true;
}

void CEnemySmokeNormal::Start()
{
	SetAnimationEndNotify<CEnemySmokeNormal>("Smoke2", this, &CEnemySmokeNormal::AnimationFinish);
}

CEnemySmokeNormal* CEnemySmokeNormal::Clone()
{
	return new CEnemySmokeNormal(*this);
}

void CEnemySmokeNormal::AnimationFinish()
{
	Destroy();
}
