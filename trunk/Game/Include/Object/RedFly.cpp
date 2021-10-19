#include "RedFly.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CRedFly::CRedFly() :
	m_fPatternTimer(2.f)
{
	m_fMaxDist = 600.f;

	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 4.f;
	m_tInfo.fHPMax = 4.f;
	m_tInfo.fMoveSpeed = 200.f;
}

CRedFly::CRedFly(const CRedFly& obj) :
	CMonsterBase(obj),
	m_fPatternTimer(2.f)
{
}

CRedFly::~CRedFly()
{
}

void CRedFly::Start()
{
	CMonsterBase::Start();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize * 0.6f);
	m_pColliderBox->SetCollisionProfile("Monster");
	m_pColliderBox->SetCollisionCollidingFunc<CRedFly>(this, &CRedFly::CollisionColliding);
}

bool CRedFly::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetSize(96.f, 96.f);
	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Monster);

	AddRedFlyAnimation();

	return true;
}

void CRedFly::Update(float fTime)
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

void CRedFly::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		Destroy();

		CMonsterSpawner::GetInst()->EnemyDieFly(m_tPos);
	}
}

CRedFly* CRedFly::Clone()
{
	return new CRedFly(*this);
}

void CRedFly::AddRedFlyAnimation()
{
	AddAnimation("RedFlyIdle", true, 0.1f);
}

void CRedFly::DetectPlayer(float fTime)
{
	if (m_fM4PDist <= m_fMaxDist)
	{
		GetM2PDir();
		Move(m_tM2PDir, m_tInfo.fMoveSpeed, true);
	}

	else
		RedFlyPattern(fTime);
}

void CRedFly::RedFlyPattern(float fTime)
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

void CRedFly::Move(const Vector2& tDir, float fSpeed, bool bUseField)
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

void CRedFly::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CMonsterBase::CollisionColliding(pSrc, pDest, fTime);
}
