
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

	if (m_bHit || !m_bEnableDamage)	// �ǰ��� �ưų� ���� �ð��� ���
	{
		if (m_bEnableDamage)	// �ǰݵ� ����
		{
			m_bHit = false;
			m_bEnableDamage = false;
			m_pPlayerBody->EnableDamage(m_bEnableDamage);

			m_pScene->GetSceneResource()->SoundPlay("PlayerHit");
		}

		else // �ǰ� �� ���� �ð��� ���
		{
			m_fNoDmgTimer += fTime;
			m_fBlinkTimer += fTime;

			if (m_fNoDmgTimer >= m_fNoDmgTimerMax)	// ���� ���� �ð��� ������ ���
			{
				m_fNoDmgTimer = 0.f;
				m_fBlinkTimer = 0.f;
				m_bEnableDamage = true;
				m_pPlayerBody->EnableDamage(m_bEnableDamage);
				m_bInvisible = false;
				m_pPlayerBody->Invisible(m_bInvisible);
			}

			else // ���� �ð��� ���
			{
				if (m_fBlinkTimer >= m_fBlinkSpeed) // �����̴� ȿ�� �߻�
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