
#include "Door.h"

void CDoor::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CDoor::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

void CDoor::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CObj::CollisionBegin(pSrc, pDest, fTime);
}

void CDoor::Start()
{
	CObj::Start();
}

bool CDoor::Init()
{
	if (CObj::Init())
		return false;

	return true;
}

void CDoor::Update(float fTime)
{
	CObj::Update(fTime);
}

void CDoor::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CDoor::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CDoor::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CDoor* CDoor::Clone()
{
	return nullptr;
}

CDoor::CDoor()	:
	m_pNextRoom(nullptr)
{
}

CDoor::CDoor(const CDoor& obj)	:
	CObj(obj),
	m_pNextRoom(nullptr)
{
}

CDoor::~CDoor()
{
}
