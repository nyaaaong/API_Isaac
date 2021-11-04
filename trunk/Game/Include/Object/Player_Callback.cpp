
#include "Player.h"
#include "../Input.h"

void CPlayer::AddCallback()
{
	CInput::GetInst()->SetCallback<CPlayer>("PlayerMoveUp", KS_PUSH, this, &CPlayer::MoveUp);
	CInput::GetInst()->SetCallback<CPlayer>("PlayerMoveDown", KS_PUSH, this, &CPlayer::MoveDown);
	CInput::GetInst()->SetCallback<CPlayer>("PlayerMoveLeft", KS_PUSH, this, &CPlayer::MoveLeft);
	CInput::GetInst()->SetCallback<CPlayer>("PlayerMoveRight", KS_PUSH, this, &CPlayer::MoveRight);

	CInput::GetInst()->SetCallback<CPlayer>("PlayerFireUp", KS_PUSH, this, &CPlayer::FireUp);
	CInput::GetInst()->SetCallback<CPlayer>("PlayerFireLeft", KS_PUSH, this, &CPlayer::FireLeft);
	CInput::GetInst()->SetCallback<CPlayer>("PlayerFireDown", KS_PUSH, this, &CPlayer::FireDown);
	CInput::GetInst()->SetCallback<CPlayer>("PlayerFireRight", KS_PUSH, this, &CPlayer::FireRight);

	CInput::GetInst()->SetCallback<CPlayer>("PlayerBomb", KS_DOWN, this, &CPlayer::Bomb);

	CInput::GetInst()->SetCallback<CPlayer>("CheatBossRoom", KS_DOWN, this, &CPlayer::CheatBossRoom);
	CInput::GetInst()->SetCallback<CPlayer>("CheatNoDamage", KS_DOWN, this, &CPlayer::CheatNoDamage);
	CInput::GetInst()->SetCallback<CPlayer>("CheatDamageUp", KS_DOWN, this, &CPlayer::CheatDamageUp);
	CInput::GetInst()->SetCallback<CPlayer>("CheatPlayerDie", KS_DOWN, this, &CPlayer::CheatPlayerDie);
}