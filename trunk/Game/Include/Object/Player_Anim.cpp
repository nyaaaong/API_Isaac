
#include "Player.h"
#include "PlayerBody.h"

void CPlayer::AddPlayerAnimation()
{
	AddAnimation("HeadIdleDown", false);
	AddAnimation("HeadIdleUp", false);
	AddAnimation("HeadIdleLeft", false);
	AddAnimation("HeadIdleRight", false);

	AddAnimation("HeadFireDown", false, m_tInfo.fTearSpeed);
	AddAnimation("HeadFireUp", false, m_tInfo.fTearSpeed);
	AddAnimation("HeadFireLeft", false, m_tInfo.fTearSpeed);
	AddAnimation("HeadFireRight", false, m_tInfo.fTearSpeed);

	AddAnimation("IsaacDeath", false, 1.f);

	AddAnimationNotify("HeadFireUp", 2, this, &CPlayer::SetFireStart);
	AddAnimationNotify("HeadFireLeft", 2, this, &CPlayer::SetFireStart);
	AddAnimationNotify("HeadFireDown", 2, this, &CPlayer::SetFireStart);
	AddAnimationNotify("HeadFireRight", 2, this, &CPlayer::SetFireStart);

	SetAnimationEndNotify<CPlayer>("HeadFireUp", this, &CPlayer::FireEnd);
	SetAnimationEndNotify<CPlayer>("HeadFireLeft", this, &CPlayer::FireEnd);
	SetAnimationEndNotify<CPlayer>("HeadFireDown", this, &CPlayer::FireEnd);
	SetAnimationEndNotify<CPlayer>("HeadFireRight", this, &CPlayer::FireEnd);

	SetAnimationEndNotify<CPlayer>("IsaacDeath", this, &CPlayer::IsaacDeathEnd);
}

void CPlayer::ChangeDirAnimation(const std::string& strAnimType)
{
	Vector2	tDir = GetBulletStartDir();

	if (tDir == Vector2::UP)
		ChangeAnimation(strAnimType + std::string("Up"));

	else if (tDir == Vector2::LEFT)
		ChangeAnimation(strAnimType + std::string("Left"));

	else if (tDir == Vector2::DOWN)
		ChangeAnimation(strAnimType + std::string("Down"));

	else if (tDir == Vector2::RIGHT)
		ChangeAnimation(strAnimType + std::string("Right"));
}

void CPlayer::DefaultAnimation()
{
	if (m_bDie)
		return;

	m_bIsMove = false;
	m_bMoveDown = false;
	m_bMoveUp = false;

	SetBulletStartDir(Vector2::DOWN);

	ChangeAnimation("HeadIdleDown");
	SetOffset(0.f, 0.f);

	m_pPlayerBody->ChangeAnimation("BodyIdleDown");
	m_pPlayerBody->SetOffset(0.f, PLAYER_BODY_OFFSET_Y);
}