
#include "Charger.h"
#include "Block.h"
#include "EnemyDie.h"
#include "Tear.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Map/MapManager.h"
#include "../Map/RoomMap.h"
#include "../Collision/ColliderBox.h"

CCharger::CCharger()	:
	m_fSpikeDelay(1.f),
	m_fPatternTimer(2.f),
	m_bSoundPlayOnce(false)
{
	m_fMaxDist = 300.f;

	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 10.f;
	m_tInfo.fHPMax = 10.f;
	m_tInfo.fMoveSpeed = 70.f;
}

CCharger::CCharger(const CCharger& obj):
	CMonsterBase(obj),
	m_fSpikeDelay(1.f),
	m_fPatternTimer(2.f),
	m_bSoundPlayOnce(false)
{
}

CCharger::~CCharger()
{
}

void CCharger::Start()
{
	CMonsterBase::Start();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize * 0.6f);
	m_pColliderBox->SetCollisionProfile("Monster");
	m_pColliderBox->SetCollisionBeginFunc<CCharger>(this, &CCharger::CollisionBegin);
	m_pColliderBox->SetCollisionCollidingFunc<CCharger>(this, &CCharger::CollisionColliding);

	RandomDir();
}

bool CCharger::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetSize(128.f, 128.f);
	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Monster);

	AddChargerAnimation();

	return true;
}

void CCharger::Update(float fTime)
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

void CCharger::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		Destroy();

		CMonsterSpawner::GetInst()->EnemyDieNormal(m_tPos);
	}
}

CCharger* CCharger::Clone()
{
	return new CCharger(*this);
}

void CCharger::AddChargerAnimation()
{
	AddAnimation("ChargerMoveRight", true);
	AddAnimation("ChargerMoveLeft", true);
	AddAnimation("ChargerMoveUp", true);
	AddAnimation("ChargerMoveDown", true);

	AddAnimation("ChargerAttackRight", true);
	AddAnimation("ChargerAttackLeft", true);
	AddAnimation("ChargerAttackUp", true);
	AddAnimation("ChargerAttackDown", true);
}

void CCharger::DetectPlayer(float fTime)
{
	if (m_fM4PDist <= m_fMaxDist)
	{
		if (!m_bSoundPlayOnce)
		{
			m_bSoundPlayOnce = true;
			m_pScene->GetSceneResource()->SoundPlay("ChargerAttack");
		}

		GetM2PDir();

		Move(m_tM2PDir, m_tInfo.fMoveSpeed + 100.f, true);

		float	fX = abs(m_tM2PDir.x);
		float	fY = abs(m_tM2PDir.y);

		if (fX > fY)
		{
			if (m_tM2PDir.x >= -1.f && m_tM2PDir.x < 0.f)
				ChangeAnimation("ChargerAttackLeft");

			else if (m_tM2PDir.x <= 1.f)
				ChangeAnimation("ChargerAttackRight");
		}

		else
		{
			if (m_tM2PDir.y >= -1.f && m_tM2PDir.y < 0.f)
				ChangeAnimation("ChargerAttackUp");

			else if (m_tM2PDir.y <= 1.f)
				ChangeAnimation("ChargerAttackDown");
		}
	}

	else
	{
		m_bSoundPlayOnce = false;
		ChagerPattern(fTime);
	}
}

void CCharger::ChagerPattern(float fTime)
{
	m_fPatternTimer += fTime;

	if (m_fPatternTimer >= 2.f)
	{
		m_fPatternTimer = 0.f;
		RandomDir();
	}

	if (m_bBlockCollision)
	{
		m_tDir *= -1.f;
		m_bBlockCollision = false;
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
		ChangeAnimation("ChargerMoveLeft");

	else if (m_tDir == Vector2::RIGHT)
		ChangeAnimation("ChargerMoveRight");

	else if (m_tDir == Vector2::UP)
		ChangeAnimation("ChargerMoveUp");

	else if (m_tDir == Vector2::DOWN)
		ChangeAnimation("ChargerMoveDown");

	Move(m_tDir, m_tInfo.fMoveSpeed, true);
}

void CCharger::Move(const Vector2& tDir, float fSpeed, bool bUseField)
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

void CCharger::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CMonsterBase::CollisionColliding(pSrc, pDest, fTime);

	std::string	strDestName = pDest->GetName();

	if (strDestName == "MapObject")
	{
		if (dynamic_cast<CBlock*>(pDest->GetOwner())->GetType() == MT_SPIKE)
		{
			m_fSpikeDelay += fTime;

			if (m_fSpikeDelay >= 1.f)
			{
				m_fSpikeDelay = 0.f;
				SetDamage(1.f);
			}
		}
	}
}

void CCharger::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}