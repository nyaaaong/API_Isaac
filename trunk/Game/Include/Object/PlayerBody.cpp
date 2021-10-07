
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

	m_pColliderBox = AddCollider<CColliderBox>("PlayerBody");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetOffset(0.f, PLAYER_BODY_OFFSET_Y);
	m_pColliderBox->SetCollisionProfile("PlayerBody");

	return true;
}

void CPlayerBody::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;

	m_tVelocity += tCurMove;
	m_pPlayer->m_tVelocity = tCurMove;

	m_tPrevPos = m_tPos;
	m_pPlayer->m_tPrevPos = m_tPos;

	m_tPos += tCurMove;
	m_pPlayer->m_tPos += tCurMove;

	if (bUseField)
	{
		Vector2	tFieldLT = m_pScene->GetFieldLT();
		Vector2	tFieldRB = m_pScene->GetFieldRB();

		if (m_tPos.x - m_tSize.x * m_tPivot.x + m_tOffset.x < tFieldLT.x)
		{
			m_tPos.x = tFieldLT.x + m_tSize.x * m_tPivot.x - m_tOffset.x;
			m_pPlayer->m_tPos.x = m_tPos.x;
		}

		else if (m_tPos.y - m_tSize.y * m_tPivot.y + m_tOffset.y < tFieldLT.y)
		{
			m_tPos.y = tFieldLT.y + m_tSize.y * m_tPivot.y - m_tOffset.y;
			m_pPlayer->m_tPos.y = m_tPos.y;
		}

		else if (m_tPos.x + m_tSize.x * m_tPivot.x + m_tOffset.x > tFieldRB.x)
		{
			m_tPos.x = tFieldRB.x - m_tSize.x * m_tPivot.x - m_tOffset.x;
			m_pPlayer->m_tPos.x = m_tPos.x;
		}

		else if (m_tPos.y + m_tSize.y * m_tPivot.y + m_tOffset.y > tFieldRB.y)
		{
			m_tPos.y = tFieldRB.y - m_tSize.y * m_tPivot.y - m_tOffset.y;
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
