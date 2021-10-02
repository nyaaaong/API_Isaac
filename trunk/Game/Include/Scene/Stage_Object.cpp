
#include "Stage.h"
#include "../GameManager.h"
#include "../Map/RoomMap.h"
#include "../Object/Player.h"
#include "../Object/PlayerBody.h"
#include "../UI/PlayerHUD.h"

void CStage::CreateObjects()
{
	Resolution	tRS = CGameManager::GetInst()->GetResolution();

	Vector2	tPlayerPos = Vector2(tRS.iW / 5.f, tRS.iH / 2.f);

	CPlayer* pPlayer = CreateObject<CPlayer>("Player", tPlayerPos, Vector2(84.f, 75.f));

	SetPlayer(pPlayer);

	CPlayerBody* pPlayerBody = CreateObject<CPlayerBody>("PlayerBody", tPlayerPos, Vector2(56.f, 45.f));
	pPlayer->SetPlayerBody(pPlayerBody);
	pPlayerBody->SetPlayer(pPlayer);

	m_pPlayerHUD = CreateUIWindow<CPlayerHUD>("PlayerHUD");
	m_pPlayerHUD->SetPlayer(pPlayer);
}