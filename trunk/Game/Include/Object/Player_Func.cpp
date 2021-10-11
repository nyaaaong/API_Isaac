
#include "Player.h"
#include "PlayerBody.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

void CPlayer::NoDamageTime(float fTime)
{
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