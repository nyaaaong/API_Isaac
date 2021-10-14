
#include "Charger.h"
#include "Block.h"
#include "EnemyDie.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Map/MapManager.h"
#include "../Map/RoomMap.h"
#include "../Collision/ColliderBox.h"

CCharger::CCharger()	:
	m_bChangeDir(false)
{
	m_fMaxDist = 300.f;

	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 10.f;
	m_tInfo.fHPMax = 10.f;
	m_tInfo.fTearTimer = 1.f;
	m_tInfo.fShotSpeed = 200.f;
	m_tInfo.fTearDistance = 300.f;
	m_tInfo.fMoveSpeed = 100.f;
}

CCharger::CCharger(const CCharger& obj):
	CMonsterBase(obj)
{
	m_bChangeDir = false;
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

	DetectPlayer();

	if (m_fKnockBack != 0.f)
	{
		Move(m_tKnockBackDir, m_fKnockBack, true);

		m_fKnockBack -= GetMoveSpeedFrame();

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

		CMonsterSpawner::GetInst()->EnemyDie1(m_tPos);
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

void CCharger::DetectPlayer()
{
	if (m_fM4PDist <= m_fMaxDist)
	{
		GetM2PDir();

		Move(m_tM2PDir, m_tInfo.fMoveSpeed + 50.f - m_fKnockBack, true);

		if (abs(m_tM2PDir.x) > abs(m_tM2PDir.y))
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
		ChagerPattern();
}

void CCharger::ChagerPattern()
{
	if (!m_bChangeDir)
	{
		int	iIdx = rand() % 4;

		m_tDir = m_arrDir[iIdx];
		m_bChangeDir = true;
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
	CMonsterBase::Move(tDir, fSpeed, bUseField);
	/*Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	Vector2	tBlockSize = CMapManager::GetInst()->GetBlockSize();
	Vector2	tBlockPivot = CMapManager::GetInst()->GetBlockPivot();
	Vector2	tBlock = tBlockSize * tBlockPivot;

	CRoomMap* pCurMap = m_pScene->GetCurrentMap();

	if (pCurMap)
	{
		if (pCurMap->IsObj(m_pScene, m_tPos.x - tBlock.x + tCurMove.x, m_tPos.y - tBlock.x + tCurMove.y, MT_ROCK) ||
			pCurMap->IsObj(m_pScene, m_tPos.x - tBlock.x + tCurMove.x, m_tPos.y - tBlock.x + tCurMove.y, MT_IRON) ||
			pCurMap->IsObj(m_pScene, m_tPos.x - tBlock.x + tCurMove.x, m_tPos.y - tBlock.x + tCurMove.y, MT_POOP))
		{
			m_bChangeDir = false;
			return;
		}
	}

	m_tVelocity += tCurMove;
	m_tPrevPos = m_tPos;
	m_tPos += tCurMove;

	if (bUseField)
	{
		if (m_pScene->CheckFieldPos(this))
		{
			m_tM2PDir *= -1.f;
			m_bChangeDir = false;
		}
	}*/
}

void CCharger::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	std::string	strDestName = pDest->GetName();

	if (strDestName == "PlayerBody")
		pDest->GetOwner()->SetDamage(1.f);

	else if (strDestName == "MapObject")
	{
		if (dynamic_cast<CBlock*>(pDest->GetOwner())->GetType() == MT_SPIKE)
			SetDamage(1.f);
	}
}

void CCharger::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}