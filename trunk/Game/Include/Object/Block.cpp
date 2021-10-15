
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
			bool	bCheckCross = tDestVelocity.x != 0.f && tDestVelocity.y != 0.f;

			float	fInterX = 0.f;
			float	fInterY = 0.f;

			if (bCheckCross)
			{
				if (bCheckLeft)
				{
					fInterX = abs(fR - fDestL);

					if (bCheckTop)
					{
						fInterY = abs(fB - fDestT);
					}

					else if (bCheckBottom)
					{
						fInterY = abs(fDestB - fT);
					}
				}

				else if (bCheckRight)
				{
					fInterX = abs(fDestR - fL);

					if (bCheckTop)
					{
						fInterY = abs(fB - fDestT);
					}

					else if (bCheckBottom)
					{
						fInterY = abs(fDestB - fT);
					}
				}

				tDestVelocity.Normalize();

				if (fInterX > fInterY)
				{
					tDestVelocity.y *= -1.f;

					pDestObj->AddPos(0.f, tDestVelocity.y * fInterY);
				}

				else
				{
					tDestVelocity.x *= -1.f;

					pDestObj->AddPos(tDestVelocity.x * fInterX, 0.f);
				}
			}

			else if (bCheckLeft)
			{
				tDestVelocity.x *= -1.f;

				pDestObj->AddPos(tDestVelocity);
			}

			else if (bCheckRight)
			{
				tDestVelocity.x *= -1.f;

				pDestObj->AddPos(tDestVelocity);
			}

			else if (bCheckTop)
			{
				tDestVelocity.y *= -1.f;

				pDestObj->AddPos(tDestVelocity);
			}

			else if (bCheckBottom)
			{
				tDestVelocity.y *= -1.f;

				pDestObj->AddPos(tDestVelocity);
			}

			// 자신이 벽 안으로 들어간 경우
			if (fL <= fDestL && fR >= fDestR && fT <= fDestT && fB >= fDestB)
			{
				float fInterL = abs(fDestL - fL);
				float fInterR = abs(fR - fDestR);
				float fInterT = abs(fDestT - fT);
				float fInterB = abs(fB - fDestB);
				float fResult = 0.f;

				fResult = fInterL <= fInterR ? fInterL : fInterR;
				fResult = fResult <= fInterT ? fResult : fInterT;
				fResult = fResult <= fInterB ? fResult : fInterB;

				if (fResult == fInterL)
					pDestObj->AddPos(-fResult, 0.f);

				else if (fResult == fInterR)
					pDestObj->AddPos(fResult, 0.f);

				else if (fResult == fInterT)
					pDestObj->AddPos(0.f, -fResult);

				else if (fResult == fInterB)
					pDestObj->AddPos(0.f, fResult);
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
