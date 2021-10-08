
#include "Block.h"
#include "Character.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

void CBlock::Start()
{
	CObj::Start();

	m_pColliderBox->SetCollisionBeginFunc<CBlock>(this, &CBlock::CollisionBegin);
	m_pColliderBox->SetCollisionCollidingFunc<CBlock>(this, &CBlock::CollisionColliding);
}

bool CBlock::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetPos(m_tPos + m_tSize * m_tPivot);

	SetZOrder(EZOrder::RoomObject);

	m_pColliderBox = AddCollider<CColliderBox>("MapObject");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionProfile("Object");

	return true;
}

void CBlock::Update(float fTime)
{
	CObj::Update(fTime);
}

void CBlock::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CBlock::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CBlock::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CBlock::CBlock()	:
	m_eType(MT_NONE),
	m_fHP(4),
	m_fHPMax(4)
{
}

CBlock::CBlock(const CBlock& obj) :
	CObj(obj)
{
	m_eType = obj.m_eType;
	m_fHP = obj.m_fHP;
	m_fHPMax = obj.m_fHPMax;
}

CBlock::~CBlock()
{
}

void CBlock::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	switch (m_eType)
	{
	case MT_ROCK:
		break;
	case MT_IRON:
		break;
	case MT_SPIKE:
		if (pDest->GetName() == "PlayerHead" || pDest->GetName() == "PlayerBody")
			pDest->GetOwner()->SetDamage(1.f);
		break;
	case MT_POOP:
		break;
	}
}

void CBlock::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	const RectInfo& tSrcRC = dynamic_cast<CColliderBox*>(pSrc)->GetInfo();
	const RectInfo& tDestRC = dynamic_cast<CColliderBox*>(pDest)->GetInfo();

	Vector2	tDir = pDest->GetOwner()->GetPos() - pDest->GetOwner()->GetPrevPos();

	RectInfo	tResultRC;
	tResultRC.fL = tSrcRC.fR - tDestRC.fL;
	tResultRC.fR = tSrcRC.fL - tDestRC.fR;
	tResultRC.fT = tSrcRC.fB - tDestRC.fT;
	tResultRC.fB = tSrcRC.fT - tDestRC.fB;

	switch (m_eType)
	{
	case MT_ROCK:
	case MT_IRON:
	case MT_POOP:
		if (pDest->GetName() == "PlayerBody")
		{
			if (tSrcRC.fL < tDestRC.fR && tSrcRC.fR > tDestRC.fL &&
				tSrcRC.fT < tDestRC.fB && tSrcRC.fB > tDestRC.fT) // 충돌한 경우
			{
				if (tDir.x > 0.f) // 오른쪽으로 이동한 경우
					m_pScene->SetPlayerMoveX(tResultRC.fR);

				else if (tDir.x < 0.f) // 왼쪽으로 이동한 경우
					m_pScene->SetPlayerMoveX(tResultRC.fL);

				if (tDir.y > 0.f) // 아래쪽으로 이동한 경우
					m_pScene->SetPlayerMoveY(tResultRC.fB);
				
				else if (tDir.y < 0.f) // 윗쪽으로 이동한 경우
					m_pScene->SetPlayerMoveY(tResultRC.fT);
			}
		}
		break;
	}
}
