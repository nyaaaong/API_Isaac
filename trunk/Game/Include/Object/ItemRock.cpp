
#include "ItemRock.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CItemRock::CItemRock()
{
}

CItemRock::CItemRock(const CItemRock& obj)	:
	CObj(obj)
{
}

CItemRock::~CItemRock()
{
}

bool CItemRock::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::RoomObject);

	SetTexture("ItemRock", TEXT("Room/Object/Item/Item_Rock.bmp"));
	SetTextureColorKey();

	return true;
}

void CItemRock::Start()
{
	CObj::Start();

	m_pColliderBox = AddCollider<CColliderBox>("ItemRock");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionProfile("Object");
	m_pColliderBox->SetCollisionCollidingFunc<CItemRock>(this, &CItemRock::CollisionColliding);
}

void CItemRock::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CItemRock::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (pDest->GetName() == "PlayerBody")
	{
		CObj* pPlayer = dynamic_cast<CObj*>(pDest->GetOwner());

		if (pPlayer)
		{
			Vector2	tDestVelocity = pPlayer->GetVelocity();
			pPlayer->Move(tDestVelocity * -100.f, true);
		}
	}
}
