
#include "Mother.h"
#include "MotherLeg.h"
#include "MotherDoor.h"
#include "MonsterSpawner.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Collision/ColliderBox.h"

CMother::CMother()	:
	m_fPatternTimer(0.f),
	m_bFirstPattern(false),
	m_pLeg(nullptr),
	m_pDoor{}
{
	m_tInfo.fAttack = 1.f;
	m_tInfo.fHP = 200.f;
	m_tInfo.fHPMax = 200.f;
}

CMother::CMother(const CMother& obj)	:
	CMonsterBase(obj),
	m_pLeg(nullptr),
	m_pDoor{}
{
	m_fPatternTimer = obj.m_fPatternTimer;
	m_bFirstPattern = false;
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

	MotherPattern(fTime);
}

void CMother::PostUpdate(float fTime)
{
	CMonsterBase::PostUpdate(fTime);

	if (m_tInfo.fHP <= 0.f)
	{
		CSceneManager::GetInst()->ChangeMusic(EMusic_Type::BossClear);
		m_pScene->GetSceneResource()->SoundPlay("MotherDie");
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

void CMother::MotherPattern(float fTime)
{
	m_fPatternTimer += fTime;

	if (!m_bFirstPattern)
	{
		if (m_fPatternTimer >= 0.6f)
		{
			m_fPatternTimer = 0.f;
			m_pLeg->Enable();
			m_bFirstPattern = true;
		}
	}
}