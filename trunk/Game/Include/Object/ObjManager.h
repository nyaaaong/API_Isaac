#pragma once

#include "../GameInfo.h"

class CObjManager
{
private:
	CObjManager();
	~CObjManager();

private:
	static CObjManager* m_pInst;
	
public:
	static CObjManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CObjManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

public:
	bool Init();

private:
	CharacterInfo	m_tPlayerInfo;
	bool	m_bChangedInfo;

public:
	void SetPlayerInfo(const CharacterInfo& pInfo)
	{
		m_tPlayerInfo = pInfo;
	}

public:
	bool IsChangedInfo()	const
	{
		return m_bChangedInfo;
	}

	const CharacterInfo& GetPlayerInfo()	const
	{
		return m_tPlayerInfo;
	}

public:
	void PushPlayerInfo(const CharacterInfo& tInfo);
	void PullPlayerInfo(CharacterInfo& tInfo);
};

