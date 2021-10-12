
#include "PlayerBody.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Map/MapManager.h"
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

void CPlayerBody::Start()
{
	CObj::Start();

	m_pPlayer = dynamic_cast<CPlayer*>(m_pScene->GetPlayer());
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


void CPlayerBody::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	m_tMoveDir = tDir;

	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	Vector2	tBlockSize = CMapManager::GetInst()->GetBlockSize();
	Vector2	tBlockPivot = CMapManager::GetInst()->GetBlockPivot();
	CRoomMap* pCurMap = m_pScene->GetCurrentMap();

	if (pCurMap)
	{
		if (pCurMap->IsObj(m_tPos.x - tBlockSize.x * tBlockPivot.x + tCurMove.x, m_tPos.y + tCurMove.y, MT_ROCK) ||
			pCurMap->IsObj(m_tPos.x - tBlockSize.x * tBlockPivot.x + tCurMove.x, m_tPos.y + tCurMove.y, MT_IRON) ||
			pCurMap->IsObj(m_tPos.x - tBlockSize.x * tBlockPivot.x + tCurMove.x, m_tPos.y + tCurMove.y, MT_POOP))
			return;
	}

	m_tVelocity += tCurMove;
	m_pPlayer->m_tVelocity = tCurMove;

	m_tPrevPos = m_tPos;
	m_pPlayer->m_tPrevPos = m_tPos;

	m_tPos += tCurMove;
	m_pPlayer->m_tPos += tCurMove;

	if (bUseField)
	{
		if (m_pScene->CheckFieldPos(this))
			m_pPlayer->m_tPos = m_tPos;
	}
}

float CPlayerBody::SetDamage(float fDamage)
{
	if (!m_bEnableDamage)
		return 0.f;

	return m_pPlayer->SetDamage(fDamage);
}
