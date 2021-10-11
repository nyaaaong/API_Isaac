
#include "BombExplosionEffect.h"
#include "Block.h"
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
	CObj::Start();

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
	std::string	strDestName = pDest->GetName();
	CObj* pDestObj = pDest->GetOwner();

	if (strDestName == "PlayerHead" || 
		strDestName == "PlayerBody")
	{
		if (!pDestObj->IsEnableDamage())
			return;

		pDestObj->SetDamage(1.f);
	}

	else if (pDest->GetProfile()->strName == "Object")
	{
		CBlock* pBlock = dynamic_cast<CBlock*>(pDestObj);
		switch (pBlock->GetType())
		{
		case MT_ROCK:
		case MT_POOP:
			pBlock->SetDamage(2.f);
			break;
		}
	}
}
