
#include "Player.h"
#include "PlayerBody.h"
#include "../Input.h"
#include "../Scene/Scene.h"

void CPlayer::Move(const Vector2& tDir, bool bUseField)
{
	m_tMoveDir = tDir;

	if (m_pPlayerBody)
		m_pPlayerBody->Move(tDir, m_eInfo.fMoveSpeed, bUseField);
}

void CPlayer::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	m_tMoveDir = tDir;

	if (m_pPlayerBody)
		m_pPlayerBody->Move(tDir, fSpeed, bUseField);
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
	Vector2	tFieldLT = m_pScene->GetFieldLT();
	Vector2	tFieldRB = m_pScene->GetFieldRB();
	float	tBodyPosY = m_pPlayerBody->GetPos().y;
	float	tBodySizeY = m_pPlayerBody->GetSize().y;
	float	tBodyPivotY = m_pPlayerBody->GetPivot().y;
	float	tBodyOffsetY = m_pPlayerBody->GetOffset().y;

	float	fPlayerBodyUpY = tFieldLT.y + tBodySizeY * tBodyPivotY - tBodyOffsetY;
	float	fPlayerBodyDownY = tFieldRB.y - tBodySizeY * tBodyPivotY - tBodyOffsetY;

	if (m_bMoveDown)
	{
		if (!CInput::GetInst()->GetKeyPush("PlayerMoveDown"))
			m_bMoveDown = false;
	}

	if (m_bMoveUp)
	{
		if (!CInput::GetInst()->GetKeyPush("PlayerMoveUp"))
			m_bMoveUp = false;
	}
}