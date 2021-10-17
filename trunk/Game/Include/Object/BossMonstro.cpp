
#include "BossMonstro.h"
#include "../Collision/ColliderBox.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"

bool CBossMonstro::Init()
{
	if (!CMonsterBase::Init())
		return false;

	m_bUseKnockBack = false;

	SetSize(256.f, 256.f);
	SetPivot(0.5f, 0.5f);

	SetPhysics(true);
	SetJumpVelocity(30.f);

	AddBossAnimation();
	AddBossPattern();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionProfile("Monster");

	return true;
}

void CBossMonstro::Start()
{
	CMonsterBase::Start();

	m_pColliderBox->SetCollisionBeginFunc<CBossMonstro>(this, &CBossMonstro::CollisionBegin);
}

void CBossMonstro::Update(float fTime)
{
	CMonsterBase::Update(fTime);

	DirCheck();

	if (m_bMove && !m_bIsJump)
		Move(m_tM2PDir, true);
}

void CBossMonstro::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
		Destroy();
}

CBossMonstro* CBossMonstro::Clone()
{
	return new CBossMonstro(*this);
}

void CBossMonstro::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CBossMonstro::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CMonsterBase::CollisionColliding(pSrc, pDest, fTime);
}

CBossMonstro::CBossMonstro()	:
	m_bMove(false)
{
	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 100.f;
	m_tInfo.fHPMax = 100.f;
	m_tInfo.fTearSpeed = 1.f;
	m_tInfo.fShotSpeed = 300.f;
	m_tInfo.fTearDistance = 500.f;
	m_tInfo.fMoveSpeed = 500.f;
}

CBossMonstro::CBossMonstro(const CBossMonstro& obj)	:
	CMonsterBase(obj)
{
	m_bMove = obj.m_bMove;

	m_tBulletStartDir = obj.m_tBulletStartDir;

	AddBossNotify();
	AddBossPattern();
}

CBossMonstro::~CBossMonstro()
{
}