
#include "PlayerHUD.h"
#include "../GameManager.h"
#include "../Scene/Stage.h"
#include "../Scene/SceneManager.h"
#include "../Object/Player.h"
#include "../Object/BossMonstro.h"

bool CPlayerHUD::Init()
{
	if (!CUIWindow::Init())
		return false;

	Resolution	tRS = CGameManager::GetInst()->GetResolution();

	m_pHPBar = CreateWidget<CHPBar>("PlayerHPBar");

	m_pHPBar->SetTexture("PlayerHPBar0", 0, TEXT("UI/Player/HP_0.bmp"));
	m_pHPBar->SetTexture("PlayerHPBar1", 1, TEXT("UI/Player/HP_1.bmp"));
	m_pHPBar->SetTexture("PlayerHPBar2", 2, TEXT("UI/Player/HP_2.bmp"));
	m_pHPBar->SetTexture("PlayerHPBar3", 3, TEXT("UI/Player/HP_3.bmp"));
	m_pHPBar->SetTexture("PlayerHPBar4", 4, TEXT("UI/Player/HP_4.bmp"));
	m_pHPBar->SetTexture("PlayerHPBar5", 5, TEXT("UI/Player/HP_5.bmp"));
	m_pHPBar->SetTexture("PlayerHPBar6", 6, TEXT("UI/Player/HP_6.bmp"));

	m_pHPBar->SetTextureColorKey();
	m_pHPBar->SetPos(100.f, 100.f);

	m_pBossHPEmptyBar = CreateWidget<CBossHPBar>("BossHPEmptyBar");
	m_pBossHPBar = CreateWidget<CBossHPBar>("BossHPBar");

	m_pBossHPEmptyBar->SetTexture("BossHPEmptyBar", TEXT("UI/Boss/HP_Empty.bmp"));
	m_pBossHPEmptyBar->SetZOrder(EZOrder::BackGroundBar);
	m_pBossHPEmptyBar->SetTextureColorKey();
	m_pBossHPEmptyBar->SetPos(tRS.iW * 0.3f + 50, 53.f);
	m_pBossHPEmptyBar->SetBackGroundBar(true);

	m_pBossHPBar->SetTexture("BossHPBar", TEXT("UI/Boss/HP.bmp"));
	m_pBossHPBar->SetZOrder(EZOrder::UI);
	m_pBossHPBar->SetTextureColorKey();
	m_pBossHPBar->SetPos(tRS.iW * 0.3f + 101.f, 53.f);

	return true;
}

void CPlayerHUD::Update(float fTime)
{
	CUIWindow::Update(fTime);

	if (m_pPlayer)
	{
		m_pHPBar->SetHP(m_pPlayer->GetHP());
		m_pHPBar->Update(fTime);
	}

	if (m_pBossMonster)
	{
		if (!m_pBossMonster->IsDead())
		{
			m_pBossHPEmptyBar->SetVisibility(true);
			m_pBossHPBar->SetVisibility(true);

			float fCurHP = m_pBossMonster->GetHP();

			if (m_fPrevHP != fCurHP)
				m_pBossHPBar->SetHP(fCurHP);

			m_fPrevHP = fCurHP;
			return;
		}
	}

	m_pBossHPEmptyBar->SetVisibility(false);
	m_pBossHPBar->SetVisibility(false);
}

void CPlayerHUD::SetPlayer(CCharacter* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pHPBar->SetHP(m_pPlayer->GetHP());
}

void CPlayerHUD::SetBossMonster(CCharacter* pBossMonster)
{
	m_pBossMonster = pBossMonster;
	m_pBossHPBar->SetHP(m_pBossMonster->GetHP());
}

CPlayerHUD::CPlayerHUD()	:
	m_fPrevHP(100.f)
{
}

CPlayerHUD::~CPlayerHUD()
{
}