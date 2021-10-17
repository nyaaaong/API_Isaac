
#include "EnemyDie.h"
#include "../Collision/ColliderBox.h"

CEnemyDie::CEnemyDie()	:
	m_eType(EEnemy_Type::Normal)
{
}

CEnemyDie::CEnemyDie(const CEnemyDie& obj)	:
	CObj(obj)
{
	m_eType = obj.m_eType;
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
	AddAnimation("DieNormal", false, 0.3f);
	AddAnimation("DieFly", false, 0.3f);

	return true;
}

void CEnemyDie::Start()
{
	CObj::Start();

	switch (m_eType)
	{
	case EEnemy_Type::Normal:
		ChangeAnimation("DieNormal");
		break;
	case EEnemy_Type::Fly:
		ChangeAnimation("DieFly");
		break;
	}

	SetAnimationEndNotify<CEnemyDie>("DieNormal", this, &CEnemyDie::AnimationFinish);
	SetAnimationEndNotify<CEnemyDie>("DieFly", this, &CEnemyDie::AnimationFinish);
}

CEnemyDie* CEnemyDie::Clone()
{
	return new CEnemyDie(*this);
}

void CEnemyDie::AnimationFinish()
{
	Destroy();
}
