
#include "Stage.h"
#include "../Object/Player.h"
#include "../Object/PlayerBody.h"
#include "../UI/PlayerHUD.h"

void CStage::CreatePlayer(const Vector2& tStartPos)
{
	CPlayer* pPlayer = CreateObject<CPlayer>("Player", tStartPos, Vector2(84.f, 75.f));
	SetPlayer(pPlayer);

	CPlayerBody* pPlayerBody = CreateObject<CPlayerBody>("PlayerBody", tStartPos, Vector2(56.f, 45.f));

	pPlayer->SetPlayerBody(pPlayerBody);
	pPlayerBody->SetPlayer(pPlayer);

	m_pPlayerHUD = CreateUIWindow<CPlayerHUD>("PlayerHUD");
	m_pPlayerHUD->SetPlayer(pPlayer);
}
