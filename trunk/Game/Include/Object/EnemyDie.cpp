
#include "EnemyDie.h"
#include "../Collision/ColliderBox.h"

CEnemyDie::CEnemyDie()
{
}

CEnemyDie::CEnemyDie(const CEnemyDie& obj)	:
	CObj(obj)
{
}

CEnemyDie::~CEnemyDie()
{
}

bool CEnemyDie::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);
	//SetOffset(0.f, -50.f);

	CreateAnimation();
	AddAnimation("Die1", false, 0.3f);

	return true;
}

void CEnemyDie::Start()
{
	CObj::Start();

	SetAnimationEndNotify<CEnemyDie>("Die1", this, &CEnemyDie::AnimationFinish);
}

CEnemyDie* CEnemyDie::Clone()
{
	return new CEnemyDie(*this);
}

void CEnemyDie::AnimationFinish()
{
	Destroy();
}
