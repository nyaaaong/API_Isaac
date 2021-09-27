#include "Item.h"

void CItem::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CItem::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

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
	if (CObj::Init())
		return false;

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

CItem::CItem()
{
}

CItem::CItem(const CItem& obj) :
	CObj(obj)
{
}

CItem::~CItem()
{
}
