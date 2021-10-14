
#include "Block.h"
#include "../Map/RoomObj.h"
#include "../Map/MapManager.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

void CBlock::Start()
{
	CObj::Start();

	m_fLife = m_pRoomObj->m_fLife;

	m_pColliderBox->SetCollisionBeginFunc<CBlock>(this, &CBlock::CollisionBegin);
	m_pColliderBox->SetCollisionCollidingFunc<CBlock>(this, &CBlock::CollisionColliding);
}

bool CBlock::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetPos(m_tPos + m_tSize * m_tPivot);

	CMapManager::GetInst()->SetBlockSize(m_tSize);
	CMapManager::GetInst()->SetBlockPivot(m_tPivot);

	SetZOrder(EZOrder::RoomObject);

	m_pColliderBox = AddCollider<CColliderBox>("MapObject");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionProfile("Object");

	return true;
}

void CBlock::Update(float fTime)
{
	CObj::Update(fTime);

	if (m_fLife != m_fPrevLife)
	{
		m_fPrevLife = m_fLife;

		if (m_eType == MT_ROCK)
			m_fLife = 0.f;
		
		if (m_pRoomObj)
			m_pRoomObj->m_fLife = m_fLife;

		if (m_fLife <= 0.f)
			Destroy();
	}
}

CBlock::CBlock()	:
	m_eType(MT_NONE),
	m_fPrevLife(4.f),
	m_fLife(4.f),
	m_fLifeMax(4.f),
	m_pRoomObj(nullptr)
{
}

CBlock::CBlock(const CBlock& obj) :
	CObj(obj)
{
	m_eType = obj.m_eType;
	m_fPrevLife = obj.m_fPrevLife;
	m_fLife = obj.m_fLife;
	m_fLifeMax = obj.m_fLifeMax;
	m_pRoomObj = obj.m_pRoomObj;
}

CBlock::~CBlock()
{
}

void CBlock::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CBlock::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	float	fL = m_pColliderBox->GetInfo().fL;
	float	fT = m_pColliderBox->GetInfo().fT;
	float	fR = m_pColliderBox->GetInfo().fR;
	float	fB = m_pColliderBox->GetInfo().fB;

	std::string	strName = pDest->GetName();
	CObj* pDestObj = pDest->GetOwner();
	Vector2	tDestVelocity = pDestObj->GetVelocity();

	if (strName == "PlayerHead")
		return;

	switch (pDest->GetColliderType())
	{
	case ECollider_Type::Box:
	{
		float	fDestL = dynamic_cast<CColliderBox*>(pDest)->GetInfo().fL;
		float	fDestT = dynamic_cast<CColliderBox*>(pDest)->GetInfo().fT;
		float	fDestR = dynamic_cast<CColliderBox*>(pDest)->GetInfo().fR;
		float	fDestB = dynamic_cast<CColliderBox*>(pDest)->GetInfo().fB;

		float	tMove = 0.f;

		if (m_eType == MT_SPIKE)
		{
			if (strName == "PlayerBody")
				pDestObj->SetDamage(1.f);
		}

		else if (m_eType == MT_ROCK || m_eType == MT_IRON || m_eType == MT_POOP)
		{
			bool	bCheckLeft = tDestVelocity.x < 0.f && tDestVelocity.x >= -1.f;
			bool	bCheckRight = tDestVelocity.x <= 1.f && tDestVelocity.x > 0.f;
			bool	bCheckTop = tDestVelocity.y < 0.f && tDestVelocity.y >= -1.f;
			bool	bCheckBottom = tDestVelocity.y <= 1.f && tDestVelocity.y > 0.f;

			// Pos 더할게 아니라 Velocity에 더해줘서 Move와 호환되도록 한다.
			if (bCheckRight)
			{
				if (bCheckBottom)
				{
					if (fT <= fDestB)
					{
						tMove = fDestB - fT + 0.1f;
						pDestObj->AddPos(0.f, -tMove * fTime);
					}
				}

				else if (bCheckTop)
				{
					if (fDestT <= fB)
					{
						tMove = fB - fDestT + 0.1f;
						pDestObj->AddPos(0.f, tMove);
					}
				}

				if (fL <= fDestR)
				{
					tMove = fDestR - fL + 0.1f;
					pDestObj->AddPos(-tMove, 0.f);
				}
			}

			if (bCheckLeft)
			{
				if (bCheckBottom)
				{
					if (fT <= fDestB)
					{
						tMove = fDestB - fT + 0.1f;
						pDestObj->AddPos(0.f, -tMove * fTime);
					}
				}

				else if (bCheckTop)
				{
					if (fDestT <= fB)
					{
						tMove = fB - fDestT + 0.1f;
						pDestObj->AddPos(0.f, tMove);
					}
				}

				if (fDestL <= fR)
				{
					tMove = fR - fDestL + 0.1f;
					pDestObj->AddPos(tMove, 0.f);
				}
			}

			if (bCheckBottom)
			{
				if (bCheckRight)
				{
					if (fL <= fDestR)
					{
						tMove = fDestR - fL + 0.1f;
						pDestObj->AddPos(-tMove * fTime, 0.f);
					}
				}

				else if (bCheckLeft)
				{
					if (fDestL <= fR)
					{
						tMove = fR - fDestL + 0.1f;
						pDestObj->AddPos(tMove, 0.f);
					}
				}

				if (fT <= fDestB)
				{
					tMove = fDestB - fT + 0.1f;
					pDestObj->AddPos(0.f, -tMove);
				}
			}

			if (bCheckTop)
			{
				if (bCheckRight)
				{
					if (fL <= fDestR)
					{
						tMove = fDestR - fL + 0.1f;
						pDestObj->AddPos(-tMove, 0.f);
					}
				}

				else if (bCheckLeft)
				{
					if (fDestL <= fR)
					{
						tMove = fR - fDestL + 0.1f;
						pDestObj->AddPos(tMove, 0.f);
					}
				}

				if (fDestT <= fB)
				{
					tMove = fB - fDestT + 0.1f;
					pDestObj->AddPos(0.f, tMove* fTime);
				}
			}
		}
	}
		break;
	case ECollider_Type::Sphere:
		break;
	}
}

float CBlock::SetDamage(float fDamage)
{
	fDamage = CObj::SetDamage(fDamage);

	m_fLife -= fDamage;

	if (m_fLife < 0.f)
		m_fLife = 0.f;

	return fDamage;
}
