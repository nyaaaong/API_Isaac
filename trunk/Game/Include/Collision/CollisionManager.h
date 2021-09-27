
#pragma once

#include "../GameInfo.h"

class CCollisionManager
{
private:
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;

public:
	bool Init();
	bool CreateProfile(const std::string& strName, ECollision_Channel eChannel, bool bEnable, ECollision_State eState = ECollision_State::Collision);
	bool SetCollisionState(const std::string& strName, ECollision_Channel eChannel, ECollision_State eState = ECollision_State::Collision);
	CollisionProfile* FindProfile(const std::string& strName);

private:
	static CCollisionManager* m_pInst;

public:
	static CCollisionManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCollisionManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	CCollisionManager();
	~CCollisionManager();
};

