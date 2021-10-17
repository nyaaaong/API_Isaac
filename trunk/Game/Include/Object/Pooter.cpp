
#include "Pooter.h"
#include "MonsterSpawner.h"
#include "Tear.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CPooter::CPooter()	:
	m_fPatternTimer(0.f),
	m_fTearSpeedTimer(1.5f)
{
	m_fMaxDist = 600.f;

	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 7.f;
	m_tInfo.fHPMax = 7.f;
	m_tInfo.fTearSpeed = 1.5f;
	m_tInfo.fShotSpeed = 200.f;
	m_tInfo.fTearDistance = 300.f;
	m_tInfo.fMoveSpeed = 10.f;
}

CPooter::CPooter(const CPooter& obj)	:
	CMonsterBase(obj),
	m_fPatternTimer(0.f),
	m_fTearSpeedTimer(1.f)
{
}

CPooter::~CPooter()
{
}

void CPooter::Start()
{
	CMonsterBase::Start();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize * 0.6f);
	m_pColliderBox->SetCollisionProfile("Monster");
	m_pColliderBox->SetCollisionBeginFunc<CPooter>(this, &CPooter::CollisionBegin);
	m_pColliderBox->SetCollisionCollidingFunc<CPooter>(this, &CPooter::CollisionColliding);

	AddAnimationNotify<CPooter>("PooterFireRight", 2, this, &CPooter::Fire);
	AddAnimationNotify<CPooter>("PooterFireLeft", 2, this, &CPooter::Fire);
}

bool CPooter::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetSize(96.f, 96.f);
	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Monster);

	AddPooterAnimation();

	return true;
}

void CPooter::Update(float fTime)
{
	CMonsterBase::Update(fTime);

	CObj* pPlayerBody = m_pScene->GetPlayerBody();

	if (pPlayerBody)
	{
		Vector2	tPlayerPos = pPlayerBody->GetPos() - pPlayerBody->GetSize() * pPlayerBody->GetPivot() + pPlayerBody->GetOffset();
		Vector2	tMonsterPos = m_tPos - m_tSize * m_tPivot * m_tOffset;

		m_fM4PDist = (tMonsterPos - tPlayerPos).Length();
	}

	DetectPlayer(fTime);

	if (m_fKnockBack != 0.f)
	{
		Move(m_tKnockBackDir, m_fKnockBack, true);

		m_fKnockBack -= GetMoveSpeedFrame() * 2.f;

		if (m_fKnockBack < 0.f)
			m_fKnockBack = 0.f;
	}
}

void CPooter::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		Destroy();

		CMonsterSpawner::GetInst()->EnemyDieFly(m_tPos);
	}
}

CPooter* CPooter::Clone()
{
	return new CPooter(*this);
}

void CPooter::AddPooterAnimation()
{
	AddAnimation("PooterIdleRight", true, 0.1f);
	AddAnimation("PooterIdleLeft", true, 0.1f);

	AddAnimation("PooterFireRight", false, 0.3f);
	AddAnimation("PooterFireLeft", false, 0.3f);
}

void CPooter::DetectPlayer(float fTime)
{
	if (m_fM4PDist <= m_fMaxDist)
	{
		GetM2PDir();

		if (m_fTearSpeedTimer >= m_tInfo.fTearSpeed)
		{
			FireAnimation();
		}

		else
		{
			m_fTearSpeedTimer += fTime;
			DefaultAnimation();
		}
	}

	else
		PooterPattern(fTime);
}

void CPooter::PooterPattern(float fTime)
{
	m_fPatternTimer += fTime;

	if (m_fPatternTimer >= 3.f)
	{
		m_fPatternTimer = 0.f;
		RandomDir();
	}

	if (GetCheckFieldPosX())
	{
		CheckFieldPosX(false);
		m_tDir.x *= -1.f;
	}

	if (GetCheckFieldPosY())
	{
		CheckFieldPosY(false);
		m_tDir.y *= -1.f;
	}

	if (m_tDir == Vector2::LEFT)
		ChangeAnimation("PooterIdleLeft");

	else if (m_tDir == Vector2::RIGHT)
		ChangeAnimation("PooterIdleRight");

	Move(m_tDir, m_tInfo.fMoveSpeed, true);
}

void CPooter::Fire()
{
	CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos + 10.f, Vector2(80.f, 80.f));
	pTear->SetDir(m_tM2PDir);
	pTear->SetMoveSpeed(m_tInfo.fShotSpeed);
	pTear->SetOwner(this);

	m_pScene->GetSceneResource()->SoundPlay("Tear");

	m_fTearSpeedTimer = 0.f;
	DefaultAnimation();
}

void CPooter::FireAnimation()
{
	if (m_tM2PDir.x >= -1.f && m_tM2PDir.x < 0.f)
		ChangeAnimation("PooterFireLeft");

	else if (m_tM2PDir.x <= 1.f)
		ChangeAnimation("PooterFireRight");
}

void CPooter::DefaultAnimation()
{
	if (m_tM2PDir.x >= -1.f && m_tM2PDir.x < 0.f)
		ChangeAnimation("PooterIdleLeft");

	else if (m_tM2PDir.x <= 1.f)
		ChangeAnimation("PooterIdleRight");
}

void CPooter::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	m_tVelocity += tCurMove;
	m_tPrevPos = m_tPos;
	m_tPos += tCurMove;

	if (bUseField)
	{
		m_pScene->CheckFieldPos(this);

		if (GetCheckFieldPosX())
		{
			CheckFieldPosX(false);
			m_tDir.x *= -1.f;
		}

		if (GetCheckFieldPosY())
		{
			CheckFieldPosY(false);
			m_tDir.y *= -1.f;
		}
	}
}

void CPooter::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CMonsterBase::CollisionColliding(pSrc, pDest, fTime);
}

void CPooter::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}
