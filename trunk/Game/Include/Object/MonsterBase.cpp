
#include "MonsterBase.h"
#include "../GameManager.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "../Scene/Scene.h"
#include "../Object/Player.h"

void CMonsterBase::ShufflePattern()
{
	if (!m_bUsePattern)
		return;

	size_t	iSize = m_vecPattern.size();

	if (iSize <= 1)
		return;

	for (int i = 0; i < 10; ++i)
	{
		int	idx1 = rand() % iSize;
		int	idx2 = rand() % iSize;

		std::function<void(float)> pTemp = m_vecPattern[idx1];
		m_vecPattern[idx1] = m_vecPattern[idx2];
		m_vecPattern[idx2] = pTemp;
	}
}

void CMonsterBase::GetM2PDir()
{
	CObj* pPlayer = m_pScene->GetPlayer();

	float	fAngle = 0.f;

	if (pPlayer)
		fAngle = GetAngle(m_tPos, pPlayer->GetPos());

	m_tM2PDir.x = cosf(DegreeToRadian(fAngle));
	m_tM2PDir.y = sinf(DegreeToRadian(fAngle));
}

bool CMonsterBase::Init()
{
	if (!CCharacter::Init())
		return false;

	SetZOrder(EZOrder::Monster);
	SetPivot(0.5f, 1.f);

	CreateAnimation();

	return true;
}

void CMonsterBase::Update(float fTime)
{
	CCharacter::Update(fTime);

	if (1 <= m_vecPattern.size())
	{
		if (m_bDelayCheck)
		{
			m_fAccTime += fTime;

			if (m_fAccTime >= m_fPatternDelay)
			{
				ShufflePattern();

				m_fAccTime = 0.f;

				if (m_vecPattern[0])
					m_vecPattern[0](fTime);
			}
		}

		else
		{
			ShufflePattern();

			if (m_vecPattern[0])
				m_vecPattern[0](fTime);

			m_bDelayCheck = true;
		}
	}
}

void CMonsterBase::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

CMonsterBase* CMonsterBase::Clone()
{
	return new CMonsterBase(*this);
}

void CMonsterBase::Move(const Vector2& tDir, bool bUseField)
{
	Move(tDir, m_tInfo.fMoveSpeed, bUseField);
}

void CMonsterBase::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	m_tVelocity += tCurMove;
	m_tPrevPos = m_tPos;
	m_tPos += tCurMove;

	if (bUseField)
	{
		if (m_pScene->CheckFieldPos(this))
			m_tM2PDir *= -1.f;
	}
}

void CMonsterBase::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

CMonsterBase::CMonsterBase() :
	m_fFireTime(0.f),
	m_fFireTimeMax(1.f),
	m_iCount(0),
	m_fAccTime(0.f),
	m_fPatternDelay(2.f),
	m_bUsePattern(false),
	m_bDelayCheck(false),
	m_fM4PDist(static_cast<float>(INT_MAX)),
	m_fMaxDist(-1.f),
	m_bUseKnockBack(true)
{
	m_vecPattern.reserve(4);

	m_arrDir[0] = Vector2::LEFT;
	m_arrDir[1] = Vector2::UP;
	m_arrDir[2] = Vector2::RIGHT;
	m_arrDir[3] = Vector2::DOWN;
}

CMonsterBase::CMonsterBase(const CMonsterBase& obj)	:
	CCharacter(obj)
{
	m_tDir = obj.m_tDir;
	m_fFireTime = obj.m_fFireTime;
	m_fFireTimeMax = obj.m_fFireTimeMax;
	m_iCount = obj.m_iCount;
	m_iZOrder = obj.m_iZOrder;
	m_fAccTime = obj.m_fAccTime;
	m_fPatternDelay = obj.m_fPatternDelay;
	m_bUsePattern = obj.m_bUsePattern;
	m_bDelayCheck = obj.m_bDelayCheck;
	m_tM2PDir = obj.m_tM2PDir;
	m_fM4PDist = obj.m_fM4PDist;
	m_fMaxDist = obj.m_fMaxDist;
	m_bUseKnockBack = obj.m_bUseKnockBack;

	memcpy_s(m_arrDir, sizeof(Vector2) * 4, obj.m_arrDir, sizeof(Vector2) * 4);
}

CMonsterBase::~CMonsterBase()
{
}
