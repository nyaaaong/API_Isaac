
#include "Tear.h"
#include "../Collision/ColliderSphere.h"
#include "Player.h"
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

	CreateAnimation();

	return true;
}

void CTear::Start()
{
	CObj::Start();

	m_pColliderSphere = nullptr;

	switch (m_eTearType)
	{
	case ETearType::Player:
	{
		CCharacter* pPlayer = dynamic_cast<CCharacter*>(m_pScene->GetPlayer());

		if (!pPlayer)
			break;

		AddAnimation("PlayerTear", false);

		m_fMoveSpeed = pPlayer->GetShotSpeed();
		m_fDistance = pPlayer->GetTearDistance();
		m_fDamage = pPlayer->GetAttack();

		ChangeAnimation("PlayerTear");

		m_pColliderSphere = AddCollider<CColliderSphere>("PlayerTear");
		m_pColliderSphere->SetRadius(18.f);
		m_pColliderSphere->SetCollisionProfile("PlayerTear");
	}
	break;
	case ETearType::Monster:
	{
		CCharacter* pMonster = dynamic_cast<CCharacter*>(m_pScene->FindObject("Monster"));

		if (!pMonster)
			break;

		AddAnimation("MonsterTear", false);

		m_fMoveSpeed = pMonster->GetShotSpeed();
		m_fDistance = pMonster->GetTearDistance();
		m_fDamage = pMonster->GetAttack();

		ChangeAnimation("MonsterTear");

		m_pColliderSphere = AddCollider<CColliderSphere>("MonsterTear");
		m_pColliderSphere->SetRadius(18.f);
		m_pColliderSphere->SetCollisionProfile("MonsterTear");
	}
	break;
	}

	if (m_pColliderSphere)
		m_pColliderSphere->SetCollisionBeginFunc(this, &CTear::CollisionBegin);
}

void CTear::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (pDest->GetName() == "Monster")
		pDest->GetOwner()->SetDamage(m_fDamage);

	TearDestroy();
}

void CTear::TearDestroy()
{
	Destroy();

	if (m_eTearType == ETearType::Player)
		CPlayerTearEffect* pEffect = m_pScene->CreateObject<CPlayerTearEffect>("PlayerTearEffect", "PlayerTearEffect", m_tPos, Vector2(192.f, 192.f));

	else if (m_eTearType == ETearType::Monster)
		CMonsterTearEffect* pEffect = m_pScene->CreateObject<CMonsterTearEffect>("MonsterTearEffect", "MonsterTearEffect", m_tPos, Vector2(192.f, 192.f));

	m_pScene->GetSceneResource()->SoundPlay("TearDrop");
}

void CTear::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CTear::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

void CTear::Update(float fTime)
{
	CObj::Update(fTime);

	Vector2	tDir = m_tDir;
	tDir.Normalize();
	Move(tDir, false);

	m_fDistance -= GetMoveSpeedFrame();

	Vector2	tActivityPos = m_pScene->GetActivityPos();
	Vector2	tActivitySize = m_pScene->GetActivitySize();

	if (m_fDistance <= 0.f)
		TearDestroy();

	else if (m_fDistance <= 100.f)
	{
		if (m_eTearType == ETearType::Player && tDir.y == 0.f)	// 플레이어 눈물이 양쪽인 경우 중력 적용
			m_bIsGround = false;
	}

	else if (m_tPos.x <= tActivityPos.x)
		TearDestroy();

	else if (m_tPos.y <= tActivityPos.y)
		TearDestroy();

	else if (m_tPos.x >= tActivitySize.x)
		TearDestroy();

	else if (m_tPos.y >= tActivitySize.y)
		TearDestroy();
}

void CTear::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CTear::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CTear::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CTear* CTear::Clone()
{
	return new CTear(*this);
}

CTear::CTear() :
	m_fDistance(600.f),
	m_fDamage(0),
	m_eTearType(ETearType::None)
{
	m_eObjectType = EObjectType::Tear;
}

CTear::CTear(const CTear& obj)	:
	CObj(obj)
{
	m_tDir = obj.m_tDir;
	m_fDistance = obj.m_fDistance;
	m_eTearType = obj.m_eTearType;
	m_iZOrder = obj.m_iZOrder;
	m_fDamage = obj.m_fDamage;
}

CTear::~CTear()
{
}
