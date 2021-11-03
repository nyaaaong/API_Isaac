
#include "Isaac.h"
#include "MonsterBase.h"
#include "Tear.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Stage.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"
#include "../Scene/RoomBase.h"
#include "../Collision/ColliderBox.h"
#include "../UI/PlayerHUD.h"

CIsaac::CIsaac()	:
	m_fTearTimer(0.f),
	m_fPatternTimer(0.f),
	m_fPatternTimerMax(3.f),
	m_fPatternDelay(0.f),
	m_fMonsterSpawnTimer(0.f),
	m_fMonsterSpawnTimerMax(5.f),
	m_fFire1Delay(0.08f),
	m_fFire2Delay(0.2f),
	m_fFire1DelayMax(0.08f),
	m_fFire2DelayMax(0.2f),
	m_fM2PAngle2(1.f),
	m_iFire1BulletCount(0),
	m_iFire2BulletCount(0),
	m_iFire1BulletCountMax(1),
	m_iFire2BulletCountMax(8),
	m_bProgress(false),
	m_bNeedTransform(true),
	m_pPlayer(nullptr),
	m_eStatus(EIsaac_Status::Lying),
	m_eDieState(EDie_State::None),
	m_eFire1State(EFire_State::None),
	m_eFire2State(EFire_State::None)
{
	m_fMaxDist = 10000.f;

	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 500.f;
	m_tInfo.fHPMax = 500.f;
	m_tInfo.fTearSpeed = 1.0f;
	m_tInfo.fShotSpeed = 300.f;
	m_tInfo.fTearDistance = 1000.f;
	m_tInfo.fMoveSpeed = 600.f;
}

CIsaac::CIsaac(const CIsaac& obj) :
	CMonsterBase(obj),
	m_fTearTimer(0.f),
	m_fPatternTimer(0.f),
	m_fPatternDelay(0.f),
	m_fMonsterSpawnTimer(0.f),
	m_fFire1Delay(0.08f),
	m_fFire2Delay(0.2f),
	m_fM2PAngle2(1.f),
	m_iFire1BulletCount(0),
	m_iFire2BulletCount(0),
	m_bProgress(false),
	m_bNeedTransform(true),
	m_eStatus(EIsaac_Status::Lying),
	m_eDieState(EDie_State::None),
	m_eFire1State(EFire_State::None),
	m_eFire2State(EFire_State::None)
{
	m_fMaxDist = obj.m_fMaxDist;

	m_fPatternTimerMax = obj.m_fPatternTimerMax;
	m_pPlayer = obj.m_pPlayer;
	m_fMonsterSpawnTimerMax = obj.m_fMonsterSpawnTimerMax;
	m_fFire1DelayMax = obj.m_fFire1DelayMax;
	m_fFire2DelayMax = obj.m_fFire2DelayMax;
	m_iFire1BulletCountMax = obj.m_iFire1BulletCountMax;
	m_iFire2BulletCountMax = obj.m_iFire2BulletCountMax;
}

CIsaac::~CIsaac()
{
}

void CIsaac::Start()
{
	CMonsterBase::Start();

	CSceneManager::GetInst()->ChangeMusic(EMusic_Type::LastBoss);

	SetSize(240.f, 240.f);
	m_pColliderBox->SetCollisionCollidingFunc<CIsaac>(this, &CIsaac::CollisionColliding);

	SetAnimationEndNotify<CIsaac>("IsaacCreate", this, &CIsaac::TransformAnimEnd);
	SetAnimationEndNotify<CIsaac>("IsaacTransform", this, &CIsaac::TransformAnimEnd);
	SetAnimationEndNotify<CIsaac>("IsaacStandUp", this, &CIsaac::TransformAnimEnd);
	SetAnimationEndNotify<CIsaac>("IsaacJump", this, &CIsaac::JumpEnd);

	dynamic_cast<CStage*>(m_pScene)->GetPlayerHUD()->SetBossMonster(this);
}

bool CIsaac::Init()
{
	if (!CMonsterBase::Init())
		return false;

	SetSize(240.f, 240.f);
	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Monster);

	AddAnimation("IsaacCreate", false, 0.3f);
	AddAnimation("IsaacLying", true, 0.1f);
	AddAnimation("IsaacTransform", false, 0.3f);
	AddAnimation("IsaacStandUp", false, 0.3f);
	AddAnimation("IsaacStand", false, 0.3f);
	AddAnimation("IsaacJump", false, 0.4f);
	AddAnimation("IsaacIdle", true, 0.8f);
	AddAnimation("IsaacFlying", false, 0.4f);
	AddAnimation("IsaacLand", false, 0.4f);
	AddAnimation("IsaacCharge", false, 2.f);

	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetExtent(m_tSize * 0.4f);
	m_pColliderBox->SetCollisionProfile("Monster");

	return true;
}

