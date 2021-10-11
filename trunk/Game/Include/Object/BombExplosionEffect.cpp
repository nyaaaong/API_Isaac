
#include "BombExplosionEffect.h"
#include "Player.h"
#include "PlayerBody.h"
#include "../Collision/ColliderBox.h"

CBombExplosionEffect::CBombExplosionEffect()
{
}

CBombExplosionEffect::CBombExplosionEffect(const CBombExplosionEffect& obj) :
	CObj(obj)
{
}

CBombExplosionEffect::~CBombExplosionEffect()
{
}

bool CBombExplosionEffect::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);
	SetOffset(0.f, -50.f);

	CreateAnimation();
	AddAnimation("BombExplosion", false, 0.3f);

	return true;
}

void CBombExplosionEffect::Start()
{
	SetAnimationEndNotify<CBombExplosionEffect>("BombExplosion", this, &CBombExplosionEffect::AnimationFinish);

	m_pColliderBox = AddCollider<CColliderBox>("BombExplosion");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetOffset(m_tOffset);
	m_pColliderBox->SetCollisionProfile("BombExplosion");
	m_pColliderBox->SetCollisionBeginFunc<CBombExplosionEffect>(this, &CBombExplosionEffect::CollisionBegin);
}

CBombExplosionEffect* CBombExplosionEffect::Clone()
{
	return new CBombExplosionEffect(*this);
}

void CBombExplosionEffect::AnimationFinish()
{
	Destroy();
}

void CBombExplosionEffect::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (pDest->GetName() == "PlayerHead" || 
		pDest->GetName() == "PlayerBody")
	{
		if (!pDest->GetOwner()->IsEnableDamage())
			return;

		pDest->GetOwner()->SetDamage(1.f);
	}

}
