
#include "Player.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "Tear.h"
#include "../Scene/SceneResource.h"

void CPlayer::FireUp(float fTime)
{
	if (m_bDie || m_bIsItemAnim)
		return;

	m_bIsFire = true;

	SetBulletStartDir(Vector2::UP);
	SetOffset(0.f, 3.f);

	if (m_bIsItem)
		ChangeDirAnimation("HeadItemFire");

	else
		ChangeDirAnimation("HeadFire");
}

void CPlayer::FireLeft(float fTime)
{
	if (m_bDie || m_bIsItemAnim)
		return;

	m_bIsFire = true;

	SetBulletStartDir(Vector2::LEFT);
	SetOffset(0.f, 3.f);

	if (m_bIsItem)
		ChangeDirAnimation("HeadItemFire");

	else
		ChangeDirAnimation("HeadFire");
}

void CPlayer::FireDown(float fTime)
{
	if (m_bDie || m_bIsItemAnim)
		return;

	m_bIsFire = true;

	SetBulletStartDir(Vector2::DOWN);
	SetOffset(0.f, 3.f);

	if (m_bIsItem)
		ChangeDirAnimation("HeadItemFire");

	else
		ChangeDirAnimation("HeadFire");
}

void CPlayer::FireRight(float fTime)
{
	if (m_bDie || m_bIsItemAnim)
		return;

	m_bIsFire = true;

	SetBulletStartDir(Vector2::RIGHT);
	SetOffset(0.f, 3.f);

	if (m_bIsItem)
		ChangeDirAnimation("HeadItemFire");

	else
		ChangeDirAnimation("HeadFire");
}

void CPlayer::FireEnd()
{
	if (m_bDie || m_bIsItemAnim)
		return;

	m_bIsFire = false;

	DefaultAnimation();

	ChangeDirAnimation("HeadIdle");
}

void CPlayer::ItemFireEnd()
{
	if (m_bDie || m_bIsItemAnim)
		return;

	m_bIsFire = false;

	DefaultAnimation();

	ChangeDirAnimation("HeadItemIdle");
}

void CPlayer::SetFireStart()
{
	if (m_bDie || m_bIsItemAnim)
		return;

	CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("PlayerTear", "PlayerTear", m_tPos + m_tBulletStartDir * 50.f, Vector2(80.f, 80.f));
	pTear->SetDir(m_tBulletStartDir);
	pTear->SetMoveSpeed(m_tInfo.fShotSpeed);
	pTear->SetOwner(this);

	m_pScene->GetSceneResource()->SoundPlay("Tear");
}

void CPlayer::SetItemFireStart()
{
	if (m_bDie || m_bIsItemAnim)
		return;

	CSharedPtr<CTear>	pTearL = m_pScene->CreateObject<CTear>("PlayerTear", "PlayerTear", m_tPos + m_tBulletStartDir * 50.f, Vector2(80.f, 80.f));
	pTearL->SetDir(m_tBulletStartDir);
	pTearL->SetMoveSpeed(m_tInfo.fShotSpeed);
	pTearL->SetOwner(this);

	CSharedPtr<CTear>	pTearR = m_pScene->CreateObject<CTear>("PlayerTear", "PlayerTear", m_tPos + m_tBulletStartDir * 50.f, Vector2(80.f, 80.f));
	pTearR->SetDir(m_tBulletStartDir);
	pTearR->SetMoveSpeed(m_tInfo.fShotSpeed);
	pTearR->SetOwner(this);

	if (m_tBulletStartDir == Vector2::DOWN)
	{
		Vector2	tLPos = pTearL->GetPos();
		Vector2	tRPos = pTearR->GetPos();

		pTearL->SetPos(tLPos.x - 20.f, tLPos.y);
		pTearR->SetPos(tRPos.x + 20.f, tRPos.y);
	}

	else if (m_tBulletStartDir == Vector2::UP)
	{
		Vector2	tLPos = pTearL->GetPos();
		Vector2	tRPos = pTearR->GetPos();

		pTearL->SetPos(tLPos.x - 20.f, tLPos.y);
		pTearR->SetPos(tRPos.x + 20.f, tRPos.y);
	}

	else if (m_tBulletStartDir == Vector2::LEFT)
	{
		Vector2	tLPos = pTearL->GetPos();
		Vector2	tRPos = pTearR->GetPos();

		pTearL->SetPos(tLPos.x, tLPos.y + 20.f);
		pTearR->SetPos(tRPos.x, tRPos.y - 20.f);
	}

	else if (m_tBulletStartDir == Vector2::RIGHT)
	{
		Vector2	tLPos = pTearL->GetPos();
		Vector2	tRPos = pTearR->GetPos();

		pTearL->SetPos(tLPos.x, tLPos.y - 20.f);
		pTearR->SetPos(tRPos.x, tRPos.y + 20.f);
	}

	m_pScene->GetSceneResource()->SoundPlay("Tear");
}

