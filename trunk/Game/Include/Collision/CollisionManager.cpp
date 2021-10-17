
#include "CollisionManager.h"

CCollisionManager* CCollisionManager::m_pInst = nullptr;

bool CCollisionManager::Init()
{
	CreateProfile("Object", Channel_Object, true);
	CreateProfile("Door", Channel_Door, true);
	CreateProfile("PlayerHead", Channel_PlayerHead, true);
	CreateProfile("PlayerBody", Channel_PlayerBody, true);
	CreateProfile("Monster", Channel_Monster, true);
	CreateProfile("PlayerTear", Channel_PlayerAttack, true);
	CreateProfile("MonsterTear", Channel_MonsterAttack, true);
	CreateProfile("Bomb", Channel_Bomb, true);
	CreateProfile("BombExplosion", Channel_BombExplosion, true);
	CreateProfile("Effect", Channel_Effect, true);

	SetCollisionState("Door", Channel_Object, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_PlayerHead, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_PlayerBody, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_Monster, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_MonsterAttack, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_Bomb, ECollision_State::Ignore);
	SetCollisionState("Door", Channel_BombExplosion, ECollision_State::Ignore);

	SetCollisionState("Object", Channel_Object, ECollision_State::Ignore);
	SetCollisionState("Object", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("Object", Channel_PlayerHead, ECollision_State::Ignore);
	SetCollisionState("Object", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("Object", Channel_MonsterAttack, ECollision_State::Ignore);

	SetCollisionState("PlayerHead", Channel_Object, ECollision_State::Ignore);
	SetCollisionState("PlayerHead", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("PlayerHead", Channel_PlayerHead, ECollision_State::Ignore);
	SetCollisionState("PlayerHead", Channel_PlayerBody, ECollision_State::Ignore);
	SetCollisionState("PlayerHead", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("PlayerHead", Channel_Bomb, ECollision_State::Ignore);

	SetCollisionState("PlayerBody", Channel_PlayerHead, ECollision_State::Ignore);
	SetCollisionState("PlayerBody", Channel_PlayerBody, ECollision_State::Ignore);
	SetCollisionState("PlayerBody", Channel_PlayerAttack, ECollision_State::Ignore);

	SetCollisionState("Monster", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("Monster", Channel_MonsterAttack, ECollision_State::Ignore);
	SetCollisionState("Monster", Channel_Bomb, ECollision_State::Ignore);

	SetCollisionState("PlayerTear", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("PlayerTear", Channel_PlayerHead, ECollision_State::Ignore);
	SetCollisionState("PlayerTear", Channel_PlayerBody, ECollision_State::Ignore);
	SetCollisionState("PlayerTear", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("PlayerTear", Channel_MonsterAttack, ECollision_State::Ignore);
	SetCollisionState("PlayerTear", Channel_BombExplosion, ECollision_State::Ignore);

	SetCollisionState("MonsterTear", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("MonsterTear", Channel_Monster, ECollision_State::Ignore);
	SetCollisionState("MonsterTear", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("MonsterTear", Channel_MonsterAttack, ECollision_State::Ignore);
	SetCollisionState("MonsterTear", Channel_BombExplosion, ECollision_State::Ignore);

	SetCollisionState("BombExplosion", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("BombExplosion", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("BombExplosion", Channel_MonsterAttack, ECollision_State::Ignore);
	SetCollisionState("BombExplosion", Channel_BombExplosion, ECollision_State::Ignore);

	SetCollisionState("Effect", Channel_Object, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_Door, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_PlayerHead, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_PlayerBody, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_Monster, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_PlayerAttack, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_MonsterAttack, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_Bomb, ECollision_State::Ignore);
	SetCollisionState("Effect", Channel_BombExplosion, ECollision_State::Ignore);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& strName, ECollision_Channel eChannel, bool bEnable, ECollision_State eState)
{
	CollisionProfile* pProfile = FindProfile(strName);

	if (pProfile)
		return false;

	pProfile = new CollisionProfile;

	pProfile->strName = strName;
	pProfile->eChannel = eChannel;
	pProfile->bCollisionEnable = bEnable;
	pProfile->vecState.resize(Channel_Max);

	for (int i = 0; i < Channel_Max; ++i)
	{
		pProfile->vecState[i] = eState;
	}

	m_mapProfile.insert(std::make_pair(strName, pProfile));

    return true;
}

bool CCollisionManager::SetCollisionState(const std::string& strName, ECollision_Channel eChannel, ECollision_State eState)
{
	CollisionProfile* pProfile = FindProfile(strName);

	if (!pProfile)
		return false;

	pProfile->vecState[eChannel] = eState;

    return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& strName)
{
	std::unordered_map<std::string, CollisionProfile*>::iterator	iter = m_mapProfile.find(strName);

	if (iter == m_mapProfile.end())
		return nullptr;

    return iter->second;
}

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	std::unordered_map<std::string, CollisionProfile*>::iterator	iter = m_mapProfile.begin();
	std::unordered_map<std::string, CollisionProfile*>::iterator	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	m_mapProfile.clear();
}
