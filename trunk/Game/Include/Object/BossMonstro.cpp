
#include "BossMonstro.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"

bool CBossMonstro::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetSize(256.f, 256.f);
	SetPivot(0.5f, 0.5f);

	SetPhysics(true);
	SetJumpVelocity(30.f);

	AddBossAnimation();
	AddBossPattern();

	m_pColliderSphere = AddCollider<CColliderSphere>("Monster");
	m_pColliderSphere->SetRadius(m_tSize.x * 0.4f);
	m_pColliderSphere->SetOffset(0.f, 50.f);
	m_pColliderSphere->SetCollisionProfile("Monster");

	return true;
}

void CBossMonstro::Start()
{
	CMonsterBase::Start();

	m_pColliderSphere->SetCollisionBeginFunc<CBossMonstro>(this, &CBossMonstro::CollisionBegin);
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

void CBossMonstro::Collision(float fTime)
{
	if (m_bInvisible)
		return;

	CMonsterBase::Collision(fTime);
}

void CBossMonstro::Render(HDC hDC)
{
	if (m_bInvisible)
		return;

	CMonsterBase::Render(hDC);
}

CBossMonstro* CBossMonstro::Clone()
{
	return new CBossMonstro(*this);
}

void CBossMonstro::Move(const Vector2& tDir, bool bUseField)
{
	Move(tDir, m_tInfo.fMoveSpeed, bUseField);
}

void CBossMonstro::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	m_tVelocity += tCurMove;
	m_tPrevPos = m_tPos;
	m_tPos += tCurMove;

	if (bUseField)
	{
		if (m_pScene->CheckFieldPos(this))
			m_tM2PDir.x *= -1.f;
	}
}

void CBossMonstro::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (pDest->GetProfile()->strName == "PlayerHead" ||
		pDest->GetProfile()->strName == "PlayerBody")
		pDest->GetOwner()->SetDamage(m_tInfo.fAttack);
}

CBossMonstro::CBossMonstro()	:
	m_bMove(false)
{
	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 100.f;
	m_tInfo.fHPMax = 100.f;
	m_tInfo.iBomb = 0;
	m_tInfo.iBombMax = 0;
	m_tInfo.fTearTimer = 1.f;
	m_tInfo.fShotSpeed = 300.f;
	m_tInfo.fTearDistance = 500.f;
	m_tInfo.fMoveSpeed = 500.f;
}

CBossMonstro::CBossMonstro(const CBossMonstro& obj)	:
	CMonsterBase(obj)
{
	m_bMove = obj.m_bMove;

	m_tBulletStartDir = obj.m_tBulletStartDir;
	m_fTearTimer = obj.m_fTearTimer;

	AddBossNotify();
	AddBossPattern();
}

CBossMonstro::~CBossMonstro()
{
}