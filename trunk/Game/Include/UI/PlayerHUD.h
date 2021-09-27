#pragma once

#include "UIWindow.h"
#include "HPBar.h"
#include "BossHPBar.h"
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
	float		m_fPrevHP;

public:
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

