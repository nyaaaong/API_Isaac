
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

	if (m_eInfo.fHP <= 0.f)
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

void CBossMonstro::Move(const Vector2& tDir, bool bUseActivity)
{
	Move(tDir, m_eInfo.fMoveSpeed, bUseActivity);
}

void CBossMonstro::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	m_tVelocity += tCurMove;
	m_tPrevPos = m_tPos;
	m_tPos += tCurMove;

	if (bUseActivity)
	{
		Vector2	tActivityLT = m_pScene->GetActivityLT();
		Vector2	tActivityRB = m_pScene->GetActivityRB();

		if (m_tPos.x - m_tSize.x * m_tPivot.x + m_tOffset.x < tActivityLT.x)
		{
			m_tPos.x = tActivityLT.x + m_tSize.x * m_tPivot.x - m_tOffset.x;
			m_tM2PDir.x *= -1.f;
		}

		else if (m_tPos.y - m_tSize.y * m_tPivot.y + m_tOffset.y < tActivityLT.y)
		{
			m_tPos.y = tActivityLT.y + m_tSize.y * m_tPivot.y - m_tOffset.y;
			m_tM2PDir.y *= -1.f;
		}

		else if (m_tPos.x + m_tSize.x * m_tPivot.x + m_tOffset.x > tActivityRB.x)
		{
			m_tPos.x = tActivityRB.x - m_tSize.x * m_tPivot.x - m_tOffset.x;
			m_tM2PDir.x *= -1.f;
		}

		else if (m_tPos.y + m_tSize.y * m_tPivot.y + m_tOffset.y > tActivityRB.y)
		{
			m_tPos.y = tActivityRB.y - m_tSize.y * m_tPivot.y - m_tOffset.y;
			m_tM2PDir.y *= -1.f;
		}
	}
}

void CBossMonstro::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (pDest->GetProfile()->strName == "PlayerHead" ||
		pDest->GetProfile()->strName == "PlayerBody")
		pDest->GetOwner()->SetDamage(m_eInfo.fAttack);
}

CBossMonstro::CBossMonstro()	:
	m_bMove(false)
{
	m_eInfo.fAttack = 1.f;
	m_eInfo.fHP = 100.f;
	m_eInfo.fHPMax = 100.f;
	m_eInfo.iBomb = 0;
	m_eInfo.iBombMax = 0;
	m_eInfo.fTearTimer = 1.f;
	m_eInfo.fShotSpeed = 300.f;
	m_eInfo.fTearDistance = 500.f;
	m_eInfo.fMoveSpeed = 500.f;
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