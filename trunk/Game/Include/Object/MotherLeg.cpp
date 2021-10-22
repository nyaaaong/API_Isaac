
#include "MotherLeg.h"
#include "Mother.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CMotherLeg::CMotherLeg()	:
	m_pMother(nullptr),
	m_bAttack(false),
	m_bAttackEnd(false),
	m_fAttackDelay(0.f),
	m_fIdleTime(0.f),
	m_bAttackPossible(false)
{
}

CMotherLeg::CMotherLeg(const CMotherLeg& obj)	:
	CObj(obj)
{
	m_pMother = obj.m_pMother;
	m_bAttack = false;
	m_bAttackEnd = false;
	m_fAttackDelay = 0.f;
	m_fIdleTime = 0.f;
	m_bAttackPossible = false;
}

CMotherLeg::~CMotherLeg()
{
}

void CMotherLeg::Start()
{
	CObj::Start();
}

bool CMotherLeg::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 1.f);
	SetPos(0.f, 0.f);
	SetZOrder(EZOrder::MotherLeg);

	SetTexture("MotherLegShortest", TEXT("Monster/Boss/Mother_Leg_Shortest.bmp"));
	SetTextureColorKey();
	SetTexture("MotherLegShort", TEXT("Monster/Boss/Mother_Leg_Short.bmp"));
	SetTextureColorKey();
	SetTexture("MotherLegNormal", TEXT("Monster/Boss/Mother_Leg_Normal.bmp"));
	SetTextureColorKey();
	SetTexture("MotherLegLong", TEXT("Monster/Boss/Mother_Leg_Long.bmp"));
	SetTextureColorKey();
	SetTexture("MotherLegLongest", TEXT("Monster/Boss/Mother_Leg_Longest.bmp"));
	SetTextureColorKey();

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetOffset(0.f, -376.f);
	m_pColliderBox->SetCollisionProfile("Monster");
	m_pColliderBox->SetCollisionCollidingFunc<CMotherLeg>(this, &CMotherLeg::CollisionColliding);

	return true;
}

void CMotherLeg::Update(float fTime)
{
	CObj::Update(fTime);

	// 해상도에 따라 텍스쳐 짤림 방지를 위해 크기별로 만들었다.
	if (m_tPos.y <= 114.f)
		SetTexture("MotherLegShortest");

	else if (m_tPos.y <= 274.f)
		SetTexture("MotherLegShort");

	else if (m_tPos.y <= 434.f)
		SetTexture("MotherLegNormal");

	else if (m_tPos.y <= 594.f)
		SetTexture("MotherLegLong");

	else
		SetTexture("MotherLegLongest");

	if (!m_bAttack)
	{
		m_fAttackDelay += fTime;

		if (m_fAttackDelay >= 1.f)
		{
			m_pScene->GetSceneResource()->SoundPlay("MotherAttack");

			m_fAttackDelay = 0.f;
			m_bAttack = true;
		}
	}

	DetectPlayer(fTime);
}

void CMotherLeg::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);

	if (!m_pMother->IsActive())
		Destroy();
}

CMotherLeg* CMotherLeg::Clone()
{
	return new CMotherLeg(*this);
}

void CMotherLeg::EnableTask()
{
	m_pScene->GetSceneResource()->SoundPlay("MotherCall1");
}

float CMotherLeg::SetDamage(float fDamage)
{
	fDamage = CObj::SetDamage(fDamage);

	m_pMother->SetDamage(fDamage);

	return fDamage;
}

void CMotherLeg::DetectPlayer(float fTime)
{
	CObj* pPlayerBody = m_pScene->GetPlayerBody();

	if (!m_bAttack)
	{
		m_tPlayerPos = pPlayerBody->GetPos() - pPlayerBody->GetSize() * pPlayerBody->GetPivot() + pPlayerBody->GetOffset();
		m_tPos.x = m_tPlayerPos.x;
		m_tPos.y = 0.f;
	}

	else
	{
		if (!m_bAttackPossible)
		{
			m_fAttackDelay += fTime;

			if (m_fAttackDelay >= 0.6f)
			{
				m_fAttackDelay = 0.f;
				m_bAttackPossible = true;
			}
		}

		else
		{
			if (!m_bAttackEnd && m_tPos.y >= m_tPlayerPos.y)
			{
				if (m_fIdleTime == 0.f)
				{
					m_tPos.y = m_tPlayerPos.y;
					m_pScene->GetSceneResource()->SoundPlay("MotherAttackEnd");
				}

				m_fIdleTime += fTime;

				if (m_fIdleTime >= 1.5f)
				{
					m_bAttackEnd = true;
				}
			}

			else
				Move(m_tPlayerPos, 10.f, false);
		}
	}
}

void CMotherLeg::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	float	fCurMove = 0.f;
	
	if (!m_bAttackEnd)
	{
		fCurMove = tDir.y * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
		m_tVelocity.y += fCurMove;
		m_tPrevPos.y = m_tPos.y;
		m_tPos.y += fCurMove;
	}

	else if (m_bAttackEnd)
	{
		fCurMove = -tDir.y * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
		m_tVelocity.y += fCurMove;
		m_tPrevPos.y = m_tPos.y;
		m_tPos.y += fCurMove;
	}

	if (m_tPos.y <= 0.f)
	{
		m_bAttack = false;
		m_bAttackEnd = false;
		m_fAttackDelay = 0.f;

		Disable();
	}
}

void CMotherLeg::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	std::string	strName = pDest->GetName();
	CObj* pPlayer = pDest->GetOwner();

	if (strName == "PlayerHead" || strName == "PlayerBody")
		pPlayer->SetDamage(1.f);
}
