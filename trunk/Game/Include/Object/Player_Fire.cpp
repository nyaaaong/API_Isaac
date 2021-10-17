
#include "Player.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "Tear.h"
#include "../Scene/SceneResource.h"

void CPlayer::FireUp(float fTime)
{
	m_bIsFire = true;

	SetBulletStartDir(Vector2::UP);
	SetOffset(0.f, 3.f);

	ChangeDirAnimation("HeadFire");
}

void CPlayer::FireLeft(float fTime)
{
	m_bIsFire = true;

	SetBulletStartDir(Vector2::LEFT);
	SetOffset(0.f, 3.f);

	ChangeDirAnimation("HeadFire");
}

void CPlayer::FireDown(float fTime)
{
	m_bIsFire = true;

	SetBulletStartDir(Vector2::DOWN);
	SetOffset(0.f, 3.f);

	ChangeDirAnimation("HeadFire");
}

void CPlayer::FireRight(float fTime)
{
	m_bIsFire = true;

	SetBulletStartDir(Vector2::RIGHT);
	SetOffset(0.f, 3.f);

	ChangeDirAnimation("HeadFire");
}

void CPlayer::FireEnd()
{
	m_bIsFire = false;

	DefaultAnimation();

	ChangeDirAnimation("HeadIdle");
}

void CPlayer::SetFireStart()
{
	CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("PlayerTear", "PlayerTear", m_tPos + m_tBulletStartDir * 50.f, Vector2(80.f, 80.f));
	pTear->SetDir(m_tBulletStartDir);
	pTear->SetMoveSpeed(m_tInfo.fShotSpeed);
	pTear->SetOwner(this);

	m_pScene->GetSceneResource()->SoundPlay("Tear");
}