void CIsaac::Update(float fTime)
{
	CMonsterBase::Update(fTime);

	if (m_tInfo.fHP <= 0.f)
		return;

	TransformAnim();
	DetectPlayer(fTime);
	BossPattern(fTime);
	MonsterSpawn(fTime);
	CheckPhase();
}

void CIsaac::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f && m_eDieState == EDie_State::None)
		BossDieEvent();

	else if (m_eDieState == EDie_State::Progress)
		BossDieEventProgress();

	else if (m_eDieState == EDie_State::Complete)
		BossDieEventEnd();		
}

CIsaac* CIsaac::Clone()
{
	return new CIsaac(*this);
}

void CIsaac::TransformAnim()
{
	if (!m_bNeedTransform)
		return;

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		ChangeAnimation("IsaacLying");
		m_bProgress = false;
		break;
	case EIsaac_Status::StandUp:
		ChangeAnimation("IsaacStandUp");
		m_pScene->GetSceneResource()->SoundPlay("IsaacStandUp");
		m_bProgress = true;
		break;
	case EIsaac_Status::Wing:
		ChangeAnimation("IsaacTransform");
		m_pScene->GetSceneResource()->SoundPlay("IsaacTransform");
		SetPos(m_tPos.x, m_tPos.y - 50.f);
		m_bProgress = true;
		break;
	}

	m_bNeedTransform = false;
}

void CIsaac::TransformAnimEnd()
{
	if (m_eStatus == EIsaac_Status::Wing)
	{
		m_bProgress = false;

		ChangeAnimation("IsaacIdle");
	}

	else if (m_eStatus == EIsaac_Status::StandUp)
	{
		m_bProgress = false;

		ChangeAnimation("IsaacStand");
	}
}

void CIsaac::CheckPhase()
{
	if (m_eStatus == EIsaac_Status::StandUp && m_tInfo.fHP / m_tInfo.fHPMax <= 0.5f)
	{
		m_eStatus = EIsaac_Status::Wing;
		m_bNeedTransform = true;
	}

	else if (m_eStatus == EIsaac_Status::Lying && m_tInfo.fHP / m_tInfo.fHPMax <= 0.7f)
	{
		m_eStatus = EIsaac_Status::StandUp;
		m_bNeedTransform = true;
	}
}

void CIsaac::BossPattern(float fTime)
{
	m_fPatternTimer += fTime;
	m_fTearTimer += fTime;

	if (m_eFire1State == EFire_State::Progress)
	{
		m_fPatternTimer = 0.f;

		FirePattern1Progress(fTime);
		return;
	}

	else if (m_eFire2State == EFire_State::Progress)
	{
		m_fPatternTimer = 0.f;

		FirePattern2Progress(fTime);
		return;
	}

	else
		FireLoop();	

	if (m_bProgress || m_fPatternTimer < m_fPatternTimerMax || m_bNeedTransform)
		return;

	m_fPatternTimer = 0.f;
	m_bProgress = true;

	float	fPercent = rand() % 10000 / 100.f;

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		if (fPercent < 50.f)
			Attack1(fTime);

		else
			Attack2(fTime);
		break;
	case EIsaac_Status::StandUp:
		if (fPercent < 50.f)
			Attack1(fTime);

		else
			Attack2(fTime);
		break;
	case EIsaac_Status::Wing:
		if (fPercent < 50.f)
			Attack1(fTime);

		else
			Attack2(fTime);
		break;
	}
}

void CIsaac::DetectPlayer(float fTime)
{
	GetM2PDir();

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		break;
	case EIsaac_Status::StandUp:
		break;
	case EIsaac_Status::Wing:
		BossMoveToPlayer();
		break;
	}
}

void CIsaac::Attack1(float fTime)
{
	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		FireCross();
		break;
	case EIsaac_Status::StandUp:
		JumpPattern1();
		break;
	case EIsaac_Status::Wing:
		FirePattern1();
		break;
	}
}

void CIsaac::Attack2(float fTime)
{
	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		Fire8Dir();
		break;
	case EIsaac_Status::StandUp:
		JumpPattern2();
		break;
	case EIsaac_Status::Wing:
		FirePattern2();
		break;
	}
}

void CIsaac::JumpPattern1()
{
	m_bProgress = true;

	ChangeAnimation("IsaacJump");

	FireCross(ESpecial_Tear::Special);
}

void CIsaac::JumpPattern2()
{
	m_bProgress = true;

	ChangeAnimation("IsaacJump");

	FireReverseCross(ESpecial_Tear::Reverse);
}

