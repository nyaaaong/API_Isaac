
#include "MonsterBase.h"
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
		fAngle = GetAngle(GetPos(), pPlayer->GetPos());

	m_tM2PDir.x = cosf(DegreeToRadian(fAngle));
	m_tM2PDir.y = sinf(DegreeToRadian(fAngle));
}

void CMonsterBase::Start()
{
	CCharacter::Start();
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

void CMonsterBase::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CMonsterBase::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CMonsterBase* CMonsterBase::Clone()
{
	return new CMonsterBase(*this);
}

CMonsterBase::CMonsterBase() :
	m_fFireTime(0.f),
	m_fFireTimeMax(1.f),
	m_iCount(0),
	m_fAccTime(0.f),
	m_fPatternDelay(2.f),
	m_bUsePattern(false),
	m_bDelayCheck(false)
{
	m_vecPattern.reserve(4);
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
}

CMonsterBase::~CMonsterBase()
{
}
