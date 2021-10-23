
#include "ItemRock.h"
#include "Player.h"
#include "ItemGlasses.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CItemRock::CItemRock()	:
	m_pItemGlasses(nullptr),
	m_bHasItem(true)
{
}

CItemRock::CItemRock(const CItemRock& obj)	:
	CObj(obj)
{
	m_pItemGlasses = obj.m_pItemGlasses;
	m_bHasItem = obj.m_bHasItem;
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
	m_pColliderBox->SetCollisionBeginFunc<CItemRock>(this, &CItemRock::CollisionBegin);
	m_pColliderBox->SetCollisionCollidingFunc<CItemRock>(this, &CItemRock::CollisionColliding);
}

void CItemRock::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (!m_bHasItem)
		return;

	if (pDest->GetName() == "PlayerBody")
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pScene->GetPlayer());

		pPlayer->AddItem();
		m_pItemGlasses->Destroy();
		m_bHasItem = false;
	}
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
