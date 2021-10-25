
#include "Player.h"
#include "Mother.h"
#include "../Scene/BossRoom.h"
#include "../Scene/SceneManager.h"

void CPlayer::CheatBossRoom(float fTime)
{
	if (m_bDie || m_pScene->GetCurMapType() == ESpecial_RoomType::Boss)
		return;

	dynamic_cast<CStage*>(m_pScene)->MoveRoom<CBossRoom>(Vector2());
}
