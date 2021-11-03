
#include "Tear.h"
#include "Player.h"
#include "Block.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "PlayerTearEffect.h"
#include "MonsterTearEffect.h"

bool CTear::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Effect);

	SetPhysics(true);

	return true;
}

void CTear::Start()
{
	CObj::Start();

	m_pColliderBox = nullptr;

	switch (m_eTearType)
	{
	case ETearType::Player:
	{
		if (!m_pOwner)
			m_pOwner = dynamic_cast<CCharacter*>(m_pScene->GetPlayer());

		AddAnimation("PlayerTear", false);

		m_fMoveSpeed = m_pOwner->GetShotSpeed();
		m_fDistance = m_pOwner->GetTearDistance();
		m_fDamage = m_pOwner->GetAttack();

		ChangeAnimation("PlayerTear");

		m_pColliderBox = AddCollider<CColliderBox>("PlayerTear");
		m_pColliderBox->SetExtent(m_tSize * 0.3f);
		m_pColliderBox->SetCollisionProfile("PlayerTear");
	}
	break;
	case ETearType::Monster:
	{
		if (!m_pOwner)
			return;

		AddAnimation("MonsterTear", false);

		m_fMoveSpeed = m_pOwner->GetShotSpeed();
		if (!m_bChildTear)

			m_fDistance = m_pOwner->GetTearDistance();

		m_fDamage = m_pOwner->GetAttack();

		ChangeAnimation("MonsterTear");

		m_pColliderBox = AddCollider<CColliderBox>("MonsterTear");
		m_pColliderBox->SetExtent(m_tSize * 0.3f);
		m_pColliderBox->SetCollisionProfile("MonsterTear");

		if (m_eSpecialTear == ESpecial_Tear::Special || 
			m_eSpecialTear == ESpecial_Tear::Reverse)
		{
			if (m_fDistance != 0.f)
				m_fDistance *= 0.3f;
		}
	}
	break;
	}

	if (m_pColliderBox)
		m_pColliderBox->SetCollisionBeginFunc<CTear>(this, &CTear::CollisionBegin);
}

void CTear::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CObj* pDestObj = pDest->GetOwner();

	if (pDest->GetName() == "Monster")
	{
		if (m_eTearType == ETearType::Monster)
			return;

		else if (m_bHit)
			return;

		else if (pDestObj->GetName() == "Isaac" && dynamic_cast<CCharacter*>(pDestObj)->GetInfo().fHP <= 0.f)
			return;

		m_bHit = true;
		pDestObj->SetDamage(m_fDamage);

		Vector2	tDir = m_tDir;
		tDir.Normalize();

		pDestObj->SetKnockBack(tDir, m_pOwner->GetInfo().fShotSpeed * 0.4f);
		TearDestroy();
	}

	else if (pDest->GetName() == "PlayerHead" ||
		pDest->GetName() == "PlayerBody")
	{
		if (m_eTearType == ETearType::Player)
			return;

		else if (m_bHit)
			return;

		m_bHit = true;
		pDestObj->SetDamage(m_fDamage);

		Vector2	tDir = m_tDir;
		tDir.Normalize();

		TearDestroy();
	}

	else if (pDest->GetName() == "MapObject")
	{
		CBlock* pBlock = dynamic_cast<CBlock*>(pDestObj);

		if (pBlock->GetType() == MT_POOP)
		{
			if (m_bHit)
				return;

			m_bHit = true;
			pBlock->SetDamage(1.f);

			TearDestroy();
		}

		else if (pBlock->GetType() == MT_IRON ||
			pBlock->GetType() == MT_ROCK)
		{
			if (m_bHit)
				return;

			m_bHit = true;

			TearDestroy();
		}
	}
}

