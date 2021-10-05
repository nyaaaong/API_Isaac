
#include "Player.h"
#include "PlayerBody.h"

void CPlayer::Move(const Vector2& tDir, bool bUseActivity)
{
	m_pPlayerBody->Move(tDir, m_eInfo.fMoveSpeed, bUseActivity);
}

void CPlayer::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	m_pPlayerBody->Move(tDir, fSpeed, bUseActivity);
}

void CPlayer::MoveUp(float fTime)
{
	m_bIsMove = true;
	m_bMoveUp = true;

	Move(Vector2::UP, m_eInfo.fMoveSpeed, true);

	if (!m_bIsFire)
	{
		SetBulletStartDir(Vector2::UP);
		ChangeDirAnimation("HeadIdle");
	}

	m_pPlayerBody->ChangeAnimation("BodyMoveUp");
	m_pPlayerBody->SetOffset(0.f, PLAYER_BODY_OFFSET_Y);
}

void CPlayer::MoveDown(float fTime)
{
	m_bIsMove = true;
	m_bMoveDown = true;

	Move(Vector2::DOWN, m_eInfo.fMoveSpeed, true);

	if (!m_bIsFire)
	{
		SetBulletStartDir(Vector2::DOWN);
		ChangeDirAnimation("HeadIdle");
	}

	m_pPlayerBody->ChangeAnimation("BodyMoveDown");
	m_pPlayerBody->SetOffset(0.f, PLAYER_BODY_OFFSET_Y);
}

void CPlayer::MoveLeft(float fTime)
{
	m_bIsMove = true;

	Move(Vector2::LEFT, m_eInfo.fMoveSpeed, true);

	if (!m_bIsFire)
	{
		SetBulletStartDir(Vector2::LEFT);

		if (!CheckMoveUpDown())
			ChangeDirAnimation("HeadIdle");
	}

	if (!CheckMoveUpDown())
	{
		m_pPlayerBody->ChangeAnimation("BodyMoveLeft");
		m_pPlayerBody->SetOffset(5.f, PLAYER_BODY_OFFSET_Y);
	}
}

void CPlayer::MoveRight(float fTime)
{
	m_bIsMove = true;

	Move(Vector2::RIGHT, m_eInfo.fMoveSpeed, true);

	if (!m_bIsFire)
	{
		SetBulletStartDir(Vector2::RIGHT);

		if (!CheckMoveUpDown())
			ChangeDirAnimation("HeadIdle");
	}

	if (!CheckMoveUpDown())
	{
		m_pPlayerBody->ChangeAnimation("BodyMoveRight");
		m_pPlayerBody->SetOffset(-5.f, PLAYER_BODY_OFFSET_Y);
	}
}

bool CPlayer::CheckMoveUpDown()
{
	if (m_bMoveDown || m_bMoveUp)
		return true;

	return false;
}

void CPlayer::UpdateMoveUpDown()
{
	if (m_bMoveDown)
	{
		if (m_tPos.y == m_tPrevPos.y && !m_bIsMove)
			m_bMoveDown = false;
	}

	if (m_bMoveUp)
	{
		if (m_tPos.y == m_tPrevPos.y && !m_bIsMove)
			m_bMoveUp = false;
	}
}