#pragma once

#include "UIWindow.h"
#include "HPBar.h"
#include "BossHPBar.h"
#include "Minimap.h"
#include "MinimapRoom.h"
#include "../Object/Character.h"

class CPlayerHUD :
	public CUIWindow
{
	friend class CScene;

private:
	CSharedPtr<CHPBar>	m_pHPBar;
	CSharedPtr<CBossHPBar>	m_pBossHPBar;
	CSharedPtr<CBossHPBar>	m_pBossHPEmptyBar;
	CSharedPtr<CCharacter> m_pPlayer;
	CSharedPtr<CCharacter> m_pBossMonster;
	CSharedPtr<CMinimap> m_pMinimap;
	CSharedPtr<CMinimapRoom> m_pMinimapRoom[11]; // StartRoom(0), Room1~9(1~9), ItemRoom(10)
	float		m_fPrevHP;
	float		m_fBossHPTimer; // 보스가 죽고 HP바가 떠있을 시간

public:
	// StartRoom = 0, ItemRoom = 10
	void ActiveMinimapRoom(int iRoonNum)
	{
		for (int i = 0; i < 11; ++i)
		{
			if (i == iRoonNum)
			{
				m_pMinimapRoom[i]->Enable();
				continue;
			}

			m_pMinimapRoom[i]->Disable();
		}
	}

	void SetHP(float fHP)
	{
		m_pHPBar->SetHP(fHP);
	}

public:
	void SetPlayer(class CCharacter* pPlayer);
	void SetBossMonster(class CCharacter* pBossMonster);

public:
	virtual bool Init();
	virtual void Update(float fTime);

private:
	CPlayerHUD();
	virtual ~CPlayerHUD();
};