void CTear::TearDestroy()
{
	Destroy();

	if (m_eTearType == ETearType::Player)
		CPlayerTearEffect* pEffect = m_pScene->CreateObject<CPlayerTearEffect>("PlayerTearEffect", "PlayerTearEffect", m_tPos, Vector2(192.f, 192.f));

	else if (m_eTearType == ETearType::Monster)
		CMonsterTearEffect* pEffect = m_pScene->CreateObject<CMonsterTearEffect>("MonsterTearEffect", "MonsterTearEffect", m_tPos, Vector2(192.f, 192.f));

	if (!m_bChildTear)
		m_pScene->GetSceneResource()->SoundPlay("TearDrop");

	else
	{
		if (!m_pScene->GetSceneResource()->IsPlaying("TearDrop"))
			m_pScene->GetSceneResource()->SoundPlay("TearDrop");
	}

	if (m_eSpecialTear == ESpecial_Tear::Special)
	{
		float	fDistance = m_pOwner->GetInfo().fTearDistance * 0.3f;

		CSharedPtr<CTear>	pLT = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pLT->SetDir(-135.f);
		pLT->SetOwner(m_pOwner);
		pLT->SetDistance(fDistance * 0.7f);
		pLT->SetChildTear(true);

		CSharedPtr<CTear>	pRT = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pRT->SetDir(-45.f);
		pRT->SetOwner(m_pOwner);
		pRT->SetDistance(fDistance * 0.7f);
		pRT->SetChildTear(true);

		CSharedPtr<CTear>	pLB = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pLB->SetDir(135.f);
		pLB->SetOwner(m_pOwner);
		pLB->SetDistance(fDistance * 0.7f);
		pLB->SetChildTear(true);

		CSharedPtr<CTear>	pRB = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pRB->SetDir(45.f);
		pRB->SetOwner(m_pOwner);
		pRB->SetDistance(fDistance * 0.7f);
		pRB->SetChildTear(true);

		m_pScene->GetSceneResource()->SoundPlay("Tear");
	}

	else if (m_eSpecialTear == ESpecial_Tear::Reverse)
	{
		float	fDistance = m_pOwner->GetInfo().fTearDistance * 0.3f;

		for (int i = 0; i < 4; ++i)
		{
			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear->SetDir(90.f * i);
			pTear->SetOwner(m_pOwner);
			pTear->SetDistance(fDistance * 0.7f);
			pTear->SetChildTear(true);
		}

		m_pScene->GetSceneResource()->SoundPlay("Tear");
	}
}

void CTear::TearMechanism(float fTime)
{
	MoveTear(fTime);
	PostProgressTear();
}

void CTear::MoveTear(float fTime)
{
	m_tDir.Normalize();

	Move(m_tDir, false);
}

void CTear::PostProgressTear()
{
	Vector2	tFieldLT = m_pScene->GetFieldLT();
	Vector2	tFieldRB = m_pScene->GetFieldRB();
	Vector2	tDir = m_tDir;

	m_fDistance -= GetMoveSpeedFrame();

	if (m_fDistance <= 0.f)
		TearDestroy();

	else if (m_fDistance <= 100.f)
	{
		if (m_eTearType == ETearType::Player && tDir.y == 0.f)	// 플레이어 눈물이 양쪽인 경우 중력 적용
			m_bIsGround = false;
	}

	if (m_tPos.x <= tFieldLT.x)
		TearDestroy();

	else if (m_tPos.y <= tFieldLT.y)
		TearDestroy();

	else if (m_tPos.x >= tFieldRB.x)
		TearDestroy();

	else if (m_tPos.y >= tFieldRB.y)
		TearDestroy();
}

void CTear::Update(float fTime)
{
	CObj::Update(fTime);

	TearMechanism(fTime);
}

CTear* CTear::Clone()
{
	return new CTear(*this);
}

CTear::CTear() :
	m_fDistance(600.f),
	m_fDamage(0),
	m_eTearType(ETearType::None),
	m_pOwner(nullptr),
	m_bHit(false),
	m_fTurnSpeed(100.f),
	m_bChildTear(false),
	m_eSpecialTear(ESpecial_Tear::None)
{
}

CTear::CTear(const CTear& obj)	:
	CObj(obj)
{
	m_tDir = obj.m_tDir;
	m_fDistance = obj.m_fDistance;
	m_eTearType = obj.m_eTearType;
	m_iZOrder = obj.m_iZOrder;
	m_fDamage = obj.m_fDamage;
	m_pOwner = obj.m_pOwner;
	m_bHit = false;
	m_eSpecialTear = obj.m_eSpecialTear;
	m_fTurnSpeed = obj.m_fTurnSpeed;
	m_bChildTear = obj.m_bChildTear;
}

CTear::~CTear()
{
}
