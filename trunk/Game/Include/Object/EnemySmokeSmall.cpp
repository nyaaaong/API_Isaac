
#include "EnemySmokeSmall.h"

CEnemySmokeSmall::CEnemySmokeSmall()
{
}

CEnemySmokeSmall::CEnemySmokeSmall(const CEnemySmokeSmall& obj)	:
	CObj(obj)
{
}

CEnemySmokeSmall::~CEnemySmokeSmall()
{
}

bool CEnemySmokeSmall::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);
	//SetOffset(0.f, -50.f);

	AddAnimation("Smoke1", false, 0.4f);

	return true;
}

void CEnemySmokeSmall::Start()
{
	SetAnimationEndNotify<CEnemySmokeSmall>("Smoke1", this, &CEnemySmokeSmall::AnimationFinish);
}

CEnemySmokeSmall* CEnemySmokeSmall::Clone()
{
	return new CEnemySmokeSmall(*this);
}

void CEnemySmokeSmall::AnimationFinish()
{
	Destroy();
}
