
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

	m_pColliderBox = AddCollider<CColliderBox>("Die1");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetOffset(m_tOffset);
	m_pColliderBox->SetCollisionProfile("Effect");
	m_pColliderBox->SetCollisionBeginFunc<CEnemyDie>(this, &CEnemyDie::CollisionBegin);
}

CEnemyDie* CEnemyDie::Clone()
{
	return new CEnemyDie(*this);
}

void CEnemyDie::AnimationFinish()
{
	Destroy();
}
