
#include "Mother.h"
#include "MotherLeg.h"
#include "MotherDoor.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/RoomBase.h"
#include "../Collision/ColliderBox.h"

CMother::CMother()	:
	m_fPatternTimer(0.f),
	m_bFirstPattern(false),
	m_pLeg(nullptr),
	m_pDoor{},
	m_fPlayerPrevHP(6.f),
	m_pPlayer(nullptr),
	m_bProgress(false)
{
	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 200.f;
	m_tInfo.fHPMax = 200.f;
}

CMother::CMother(const CMother& obj)	:
	CMonsterBase(obj),
	m_pLeg(nullptr),
	m_pDoor{},
	m_pPlayer(nullptr),
	m_bProgress(false)
{
	m_fPatternTimer = obj.m_fPatternTimer;
	m_bFirstPattern = false;
	m_fPlayerPrevHP = obj.m_fPlayerPrevHP;
}

CMother::~CMother()
{
}

void CMother::Start()
{
	CMonsterBase::Start();

	m_pLeg->Disable();

	for (int i = 0; i < DD_MAX; ++i)
	{
		m_pDoor[i]->Disable();
	}

	m_pPlayer = dynamic_cast<CCharacter*>(m_pScene->GetPlayer());
	m_fPlayerPrevHP = m_pPlayer->GetHP();

	m_vecPatternFunc.push_back(std::bind(&CMother::SpawnLeg, this));
}

bool CMother::Init()
{
	if (!CMonsterBase::Init())
		return false;

	return true;
}

void CMother::Update(float fTime)
{
	CMonsterBase::Update(fTime);

	MotherPlayerHPUpdater();

	MotherPattern(fTime);
}

void CMother::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		CSceneManager::GetInst()->ChangeMusic(EMusic_Type::BossClear);
		m_pScene->GetSceneResource()->SoundPlay("MotherDie");
		dynamic_cast<CRoomBase*>(m_pScene)->SubMonsterCount();
		Destroy();
	}
}

CMother* CMother::Clone()
{
	return new CMother(*this);
}

void CMother::SetPart(CMotherLeg* pLeg, CMotherDoor** pDoor)
{
	m_pLeg = pLeg;

	for (int i = 0; i < DD_MAX; ++i)
	{
		m_pDoor[i] = pDoor[i];
	}
}

void CMother::MotherPlayerHPUpdater()
{
	float	fPlayerHP = m_pPlayer->GetHP();

	if (m_fPlayerPrevHP != fPlayerHP)
	{
		if (m_fPlayerPrevHP > fPlayerHP)
		{
			if (!m_pScene->GetSceneResource()->IsPlaying("MotherIsaacHit"))
				m_pScene->GetSceneResource()->SoundPlay("MotherIsaacHit");
		}

		m_fPlayerPrevHP = fPlayerHP;
	}
}

void CMother::MotherPattern(float fTime)
{
	if (!m_bFirstPattern)
	{
		m_fPatternTimer += fTime;

		if (m_fPatternTimer >= 0.6f)
		{
			if (!m_pLeg->IsEnable())
				m_pScene->GetSceneResource()->SoundPlay("MotherCall1");
		}

		SpawnLeg();

		if (!m_bProgress)
			m_bFirstPattern = true;
	}

	if (!m_bProgress)
	{
		m_fPatternTimer += fTime;

		if (m_fPatternTimer >= 5.f)
		{
			size_t iSize = m_vecPatternFunc.size();

			int iRand = rand() % iSize;

			m_vecPatternFunc[iRand]();
		}
	}
}

void CMother::SpawnLeg()
{
	if (m_fPatternTimer >= 0.6f)
	{
		m_fPatternTimer = 0.f;
		m_pLeg->Enable();

		m_bProgress = false;
		return;
	}

	m_bProgress = true;
}
