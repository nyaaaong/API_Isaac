
#include "Player.h"
#include "../Input.h"

void CPlayer::AddCallback()
{
	CInput::GetInst()->SetCallback<CPlayer>("MoveUp", KS_PUSH, this, &CPlayer::MoveUp);
	CInput::GetInst()->SetCallback<CPlayer>("MoveDown", KS_PUSH, this, &CPlayer::MoveDown);
	CInput::GetInst()->SetCallback<CPlayer>("MoveLeft", KS_PUSH, this, &CPlayer::MoveLeft);
	CInput::GetInst()->SetCallback<CPlayer>("MoveRight", KS_PUSH, this, &CPlayer::MoveRight);

	CInput::GetInst()->SetCallback<CPlayer>("FireUp", KS_PUSH, this, &CPlayer::FireUp);
	CInput::GetInst()->SetCallback<CPlayer>("FireLeft", KS_PUSH, this, &CPlayer::FireLeft);
	CInput::GetInst()->SetCallback<CPlayer>("FireDown", KS_PUSH, this, &CPlayer::FireDown);
	CInput::GetInst()->SetCallback<CPlayer>("FireRight", KS_PUSH, this, &CPlayer::FireRight);

	CInput::GetInst()->SetCallback<CPlayer>("Bomb", KS_DOWN, this, &CPlayer::Bomb);
}