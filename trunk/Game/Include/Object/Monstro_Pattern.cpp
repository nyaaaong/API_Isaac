
#include "BossMonstro.h"
#include "../Scene/Scene.h"

void CBossMonstro::PatternMove(float fTime)
{
	GetM2PDir();

	ChangeDirAnimation("MonstroMove");
}

void CBossMonstro::PatternMoveNotify()
{
	m_bMove = true;
}

void CBossMonstro::PatternJump(float fTime)
{
	GetM2PDir();

	ChangeDirAnimation("MonstroJump");
}

void CBossMonstro::PatternJumpNotify()
{
	Jump(m_tM2PDir.y);
}

void CBossMonstro::PatternFire(float fTime)
{
	GetM2PDir();

	ChangeDirAnimation("MonstroFire");
}

void CBossMonstro::PatternDefault()
{
	m_bMove = false;

	ChangeDirAnimation("MonstroIdle");
}

void CBossMonstro::AddBossPattern()
{
	AddMonsterPattern<CBossMonstro>(this, &CBossMonstro::PatternMove);
	AddMonsterPattern<CBossMonstro>(this, &CBossMonstro::PatternJump);
	AddMonsterPattern<CBossMonstro>(this, &CBossMonstro::PatternFire);
}