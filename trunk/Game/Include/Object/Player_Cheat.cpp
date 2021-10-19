
#include "Player.h"

void CPlayer::CheatDie(float fTime)
{
	if (m_bDie)
		return;

	m_tInfo.fHP = 0.f;
}
