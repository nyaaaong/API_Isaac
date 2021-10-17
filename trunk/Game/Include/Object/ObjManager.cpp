#include "ObjManager.h"

CObjManager* CObjManager::m_pInst = nullptr;

CObjManager::CObjManager()	:
	m_tPlayerInfo{},
	m_bChangedInfo(false)
{
}

CObjManager::~CObjManager()
{
}

bool CObjManager::Init()
{
	return true;
}
void CObjManager::PushPlayerInfo(const CharacterInfo& tInfo)
{
	m_tPlayerInfo = tInfo;

	m_bChangedInfo = true;
}

void CObjManager::PullPlayerInfo(CharacterInfo& tInfo)
{
	if (!m_bChangedInfo)
		return;

	tInfo.fAttack = m_tPlayerInfo.fAttack;
	tInfo.fHP = m_tPlayerInfo.fHP;
	tInfo.fHPMax = m_tPlayerInfo.fHPMax;
	tInfo.fTearSpeed = m_tPlayerInfo.fTearSpeed;
	tInfo.fShotSpeed = m_tPlayerInfo.fShotSpeed;
	tInfo.fTearDistance = m_tPlayerInfo.fTearDistance;
	tInfo.fMoveSpeed = m_tPlayerInfo.fMoveSpeed;

	m_bChangedInfo = false;
}
