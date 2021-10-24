
#include "PlayerHUD.h"
#include "../GameManager.h"
#include "../Scene/Stage.h"
#include "../Scene/SceneManager.h"
#include "../Object/Player.h"

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
	m_pBossHPEmptyBar->SetVisibility(false);

	m_pBossHPBar->SetTexture("BossHPBar", TEXT("UI/Boss/HP.bmp"));
	m_pBossHPBar->SetZOrder(EZOrder::UI);
	m_pBossHPBar->SetTextureColorKey();
	m_pBossHPBar->SetPos(tRS.iW * 0.3f + 101.f, 53.f);
	m_pBossHPBar->SetVisibility(false);

	m_pMinimap = CreateWidget<CMinimap>("Minimap");

	Vector2	tMinimapSize = m_pMinimap->GetSize();
	m_pMinimap->SetPos((float)tRS.iW - tMinimapSize.x, 0.f);

	char cName[32] = {};
	char cNum[4] = {};
	Vector2	tMinimapPos = m_pMinimap->GetPos();

	for (int i = 1; i <= 9; ++i) // 1~9번째 인덱스는 Room1~9
	{
		memset(cName, 0, sizeof(char) * 32);
		memset(cNum, 0, sizeof(char) * 4);

		sprintf_s(cNum, "%d", i + 1);
		strcpy_s(cName, "ActiveRoom");
		strcat_s(cName, cNum);

		m_pMinimapRoom[i] = CreateWidget<CMinimapRoom>(cName);
		m_pMinimapRoom[i]->SetPos(tMinimapPos);
		m_pMinimapRoom[i]->SetRoomType(EMinimapRoom_Type::Normal);
		m_pMinimapRoom[i]->Disable();
	}

	// 0번째 인덱스는 StartRoom
	m_pMinimapRoom[0] = CreateWidget<CMinimapRoom>("ActiveStartRoom");
	m_pMinimapRoom[0]->SetPos(tMinimapPos.x + 62.f, tMinimapPos.y + 10.f);
	m_pMinimapRoom[0]->SetRoomType(EMinimapRoom_Type::Normal);
	m_pMinimapRoom[0]->Disable();

	m_pMinimapRoom[1]->SetPos(tMinimapPos.x + 38.f, tMinimapPos.y + 31.f);

	m_pMinimapRoom[2]->SetPos(tMinimapPos.x + 62.f, tMinimapPos.y + 31.f);

	m_pMinimapRoom[3]->SetPos(tMinimapPos.x + 86.f, tMinimapPos.y + 31.f);

	m_pMinimapRoom[4]->SetPos(tMinimapPos.x + 38.f, tMinimapPos.y + 52.f);

	m_pMinimapRoom[5]->SetPos(tMinimapPos.x + 86.f, tMinimapPos.y + 52.f);

	m_pMinimapRoom[6]->SetPos(tMinimapPos.x + 110.f, tMinimapPos.y + 52.f);

	m_pMinimapRoom[7]->SetPos(tMinimapPos.x + 86.f, tMinimapPos.y + 73.f);

	m_pMinimapRoom[8]->SetPos(tMinimapPos.x + 62.f, tMinimapPos.y + 73.f);

	m_pMinimapRoom[9]->SetPos(tMinimapPos.x + 62.f, tMinimapPos.y + 94.f);

	// 10번째 인덱스는 ItemRoom
	m_pMinimapRoom[10] = CreateWidget<CMinimapRoom>("ActiveItemRoom");
	m_pMinimapRoom[10]->SetPos(tMinimapPos.x + 14.f, tMinimapPos.y + 52.f);
	m_pMinimapRoom[10]->SetRoomType(EMinimapRoom_Type::Item);
	m_pMinimapRoom[10]->Disable();

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
			return;
		}

		else
		{
			m_fBossHPTimer += fTime;

			if (m_fBossHPTimer >= 2.f)
			{
				m_pBossHPEmptyBar->SetVisibility(false);
				m_pBossHPBar->SetVisibility(false);

				m_pBossMonster = nullptr;
			}
		}
	}
}

void CPlayerHUD::SetPlayer(CCharacter* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pHPBar->SetHP(m_pPlayer->GetHP());
}

void CPlayerHUD::SetBossMonster(CCharacter* pBossMonster)
{
	m_pBossMonster = pBossMonster;
	m_pBossHPBar->SetBoss(m_pBossMonster);
}

CPlayerHUD::CPlayerHUD()	:
	m_fPrevHP(100.f),
	m_fBossHPTimer(0.f)
{
}

CPlayerHUD::~CPlayerHUD()
{
}
