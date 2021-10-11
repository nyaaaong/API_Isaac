#include "Character.h"
#include "../GameManager.h"

CCharacter::CCharacter()	:
	m_eInfo{},
	m_tBulletStartDir(Vector2::DOWN),
	m_fTearTimer(0.f)
{
}

CCharacter::CCharacter(const CCharacter& obj)	:
	CObj(obj),
	m_tBulletStartDir(Vector2::DOWN),
	m_fTearTimer(0.f)
{
	m_eInfo = obj.m_eInfo;
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetFireStart()
{
}

float CCharacter::SetDamage(float fDamage)
{
	fDamage = CObj::SetDamage(fDamage);

	m_eInfo.fHP -= fDamage;

	if (m_eInfo.fHP < 0.f)
		m_eInfo.fHP = 0.f;

    return fDamage;
}

void CCharacter::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CCharacter::Move(const Vector2& tDir, bool bUseField)
{
	CObj::Move(tDir, bUseField);
}

void CCharacter::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	CObj::Move(tDir, fSpeed, bUseField);
}

void CCharacter::Start()
{
	CObj::Start();
}

bool CCharacter::Init()
{
	if (!CObj::Init())
		return false;

	CreateAnimation();

	return true;
}

void CCharacter::Update(float fTime)
{
	CObj::Update(fTime);
}

void CCharacter::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CCharacter::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CCharacter::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CCharacter* CCharacter::Clone()
{
	return nullptr;
}
