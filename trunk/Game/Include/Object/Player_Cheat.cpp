
#include "Player.h"
#include "Mother.h"
#include "../Scene/BossRoom.h"

void CPlayer::CheatDie(float fTime)
{
	if (m_bDie)
		return;

	m_tInfo.fHP = 0.f;
}

void CPlayer::CheatBossRoom(float fTime)
{
	CStage* pStage = dynamic_cast<CStage*>(m_pScene);

	pStage->MoveRoom<CBossRoom>(Vector2());
}

void CPlayer::CheatBossHurt(float fTime)
{
	if (m_pMother)
		m_pMother->SetDamage(m_pMother->GetHP() * 0.99f);
}
