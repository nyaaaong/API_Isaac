
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
	m_bProgress(false),
	m_fFirstDelay(0.f),
	m_fPatternDelay(0.f),
	m_fPatternTimerMax(0.4f)
{
	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 200.f;
	m_tInfo.fHPMax = 200.f;
	m_tInfo.fTearSpeed = 1.f;
	m_tInfo.fShotSpeed = 500.f;
	m_tInfo.fTearDistance = 1000.f;
	m_tInfo.fMoveSpeed = 200.f;
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
	m_fFirstDelay = 0.f;
	m_fPatternDelay = 0.f;
	m_fPatternTimerMax = obj.m_fPatternTimerMax;
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
	m_vecPatternFunc.push_back(std::bind(&CMother::SpawnEye, this));
	m_vecPatternFunc.push_back(std::bind(&CMother::SpawnSkin, this));
	m_vecPatternFunc.push_back(std::bind(&CMother::Call1, this));
	//m_vecPatternFunc.push_back(std::bind(&CMother::Call2, this));
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
		dynamic_cast<CRoomBase*>(m_pScene)->SubBossMonsterCount();
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
	m_fPatternDelay += fTime;

	if (!m_bFirstPattern)
		SpawnLeg();

	else if (!m_bProgress)
	{
		m_fPatternTimer += fTime;

		if (m_fPatternTimer >= m_fPatternTimerMax)
		{
			m_fPatternTimer = 0.f;

			float	fPercent = rand() % 10000 / 100.f;

			if (fPercent < 5.f)
				m_vecPatternFunc[MP_CALL1]();

			else if (fPercent < 35.f)
				m_vecPatternFunc[MP_LEG]();

			else if (fPercent < 65.f)
				m_vecPatternFunc[MP_EYE]();

			else
				m_vecPatternFunc[MP_SKIN]();
		}
	}
}

void CMother::EnableRandomDoor(EMotherDoor_Type eType)
{
	int iCount = rand() % 3 + 1;

	for (int i = 0; i < iCount; ++i)
	{
		int iIdx = rand() % DD_MAX;

		if (m_pDoor[iIdx]->IsEnable())
			continue;

		else
		{
			m_pDoor[iIdx]->Enable();
			m_pDoor[iIdx]->SetDoorType(eType);
		}
	}
}

void CMother::AddPatternTimer(float fValue)
{
	m_fPatternTimerMax = 0.4f;
	m_fPatternTimerMax += fValue;
}

void CMother::SpawnLeg()
{
	if (!m_bFirstPattern)
	{
		if (!m_pScene->GetSceneResource()->IsPlaying("MotherCall1"))
			m_pScene->GetSceneResource()->SoundPlay("MotherCall1");

		if (m_fPatternDelay >= 0.2f)
		{
			m_fPatternDelay = 0.f;

			if (!m_bFirstPattern)
			{
				m_fFirstDelay = 0.f;
				m_bFirstPattern = true;
			}

			m_pLeg->Enable();

			return;
		}
	}

	else
		m_pLeg->Enable();

	m_bProgress = true;
}

void CMother::SpawnEye()
{
	EnableRandomDoor(EMotherDoor_Type::Eye);
}

void CMother::SpawnSkin()
{
	EnableRandomDoor(EMotherDoor_Type::Skin);
}

void CMother::Call1()
{
	m_pScene->GetSceneResource()->SoundPlay("MotherCall1");
	m_bProgress = false;
}

void CMother::Call2()
{
	m_pScene->GetSceneResource()->SoundPlay("MotherCall2");
	m_bProgress = false;
}