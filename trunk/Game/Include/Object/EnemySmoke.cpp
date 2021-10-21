
#include "EnemySmoke.h"

CEnemySmoke::CEnemySmoke()
{
}

CEnemySmoke::CEnemySmoke(const CEnemySmoke& obj)	:
	CObj(obj)
{
}

CEnemySmoke::~CEnemySmoke()
{
}

bool CEnemySmoke::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);
	//SetOffset(0.f, -50.f);

	AddAnimation("Smoke1", false, 0.4f);

	return true;
}

void CEnemySmoke::Start()
{
	SetAnimationEndNotify<CEnemySmoke>("Smoke1", this, &CEnemySmoke::AnimationFinish);
}

CEnemySmoke* CEnemySmoke::Clone()
{
	return new CEnemySmoke(*this);
}

void CEnemySmoke::AnimationFinish()
{
	Destroy();
}
