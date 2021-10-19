
#include "Player.h"
#include "PlayerBody.h"
#include "ObjManager.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "../Scene/Stage.h"
#include "../Scene/StartRoom.h"
#include "../Scene/SceneResource.h"

void CPlayer::NoDamageTime(float fTime)
{
	if (m_bDie)
		return;

	if (m_bHit || !m_bEnableDamage)	// 피격이 됐거나 무적 시간인 경우
	{
		if (m_bEnableDamage)	// 피격된 직후
		{
			m_bHit = false;
			m_bEnableDamage = false;
			m_pPlayerBody->EnableDamage(m_bEnableDamage);

			m_pScene->GetSceneResource()->SoundPlay("PlayerHit");
		}

		else // 피격 후 무적 시간인 경우
		{
			m_fNoDmgTimer += fTime;
			m_fBlinkTimer += fTime;

			if (m_fNoDmgTimer >= m_fNoDmgTimerMax)	// 만약 무적 시간이 끝났을 경우
			{
				m_fNoDmgTimer = 0.f;
				m_fBlinkTimer = 0.f;
				m_bEnableDamage = true;
				m_pPlayerBody->EnableDamage(m_bEnableDamage);
				m_bInvisible = false;
				m_pPlayerBody->Invisible(m_bInvisible);
			}

			else // 무적 시간인 경우
			{
				if (m_fBlinkTimer >= m_fBlinkSpeed) // 깜빡이는 효과 발생
				{
					m_fBlinkTimer = 0.f;
					m_bInvisible = !m_bInvisible;
					m_pPlayerBody->Invisible(m_bInvisible);
				}
			}
		}
	}
}

void CPlayer::IsaacDeath(float fTime)
{
	DefaultAnimation();

	m_bDie = true;
	m_bEnableDamage = false;
	m_bInvisible = false;

	CInput::GetInst()->LockInput(true);

	SetOffset(0.f, 0.f);

	m_pPlayerBody->Invisible(true);
	m_pPlayerBody->EnableDamage(false);

	ChangeAnimation("IsaacDeath");

	m_pScene->GetSceneResource()->SoundPlay("PlayerDie");
}

void CPlayer::IsaacDeathEnd()
{
	CInput::GetInst()->LockInput(false);
	m_bEnableDamage = true;

	m_pPlayerBody->Invisible(false);
	m_pPlayerBody->EnableDamage(true);

	m_tInfo.fHP = m_tInfo.fHPMax;

	CObjManager::GetInst()->ResetPlayerHP();

	dynamic_cast<CStage*>(m_pScene)->MoveRoom<CStartRoom>(Vector2::RIGHT);
}