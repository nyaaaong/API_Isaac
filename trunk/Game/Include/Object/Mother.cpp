
#include "Mother.h"

CMother::CMother()	:
	m_fPatternTimer(0.f)
{
}

CMother::CMother(const CMother& obj)	:
	CMonsterBase(obj)
{
	m_fPatternTimer = obj.m_fPatternTimer;
}

CMother::~CMother()
{
}

void CMother::Start()
{
}

bool CMother::Init()
{
	return true;
}

void CMother::Update(float fTime)
{
}

void CMother::PostUpdate(float fTime)
{
}

CMother* CMother::Clone()
{
	return nullptr;
}

void CMother::AddMotherAnimation()
{
}

void CMother::DetectPlayer(float fTime)
{
}

void CMother::MotherPattern(float fTime)
{
}

void CMother::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
}

void CMother::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
}
