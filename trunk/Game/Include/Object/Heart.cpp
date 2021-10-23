
#include "Heart.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CHeart::CHeart()	:
	m_eType(EHeart_Type::Half)
{
}

CHeart::CHeart(const CHeart& obj)	:
	CItem(obj)
{
	m_eType = obj.m_eType;
}

CHeart::~CHeart()
{
}

void CHeart::Start()
{
	CItem::Start();

	switch (m_eType)
	{
	case EHeart_Type::Half:
		SetTexture("HeartHalf");
		m_fValue = 1.f;
		break;
	case EHeart_Type::Normal:
		SetTexture("HeartNormal");
		m_fValue = 2.f;
		break;
	case EHeart_Type::Double:
		SetTexture("HeartDouble");
		m_fValue = 4.f;
		break;
	}

	m_pColliderBox = AddCollider<CColliderBox>("Heart");
	m_pColliderBox->SetExtent(m_tSize * 0.5f);
	m_pColliderBox->SetCollisionProfile("Item");
	m_pColliderBox->SetCollisionBeginFunc<CHeart>(this, &CHeart::CollisionBegin);
}

bool CHeart::Init()
{
	if (!CItem::Init())
		return false;

	SetZOrder(EZOrder::PickUpItem);

	SetTexture("HeartHalf", TEXT("Item/PickUp/Heart_1.bmp"));
	SetTextureColorKey();
	SetTexture("HeartNormal", TEXT("Item/PickUp/Heart_2.bmp"));
	SetTextureColorKey();
	SetTexture("HeartDouble", TEXT("Item/PickUp/Heart_3.bmp"));
	SetTextureColorKey();

	return true;
}

void CHeart::Update(float fTime)
{
	CItem::Update(fTime);
}

void CHeart::PostUpdate(float fTime)
{
	CItem::PostUpdate(fTime);
}

void CHeart::Collision(float fTime)
{
	CItem::Collision(fTime);
}

void CHeart::Render(HDC hDC)
{
	CItem::Render(hDC);
}

CHeart* CHeart::Clone()
{
	return new CHeart(*this);
}

void CHeart::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	if (!m_pPlayer)
		return;

	std::string	strName = pDest->GetName();
	float	fPlayerHP = m_pPlayer->GetHP();
	float	fPlayerHPMax = m_pPlayer->GetHPMax();

	if (strName == "PlayerBody")
	{
		if (fPlayerHP == fPlayerHPMax)
			return;

		else if (fPlayerHP < fPlayerHPMax)
		{
			m_pPlayer->AddHP(m_fValue);
			m_pScene->GetSceneResource()->SoundPlay("HeartAdd");
			Destroy();
		}
	}
}
