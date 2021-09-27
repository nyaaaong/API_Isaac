#include "BackGround.h"

bool CBackGround::Init()
{
	if (!CObj::Init())
		return false;

	SetTexture("BackGround", TEXT("Room/Room.bmp"));
	SetZOrder(EZOrder::BackGround);

	return true;
}

void CBackGround::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CBackGround::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

void CBackGround::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CBackGround::Start()
{
	CObj::Start();
}

void CBackGround::Update(float fTime)
{
	CObj::Update(fTime);
}

void CBackGround::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CBackGround::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CBackGround::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CBackGround* CBackGround::Clone()
{
	return new CBackGround(*this);
}

CBackGround::CBackGround()
{
	m_eObjectType = EObjectType::BackGround;
}

CBackGround::CBackGround(const CBackGround& obj)
{
}

CBackGround::~CBackGround()
{
}
