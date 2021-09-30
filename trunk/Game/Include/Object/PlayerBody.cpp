
#include "PlayerBody.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../GameManager.h"

bool CPlayerBody::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::PlayerBody);
	SetPivot(0.5f, 0.5f);
	SetOffset(0.f, PLAYER_BODY_OFFSET_Y);

	CreateAnimation();

	AddAnimation("BodyIdleDown", false);

	AddAnimation("BodyMoveDown");
	AddAnimation("BodyMoveUp");
	AddAnimation("BodyMoveLeft");
	AddAnimation("BodyMoveRight");

	return true;
}

void CPlayerBody::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;

	m_tVelocity += tCurMove;
	m_pPlayer->m_tVelocity = tCurMove;

	m_tPrevPos = m_tPos;
	m_pPlayer->m_tPrevPos = m_tPos;

	m_tPos += tCurMove;
	m_pPlayer->m_tPos += tCurMove;

	if (bUseActivity)
	{
		Vector2	tActivityLT = m_pScene->GetActivityLT();
		Vector2	tActivityRB = m_pScene->GetActivityRB();

		if (m_tPos.x - m_tSize.x * m_tPivot.x + m_tOffset.x < tActivityLT.x)
		{
			m_tPos.x = tActivityLT.x + m_tSize.x * m_tPivot.x - m_tOffset.x;
			m_pPlayer->m_tPos.x = m_tPos.x;
		}

		else if (m_tPos.y - m_tSize.y * m_tPivot.y + m_tOffset.y < tActivityLT.y)
		{
			m_tPos.y = tActivityLT.y + m_tSize.y * m_tPivot.y - m_tOffset.y;
			m_pPlayer->m_tPos.y = m_tPos.y;
		}

		else if (m_tPos.x + m_tSize.x * m_tPivot.x + m_tOffset.x > tActivityRB.x)
		{
			m_tPos.x = tActivityRB.x - m_tSize.x * m_tPivot.x - m_tOffset.x;
			m_pPlayer->m_tPos.x = m_tPos.x;
		}

		else if (m_tPos.y + m_tSize.y * m_tPivot.y + m_tOffset.y > tActivityRB.y)
		{
			m_tPos.y = tActivityRB.y - m_tSize.y * m_tPivot.y - m_tOffset.y;
			m_pPlayer->m_tPos.y = m_tPos.y;
		}
	}
}

void CPlayerBody::Start()
{
	CObj::Start();
}

void CPlayerBody::Update(float fTime)
{
	CObj::Update(fTime);
}

void CPlayerBody::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CPlayerBody::Collision(float fTime)
{
	if (m_bInvisible)
		return;

	CObj::Collision(fTime);
}

void CPlayerBody::Render(HDC hDC)
{
	if (m_bInvisible)
		return;

	CObj::Render(hDC);
}

CPlayerBody* CPlayerBody::Clone()
{
	return nullptr;
}

CPlayerBody::CPlayerBody()	:
	m_pPlayer(nullptr)
{
}

CPlayerBody::CPlayerBody(const CPlayerBody& obj)	:
	CObj(obj),
	m_pPlayer(nullptr)
{
}

CPlayerBody::~CPlayerBody()
{
}
