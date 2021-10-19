
#include "Player.h"
#include "Bomb.h"
#include "../Scene/Scene.h"

void CPlayer::Bomb(float fTime)
{
	if (m_bUseBomb || m_bDie)
		return;

	m_pScene->CreateObject<CBomb>("Bomb", "Bomb", Vector2(m_tPos.x, m_tPos.y + 30.f), Vector2(96.f, 96.f));

	UseBomb(true);
}