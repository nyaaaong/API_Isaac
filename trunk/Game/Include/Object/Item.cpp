#include "Item.h"

void CItem::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CObj::CollisionBegin(pSrc, pDest, fTime);
}

void CItem::Start()
{
	CObj::Start();
}

bool CItem::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Item);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CItem::Update(float fTime)
{
	CObj::Update(fTime);
}

void CItem::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CItem::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CItem::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CItem* CItem::Clone()
{
	return nullptr;
}

CItem::CItem()	:
	m_pPlayer(nullptr),
	m_fValue(0.f)
{
}

CItem::CItem(const CItem& obj) :
	CObj(obj)
{
	m_pPlayer = obj.m_pPlayer;
	m_fValue = obj.m_fValue;
}

CItem::~CItem()
{
}
