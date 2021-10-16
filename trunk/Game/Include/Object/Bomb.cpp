
#include "Bomb.h"
#include "BombExplosionEffect.h"
#include "Block.h"
#include "Tear.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderSphere.h"

CBomb::CBomb()	:
	m_fTimer(0.f),
	m_fTimerMax(2.f),
	m_bDontMove(false),
	m_fInitialSpeed(0.f)
{
}

CBomb::CBomb(const CBomb& obj)	:
	CObj(obj),
	m_fTimer(0.f),
	m_bDontMove(false),
	m_fInitialSpeed(0.f)
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
	m_pColliderSphere->SetCollisionCollidingFunc<CBomb>(this, &CBomb::CollisionColliding);
	m_pColliderSphere->SetCollisionEndFunc<CBomb>(this, &CBomb::CollisionEnd);

	if (m_pScene->GetPlayer()->GetVelocity() != Vector2())
	{
		if (!m_bDontMove)
			m_bDontMove = true;
	}
}

void CBomb::Update(float fTime)
{
	CObj::Update(fTime);

	m_fTimer += fTime;

	if (m_fTimer >= m_fTimerMax)
		BombDestroy();

	if (m_fKnockBack != 0.f)
	{
		Move(m_tKnockBackDir, m_fKnockBack, true);

		m_fKnockBack -= GetMoveSpeedFrame();

		if (m_fKnockBack < 0.f)
			m_fKnockBack = 0.f;
	}

	if (!m_bDontMove && m_fInitialSpeed != 0.f)
	{
		Move(m_tMoveDir, m_fInitialSpeed, true);

		m_fInitialSpeed -= GetMoveSpeedFrame();
		
		if (m_fInitialSpeed < 0.f)
			m_fInitialSpeed = 0.f;
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
	std::string	strName = pDest->GetName();

	if (strName == "PlayerTear" ||
		strName == "MonsterTear")
	{
		CTear* pDestObj = dynamic_cast<CTear*>(pDest->GetOwner());
		Vector2	pDestDir = pDestObj->GetDir();

		m_tKnockBackDir = pDestDir;
		m_fKnockBack = pDestObj->GetMoveSpeed();

		pDestObj->TearDestroy();
	}

	else if (strName == "PlayerBody")
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pScene->GetPlayer());
		Vector2	tPlayerVelocity = pPlayer->GetVelocity();

		if (tPlayerVelocity == Vector2())
			m_bDontMove = true;

		if (!m_bDontMove)
		{
			tPlayerVelocity.Normalize();

			m_tMoveDir = tPlayerVelocity;

			m_fInitialSpeed = m_fMoveSpeed;
		}
	}
}

void CBomb::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	std::string	strName = pDest->GetName();
	CObj* pDestObj = pDest->GetOwner();
	ECollider_Type	eDestType = pDest->GetColliderType();

	if (strName == "PlayerHead")
		return;

	if (strName == "MapObject")
	{
		if ((strName == "MapObject") && dynamic_cast<CBlock*>(pDest->GetOwner())->GetType() == MT_SPIKE)
			return;

		m_fKnockBack = 0.f;
		m_fInitialSpeed = 0.f;
	}

	else if (strName == "Monster")
	{
	}

	else if (strName == "PlayerBody")
	{
		if (!m_bDontMove)
		{
			m_fInitialSpeed = m_fMoveSpeed;

			PushCollider(pSrc, pDest);
		}
	}
}

void CBomb::CollisionEnd(CCollider* pSrc, CCollider* pDest, float fTime)
{
	std::string	strName = pDest->GetName();

	if (strName == "PlayerBody")
	{
		if (m_bDontMove)
			m_bDontMove = false;
	}
}
