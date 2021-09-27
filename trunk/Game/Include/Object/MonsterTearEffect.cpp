
#include "MonsterTearEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

bool CMonsterTearEffect::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);

	CreateAnimation();
	AddAnimation("MonsterTearDrop", false, 0.3f);

	SetAnimationEndNotify<CMonsterTearEffect>("MonsterTearDrop", this, &CMonsterTearEffect::AnimationFinish);

	return true;
}

void CMonsterTearEffect::Start()
{
	CObj::Start();
}

void CMonsterTearEffect::AnimationFinish()
{
	Destroy();
}

void CMonsterTearEffect::Move(const Vector2& tDir, bool bUseActivity)
{
	CObj::Move(tDir, bUseActivity);
}

void CMonsterTearEffect::Move(const Vector2& tDir, float fSpeed, bool bUseActivity)
{
	CObj::Move(tDir, fSpeed, bUseActivity);
}

void CMonsterTearEffect::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CMonsterTearEffect::Update(float fTime)
{
	CObj::Update(fTime);
}

void CMonsterTearEffect::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CMonsterTearEffect::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CMonsterTearEffect::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CMonsterTearEffect* CMonsterTearEffect::Clone()
{
	return new CMonsterTearEffect(*this);
}

CMonsterTearEffect::CMonsterTearEffect()
{
	m_eObjectType = EObjectType::Effect;
}

CMonsterTearEffect::CMonsterTearEffect(const CMonsterTearEffect& obj)	:
	CObj(obj)
{
}

CMonsterTearEffect::~CMonsterTearEffect()
{
}
