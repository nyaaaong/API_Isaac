
#include "ObjManager.h"
#include "Player.h"

CObjManager* CObjManager::m_pInst = nullptr;

CObjManager::CObjManager()	:
	m_tPlayerInfo{},
	m_bChangedInfo(false),
	m_bIsItem(false)
{
}

CObjManager::~CObjManager()
{
}

bool CObjManager::Init()
{
	return true;
}

// Scene에서 플레이어 정보를 Manager에게 넘겨줄 때
void CObjManager::PushPlayerInfo(CPlayer* pPlayer)
{
	m_tPlayerInfo = pPlayer->m_tInfo;
	m_bIsItem = pPlayer->m_bIsItem;

	m_bChangedInfo = true;
}

// Manager에 저장되어 있던 플레이어 정보를 새로운 Scene의 플레이어에게 넘겨줄 때
void CObjManager::PullPlayerInfo(CPlayer* pPlayer)
{
	if (!m_bChangedInfo)
		return;

	pPlayer->m_tInfo.fAttack = m_tPlayerInfo.fAttack;
	pPlayer->m_tInfo.fHP = m_tPlayerInfo.fHP;
	pPlayer->m_tInfo.fHPMax = m_tPlayerInfo.fHPMax;
	pPlayer->m_tInfo.fTearSpeed = m_tPlayerInfo.fTearSpeed;
	pPlayer->m_tInfo.fShotSpeed = m_tPlayerInfo.fShotSpeed;
	pPlayer->m_tInfo.fTearDistance = m_tPlayerInfo.fTearDistance;
	pPlayer->m_tInfo.fMoveSpeed = m_tPlayerInfo.fMoveSpeed;

	pPlayer->m_bIsItem = m_bIsItem;

	m_bChangedInfo = false;
}

void CObjManager::ResetPlayerHP()
{
	m_tPlayerInfo.fHP = PLAYER_HP_MAX;
	m_tPlayerInfo.fHPMax = PLAYER_HP_MAX;
}
