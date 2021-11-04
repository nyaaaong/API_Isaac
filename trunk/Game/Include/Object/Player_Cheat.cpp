
#include "Player.h"
#include "PlayerBody.h"
#include "Mother.h"
#include "../Scene/BossRoom.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"

void CPlayer::CheatBossRoom(float fTime)
{
	if (m_bDie || m_pScene->GetCurMapType() == ESpecial_RoomType::Boss)
		return;

	dynamic_cast<CStage*>(m_pScene)->MoveRoom<CBossRoom>(Vector2());

	m_pScene->GetSceneResource()->SoundPlay("CheatOn");
}

void CPlayer::CheatNoDamage(float fTime)
{
	m_bCheatNoDamage = !m_bCheatNoDamage;

	if (m_bCheatNoDamage)
	{
		m_bEnableDamage = false;
		m_pPlayerBody->EnableDamage(false);
		m_bInvisible = false; // 깜빡이고 있었을 경우 해제
		m_pPlayerBody->Invisible(m_bInvisible);

		m_pScene->GetSceneResource()->SoundPlay("CheatOn");
	}

	else
	{
		m_fNoDmgTimer = 0.f;
		m_fBlinkTimer = 0.f;
		m_bEnableDamage = true;
		m_pPlayerBody->EnableDamage(false);
		m_bInvisible = false;
		m_pPlayerBody->Invisible(false);

		m_pScene->GetSceneResource()->SoundPlay("CheatOff");
	}
}

void CPlayer::CheatDamageUp(float fTime)
{
	if (m_tInfo.fAttack == 3.f)
	{
		m_tInfo.fAttack = 100.f;

		m_pScene->GetSceneResource()->SoundPlay("CheatOn");
	}

	else
	{
		m_tInfo.fAttack = 3.f;

		m_pScene->GetSceneResource()->SoundPlay("CheatOff");
	}
}

void CPlayer::CheatPlayerDie(float fTime)
{
	if (m_bDie)
		return;

	m_tInfo.fHP = 0.f;

	m_pScene->GetSceneResource()->SoundPlay("CheatOn");
}
