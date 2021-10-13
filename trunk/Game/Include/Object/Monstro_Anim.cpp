
#include "BossMonstro.h"
#include "../Scene/Scene.h"

void CBossMonstro::AddBossAnimation()
{
	AddAnimation("MonstroIdleLeft");
	AddAnimation("MonstroIdleRight");
	AddAnimation("MonstroMoveLeft", false);
	AddAnimation("MonstroMoveRight", false);
	AddAnimation("MonstroJumpLeft", false);
	AddAnimation("MonstroJumpRight", false);
	AddAnimation("MonstroFireLeft", false);
	AddAnimation("MonstroFireRight", false);

	AddBossNotify();
}

void CBossMonstro::AddBossNotify()
{
	AddAnimationNotify<CBossMonstro>("MonstroMoveLeft", 1, this, &CBossMonstro::PatternMoveNotify);
	AddAnimationNotify<CBossMonstro>("MonstroMoveLeft", 2, this, &CBossMonstro::PatternMoveNotify);
	AddAnimationNotify<CBossMonstro>("MonstroMoveLeft", 3, this, &CBossMonstro::PatternMoveNotify);

	AddAnimationNotify<CBossMonstro>("MonstroMoveRight", 1, this, &CBossMonstro::PatternMoveNotify);
	AddAnimationNotify<CBossMonstro>("MonstroMoveRight", 2, this, &CBossMonstro::PatternMoveNotify);
	AddAnimationNotify<CBossMonstro>("MonstroMoveRight", 3, this, &CBossMonstro::PatternMoveNotify);

	AddAnimationNotify<CBossMonstro>("MonstroJumpLeft", 1, this, &CBossMonstro::PatternJumpNotify);
	AddAnimationNotify<CBossMonstro>("MonstroJumpLeft", 1, this, &CBossMonstro::PatternMoveNotify);
	AddAnimationNotify<CBossMonstro>("MonstroJumpLeft", 2, this, &CBossMonstro::PatternMoveNotify);

	AddAnimationNotify<CBossMonstro>("MonstroJumpRight", 1, this, &CBossMonstro::PatternJumpNotify);
	AddAnimationNotify<CBossMonstro>("MonstroJumpRight", 1, this, &CBossMonstro::PatternMoveNotify);
	AddAnimationNotify<CBossMonstro>("MonstroJumpRight", 2, this, &CBossMonstro::PatternMoveNotify);

	SetAnimationEndNotify<CBossMonstro>("MonstroMoveLeft", this, &CBossMonstro::PatternDefault);
	SetAnimationEndNotify<CBossMonstro>("MonstroMoveRight", this, &CBossMonstro::PatternDefault);
	SetAnimationEndNotify<CBossMonstro>("MonstroJumpLeft", this, &CBossMonstro::PatternDefault);
	SetAnimationEndNotify<CBossMonstro>("MonstroJumpRight", this, &CBossMonstro::PatternDefault);
	SetAnimationEndNotify<CBossMonstro>("MonstroFireLeft", this, &CBossMonstro::PatternDefault);
	SetAnimationEndNotify<CBossMonstro>("MonstroFireRight", this, &CBossMonstro::PatternDefault);
}

void CBossMonstro::ChangeDirAnimation(const std::string& strAnimType)
{
	if (m_tDir == Vector2::LEFT)
		ChangeAnimation(strAnimType + std::string("Left"));

	else if (m_tDir == Vector2::RIGHT)
		ChangeAnimation(strAnimType + std::string("Right"));
}

void CBossMonstro::DirCheck()
{
	Vector2 tPlayerDir = m_pScene->GetPlayer()->GetPos() - GetPos();
	tPlayerDir.Normalize();

	if (tPlayerDir.x >= -1.f &&
		tPlayerDir.x < 0.f)
		m_tDir = Vector2::LEFT;

	else
		m_tDir = Vector2::RIGHT;
}
