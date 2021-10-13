
#include "Bomb.h"
#include "BombExplosionEffect.h"
#include "Tear.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderSphere.h"

CBomb::CBomb()	:
	m_fDistance(0.f),
	m_fTimer(0.f),
	m_fTimerMax(2.f)
{
}

CBomb::CBomb(const CBomb& obj)	:
	CObj(obj),
	m_fDistance(0.f),
	m_fTimer(0.f)
{
	m_fTimerMax = obj.m_fTimerMax;
}

CBomb::~CBomb()
{
}

bool CBomb::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Bomb);

	SetTexture("Bomb", TEXT("Player/Bomb/Bomb.bmp"));
	SetTextureColorKey();

	return true;
}

void CBomb::Start()
{
	CObj::Start();

	m_pColliderSphere = AddCollider<CColliderSphere>("Bomb");
	m_pColliderSphere->SetRadius(30.f);
	m_pColliderSphere->SetCollisionProfile("Bomb");
	m_pColliderSphere->SetCollisionBeginFunc<CBomb>(this, &CBomb::CollisionBegin);
}

void CBomb::Update(float fTime)
{
	CObj::Update(fTime);

	m_fTimer += fTime;

	if (m_fTimer >= m_fTimerMax)
		BombDestroy();

	if (m_fKnockBack != 0.f)
	{
		Move(m_tDir, m_fKnockBack, true);

		m_fDistance -= GetMoveSpeedFrame();
		m_fKnockBack -= GetMoveSpeedFrame();

		if (m_fDistance < 0.f)
			m_fDistance = 0.f;

		if (m_fKnockBack < 0.f)
			m_fKnockBack = 0.f;
	}
}

void CBomb::Collision(float fTime)
{
	CObj::Collision(fTime);
}

CBomb* CBomb::Clone()
{
	return new CBomb(*this);
}

void CBomb::BombDestroy()
{
	Destroy();

	CBombExplosionEffect* pExplosion = m_pScene->CreateObject<CBombExplosionEffect>("BombExplosion", "BombExplosion", m_tPos, Vector2(288.f, 288.f));

	m_pScene->GetSceneResource()->SoundPlay("BombExplosion");

	dynamic_cast<CPlayer*>(m_pScene->GetPlayer())->UseBomb(false);
}

void CBomb::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (pDest->GetName() == "PlayerTear" ||
		pDest->GetName() == "MonsterTear")
	{
		CTear* pDestObj = dynamic_cast<CTear*>(pDest->GetOwner());
		Vector2	pDestDir = pDestObj->GetDir();

		if (pDestDir == Vector2())
			assert(false);

		m_tDir = pDestDir;
		m_fDistance = 300.f;
		m_fKnockBack = pDestObj->GetMoveSpeed();

		pDestObj->TearDestroy();
	}
}