void CIsaac::JumpEnd()
{
	m_bProgress = false;

	ChangeAnimation("IsaacStand");
}

void CIsaac::FireLoop()
{
	if (m_fTearTimer < m_tInfo.fTearSpeed)
		return;

	m_fTearTimer = 0.f;

	GetM2PDir();

	float	fPercent = rand() % 10000 / 100.f;

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		if (fPercent < 50.f)
		{
			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear->SetDir(m_tM2PDir);
			pTear->SetOwner(this);
		}

		else
		{
			CSharedPtr<CTear>	pTear1 = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			CSharedPtr<CTear>	pTear2 = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear1->SetDir(m_fM2PAngle + 30.f);
			pTear2->SetDir(m_fM2PAngle - 30.f);
			pTear1->SetOwner(this);
			pTear2->SetOwner(this);
		}
		break;
	case EIsaac_Status::StandUp:
	{
		CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pTear->SetDir(m_tM2PDir);
		pTear->SetOwner(this); 
	}
		break;
	case EIsaac_Status::Wing:
	{
		CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		CSharedPtr<CTear>	pTear1 = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		CSharedPtr<CTear>	pTear2 = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pTear->SetDir(m_tM2PDir);
		pTear1->SetDir(m_fM2PAngle + 30.f);
		pTear2->SetDir(m_fM2PAngle - 30.f);
		pTear->SetOwner(this);
		pTear1->SetOwner(this);
		pTear2->SetOwner(this);
	}
		break;
	}
}

void CIsaac::FireCross(ESpecial_Tear eSpecialPattern)
{
	for (int i = 0; i < 4; ++i)
	{
		CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pTear->SetDir(90.f * i);
		pTear->SetOwner(this);
		pTear->SetSpecialTear(eSpecialPattern);
	}

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		m_pScene->GetSceneResource()->SoundPlay("IsaacCrying1");
		break;
	case EIsaac_Status::StandUp:
		m_pScene->GetSceneResource()->SoundPlay("IsaacJump");
		break;
	case EIsaac_Status::Wing:
		break;
	}

	m_bProgress = false;
}

void CIsaac::FireReverseCross(ESpecial_Tear eSpecialPattern)
{
	CSharedPtr<CTear>	pLT = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
	pLT->SetDir(-135.f);
	pLT->SetOwner(this);
	pLT->SetSpecialTear(eSpecialPattern);

	CSharedPtr<CTear>	pRT = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
	pRT->SetDir(-45.f);
	pRT->SetOwner(this);
	pRT->SetSpecialTear(eSpecialPattern);

	CSharedPtr<CTear>	pLB = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
	pLB->SetDir(135.f);
	pLB->SetOwner(this);
	pLB->SetSpecialTear(eSpecialPattern);

	CSharedPtr<CTear>	pRB = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
	pRB->SetDir(45.f);
	pRB->SetOwner(this);
	pRB->SetSpecialTear(eSpecialPattern);

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		break;
	case EIsaac_Status::StandUp:
		m_pScene->GetSceneResource()->SoundPlay("IsaacJump");
		break;
	case EIsaac_Status::Wing:
		break;
	}

	m_bProgress = false;
}

void CIsaac::Fire8Dir()
{
	float	fAngle = 0.f;

	for (int i = 0; i < 8; ++i)
	{
		CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
		pTear->SetDir(45.f * i);
		pTear->SetOwner(this);
	}

	switch (m_eStatus)
	{
	case EIsaac_Status::Lying:
		m_pScene->GetSceneResource()->SoundPlay("IsaacCrying2");
		break;
	case EIsaac_Status::StandUp:
		break;
	case EIsaac_Status::Wing:
		break;
	}

	m_bProgress = false;
}

void CIsaac::FirePattern1()
{
	m_eFire1State = EFire_State::Progress;

	m_iFire1BulletCountMax = rand() % 6 + 2; // 2~7
}

void CIsaac::FirePattern1Progress(float fTime)
{
	m_fFire1Delay += fTime;

	if (m_fFire1Delay >= m_fFire1DelayMax)
	{
		m_fFire1Delay = 0.f;

		for (int i = 0; i < 5; ++i)
		{
			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear->SetDir(36.f * i);
			pTear->SetOwner(this);
		}

		for (int i = 1; i <= 5; ++i)
		{
			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear->SetDir(-36.f * i);
			pTear->SetOwner(this);
		}

		m_pScene->GetSceneResource()->SoundPlay("IsaacFire");

		++m_iFire1BulletCount;
	}

	if (m_iFire1BulletCount >= m_iFire1BulletCountMax)
	{
		m_eFire1State = EFire_State::Complete;
		m_bProgress = false;
		m_fFire1Delay = m_fFire1DelayMax; // 처음에 무조건 한발은 발사하도록 max값으로 넣어준다.
		m_iFire1BulletCount = 0;
	}
}

