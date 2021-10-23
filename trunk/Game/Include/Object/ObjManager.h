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
	bool	m_bIsItem;
	bool	m_bChangedInfo;

public:
	void SetPlayerInfo(const CharacterInfo& pInfo, bool bIsItem)
	{
		m_tPlayerInfo = pInfo;
		m_bIsItem = bIsItem;
	}

public:
	bool IsChangedInfo()	const
	{
		return m_bChangedInfo;
	}

	bool IsItem()	const
	{
		return m_bIsItem;
	}

	const CharacterInfo& GetPlayerInfo()	const
	{
		return m_tPlayerInfo;
	}

public:
	void PushPlayerInfo(class CPlayer* pPlayer);
	void PullPlayerInfo(class CPlayer* pPlayer);
	void ResetPlayerHP();
};

