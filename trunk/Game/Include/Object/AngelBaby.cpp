
#include "AngelBaby.h"
#include "MonsterSpawner.h"
#include "Tear.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CAngelBaby::CAngelBaby()	:
	m_fPatternTimer(0.f),
	m_fTearSpeedTimer(0.f),
	m_fFireAnimDelay(0.f),
	m_fFireAnimDelayMax(1.f),
	m_bIsFire(false)
{
	m_fMaxDist = 700.f;

	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 15.f;
	m_tInfo.fHPMax = 15.f;
	m_tInfo.fTearSpeed = 1.5f;
	m_tInfo.fShotSpeed = 200.f;
	m_tInfo.fTearDistance = 300.f;
	m_tInfo.fMoveSpeed = 150.f;
}

CAngelBaby::CAngelBaby(const CAngelBaby& obj)	:
	CMonsterBase(obj),
	m_bIsFire(false)
{
	m_fPatternTimer = 0.f;
	m_fTearSpeedTimer = 0.f;
	m_fFireAnimDelay = 0.f;
	m_fFireAnimDelayMax = obj.m_fFireAnimDelayMax;
}

CAngelBaby::~CAngelBaby()
{
}

void CAngelBaby::Start()
{
	CMonsterBase::Start();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(114.f, 81.f);
	m_pColliderBox->SetCollisionProfile("Monster");
	//m_pColliderBox->SetOffset(0.f, -100.f);
	m_pColliderBox->SetCollisionCollidingFunc<CAngelBaby>(this, &CAngelBaby::CollisionColliding);

	m_fFireAnimDelay = (rand() % 10000 + 1) / 10000.f;

	SetPivot(0.5f, 0.5f);
	SetTexture("AngelBabyIdle");
}

bool CAngelBaby::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetZOrder(EZOrder::Monster);

	SetTexture("AngelBabyIdle", TEXT("Monster/Enemy/AngelBaby/AngelBaby_Idle.bmp"));
	SetTextureColorKey();
	SetTexture("AngelBabyAttack", TEXT("Monster/Enemy/AngelBaby/AngelBaby_Attack.bmp"));
	SetTextureColorKey();

	return true;
}

void CAngelBaby::Update(float fTime)
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

void CAngelBaby::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		Destroy();

		CMonsterSpawner::GetInst()->EnemyDieNormal(m_tPos);
	}
}

CAngelBaby* CAngelBaby::Clone()
{
	return new CAngelBaby(*this);
}

void CAngelBaby::DetectPlayer(float fTime)
{
	if (m_bIsFire)
	{
		FireEnd(fTime);
		return;
	}

	if (m_fM4PDist <= m_fMaxDist)
	{
		GetM2PDir();

		if (m_fTearSpeedTimer >= m_tInfo.fTearSpeed)
			Fire();

		else
		{
			m_fTearSpeedTimer += fTime;
			SetTexture("AngelBabyIdle");
		}
	}

	else
		AngelBabyPattern(fTime);
}

void CAngelBaby::AngelBabyPattern(float fTime)
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

void CAngelBaby::Fire()
{
	if (m_bIsFire)
	{
		m_fTearSpeedTimer = 0.f;
		return;
	}

	m_bIsFire = true;

	SetTexture("AngelBabyAttack");

	float	fPercent = rand() % 10000 / 100.f;

	if (fPercent < 50.f)
		m_pScene->GetSceneResource()->SoundPlay("AngelBabyAttack1");

	else
		m_pScene->GetSceneResource()->SoundPlay("AngelBabyAttack2");

	CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
	CSharedPtr<CTear>	pTear1 = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
	CSharedPtr<CTear>	pTear2 = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));

	pTear->SetDir(m_tM2PDir);
	pTear1->SetDir(m_fM2PAngle + 30.f);
	pTear2->SetDir(m_fM2PAngle - 30.f);

	pTear->SetOwner(this);
	pTear1->SetOwner(this);
	pTear2->SetOwner(this);

	m_pScene->GetSceneResource()->SoundPlay("Tear");

	m_fTearSpeedTimer = 0.f;
}

void CAngelBaby::FireEnd(float fTime)
{
	m_fFireAnimDelay += fTime;

	if (m_fFireAnimDelay >= m_fFireAnimDelayMax)
	{
		m_fFireAnimDelay = 0.f;
		m_fTearSpeedTimer = 0.f;
		m_bIsFire = false;

		SetTexture("AngelBabyIdle");
	}
}

void CAngelBaby::Move(const Vector2& tDir, float fSpeed, bool bUseField)
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

void CAngelBaby::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CMonsterBase::CollisionColliding(pSrc, pDest, fTime);
}
