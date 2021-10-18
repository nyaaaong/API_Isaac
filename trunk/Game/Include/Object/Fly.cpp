
#include "Fly.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CFly::CFly() :
	m_fPatternTimer(2.f)
{
	m_fMaxDist = 0.f;

	m_tInfo.fAttack = 0.f;
	m_tInfo.fHP = 3.f;
	m_tInfo.fHPMax = 3.f;
	m_tInfo.fMoveSpeed = 30.f;
}

CFly::CFly(const CFly& obj) :
	CMonsterBase(obj),
	m_fPatternTimer(2.f)
{
}

CFly::~CFly()
{
}

void CFly::Start()
{
	CMonsterBase::Start();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize * 0.6f);
	m_pColliderBox->SetCollisionProfile("Monster");
}

bool CFly::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetSize(96.f, 96.f);
	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Monster);

	AddFlyAnimation();

	return true;
}

void CFly::Update(float fTime)
{
	CMonsterBase::Update(fTime);

	if (m_fKnockBack != 0.f)
	{
		Move(m_tKnockBackDir, m_fKnockBack, true);

		m_fKnockBack -= GetMoveSpeedFrame() * 2.f;

		if (m_fKnockBack < 0.f)
			m_fKnockBack = 0.f;
	}

	FlyPattern(fTime);
}

void CFly::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		Destroy();

		CMonsterSpawner::GetInst()->EnemyDieFly(m_tPos);
	}
}

CFly* CFly::Clone()
{
	return new CFly(*this);
}

void CFly::AddFlyAnimation()
{
	AddAnimation("FlyIdle", true, 0.1f);
}

void CFly::FlyPattern(float fTime)
{
	m_fPatternTimer += fTime;

	if (m_fPatternTimer >= 2.f)
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

	Move(m_tDir, m_tInfo.fMoveSpeed, true);
}

void CFly::Move(const Vector2& tDir, float fSpeed, bool bUseField)
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