void CIsaac::FirePattern2()
{
	m_eFire2State = EFire_State::Progress;
}

void CIsaac::FirePattern2Progress(float fTime)
{
	m_fFire2Delay += fTime;

	if (m_fFire2Delay >= m_fFire2DelayMax)
	{
		m_fFire2Delay = 0.f;

		for (int i = 0; i < 5; ++i)
		{
			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear->SetDir(36.f * i);
			pTear->SetOwner(this);
		}

		for (int i = 1; i <= 5; ++i)
		{
			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tPos, Vector2(80.f, 80.f));
			pTear->SetDir(-36.f * i);
			pTear->SetOwner(this);
		}

		m_pScene->GetSceneResource()->SoundPlay("IsaacFire");

		++m_iFire2BulletCount;
	}

	if (m_iFire2BulletCount >= m_iFire2BulletCountMax)
	{
		m_eFire2State = EFire_State::Complete;
		m_bProgress = false;
		m_fFire2Delay = m_fFire2DelayMax; // 처음에 무조건 한발은 발사하도록 max값으로 넣어준다.
		m_iFire2BulletCount = 0;
	}
}

void CIsaac::BossDieEvent()
{
	m_eDieState = EDie_State::Progress;

	CSceneManager::GetInst()->ChangeMusic(EMusic_Type::BossClear);
	m_pScene->GetSceneResource()->SoundPlay("IsaacDie");

	ChangeAnimation("IsaacFlying");
}

void CIsaac::BossDieEventProgress()
{
	if (!IsEndAnimation()) // Flying 모션이 끝나지 않았다면 리턴
		return;

	if (m_tPos.y + m_tSize.y * m_tPivot.y + m_tOffset.y < 0.f) // 보스의 발밑이 화면 밖으로 올라간 경우
	{
		m_eDieState = EDie_State::Complete;
		return;
	}

	Move(Vector2::UP, false);
}

void CIsaac::BossDieEventEnd()
{
	CMonsterSpawner::GetInst()->KillBossMonster();
	Destroy();
}

void CIsaac::BossMoveToPlayer()
{
	if (m_eDieState != EDie_State::None || m_bProgress)
		return;

	if (m_eStatus == EIsaac_Status::Wing)
	{
		GetM2PDir2();

		Move(m_tM2PDir2, true);
	}
}

void CIsaac::GetM2PDir2()
{
	CObj* pPlayer = m_pScene->GetPlayer();

	if (pPlayer)
	{
		Vector2	tPlayerPos = pPlayer->GetPos();

		if (tPlayerPos.x < m_tPos.x)
			m_fM2PAngle2 = GetAngle(Vector2(m_tPos.x, m_tPos.y), Vector2(tPlayerPos.x + 300.f, tPlayerPos.y));

		else if (tPlayerPos.x >= m_tPos.x)
			m_fM2PAngle2 = GetAngle(Vector2(m_tPos.x, m_tPos.y), Vector2(tPlayerPos.x - 300.f, tPlayerPos.y));
	}

	if (isnan<float>(m_fM2PAngle2))
		return;

	float	fDegree = DegreeToRadian(m_fM2PAngle2);

	m_tM2PDir2.x = cosf(fDegree);
	m_tM2PDir2.y = sinf(fDegree);
}

void CIsaac::MonsterSpawn(float fTime)
{
	// 날아서 사라졌을 경우 예외처리를 추가로 해야한다.
	if (m_eStatus != EIsaac_Status::StandUp || m_bNeedTransform)
		return;

	m_fMonsterSpawnTimer += fTime;

	if (m_fMonsterSpawnTimer >= m_fMonsterSpawnTimerMax)
	{
		m_fMonsterSpawnTimer = 0.f;

		CRoomBase* pScene = dynamic_cast<CRoomBase*>(m_pScene);

		if (pScene->GetMonsterCount() <= 0)
		{
			float x = static_cast<float>(CGameManager::GetInst()->GetResolution().iW);
			float y = m_pScene->GetFieldLT().y + 100.f;

			CMonsterSpawner::GetInst()->CreateMonster("AngelBaby", Vector2(x * 0.4f, y));
			CMonsterSpawner::GetInst()->CreateMonster("AngelBaby", Vector2(x * 0.6f, y));

			pScene->AddMonsterCount(2);
		}
	}
}

void CIsaac::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (m_tInfo.fHP > 0.f)
		CMonsterBase::CollisionColliding(pSrc, pDest, fTime);
}
