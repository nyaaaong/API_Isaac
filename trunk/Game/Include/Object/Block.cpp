
#include "Block.h"
#include "../Collision/ColliderBox.h"

void CBlock::Start()
{
	CObj::Start();
}

bool CBlock::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::RoomObject);

	m_pColliderBox = AddCollider<CColliderBox>("MapObject");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetOffset(m_tSize * 0.5f);
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
	m_eType(MT_NONE)
{
}

CBlock::CBlock(const CBlock& obj) :
	CObj(obj)
{
	m_eType = obj.m_eType;
}

CBlock::~CBlock()
{
}

void CBlock::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CObj::CollisionBegin(pSrc, pDest, fTime);

	switch (m_eType)
	{
	case MT_ROCK:
		break;
	case MT_IRON:
		break;
	case MT_SPIKE:
		if (pDest->GetName() == "PlayerHead" || pDest->GetName() == "PlayerBody")
		{
			pDest->GetOwner()->SetDamage(1.f);
		}
		break;
	case MT_POOP:
		break;
	}
}
