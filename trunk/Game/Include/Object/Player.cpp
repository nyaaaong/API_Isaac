
#include "Player.h"
#include "PlayerBody.h"
#include "ObjManager.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"

bool CPlayer::Init()
{
	if (!CCharacter::Init())
		return false;

	SetZOrder(EZOrder::Player);
	SetPivot(0.5f, 0.5f);

	AddPlayerAnimation();

	m_pColliderSphere = AddCollider<CColliderSphere>("PlayerHead");
	m_pColliderSphere->SetRadius(40.f);
	m_pColliderSphere->SetCollisionProfile("PlayerHead");

	CObjManager::GetInst()->PullPlayerInfo(m_tInfo);

	return true;
}

void CPlayer::Start()
{
	CCharacter::Start();

	AddCallback();

	m_pPlayerBody = dynamic_cast<CPlayerBody*>(m_pScene->GetPlayerBody());
	m_pPlayerBody->Start();
	m_pPlayerBody->SetPos(m_tPos);

	m_pColliderSphere->SetCollisionBeginFunc<CPlayer>(this, &CPlayer::CollisionBegin);
}

void CPlayer::Update(float fTime)
{
	CCharacter::Update(fTime);

	NoDamageTime(fTime);

	UpdateMoveUpDown();
}

void CPlayer::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	if (!m_bIsFire &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveUp") &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveDown") &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveLeft") &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveRight"))
		DefaultAnimation();
}

void CPlayer::Collision(float fTime)
{
	if (m_bInvisible)
		return;

	CCharacter::Collision(fTime);
}

void CPlayer::Render(HDC hDC)
{
	if (m_bInvisible)
		return;

	CCharacter::Render(hDC);
}

float CPlayer::SetDamage(float fDamage)
{
	if (!m_bEnableDamage)
		return 0.f;

	m_bHit = true;

	fDamage = CCharacter::SetDamage(fDamage);

	NoDamageTime(CGameManager::GetInst()->GetDeltaTime());

	return fDamage;
}

void CPlayer::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	//if (pDest->GetProfile()->strName == "Monster")
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

CPlayer::CPlayer() :
	m_bIsFire(false),
	m_bIsMove(false),
	m_bUseBomb(false),
	m_bMoveUp(false),
	m_bMoveDown(false),
	m_fSkill1Time(0.f),
	m_pPlayerBody(nullptr),
	m_fNoDmgTimer(0.f),
	m_fNoDmgTimerMax(2.f),
	m_bHit(false),
	m_fBlinkTimer(0.f),
	m_fBlinkSpeed(0.2f)
{
	m_tInfo.fAttack = 3.f;
	m_tInfo.fHP = PLAYER_HP_MAX;
	m_tInfo.fHPMax = PLAYER_HP_MAX;
	m_tInfo.iBomb = 3;
	m_tInfo.iBombMax = 99;
	m_tInfo.fTearTimer = 0.5f;
	m_tInfo.fShotSpeed = 400.f;
	m_tInfo.fTearDistance = 500.f;
	m_tInfo.fMoveSpeed = 300.f;
}

CPlayer::CPlayer(const CPlayer& obj) :
	CCharacter(obj),
	m_bIsFire(false),
	m_bIsMove(false),
	m_bMoveDown(false),
	m_bMoveUp(false),
	m_pPlayerBody(obj.m_pPlayerBody)
{
	m_fSkill1Time = obj.m_fSkill1Time;
	m_tInfo = obj.m_tInfo;
	m_bUseBomb = false;
	m_fNoDmgTimer = obj.m_fNoDmgTimer;
	m_fNoDmgTimerMax = obj.m_fNoDmgTimerMax;
	m_bHit = obj.m_bHit;
	m_fBlinkTimer = obj.m_fBlinkTimer;
	m_fBlinkSpeed = obj.m_fBlinkSpeed;
}

CPlayer::~CPlayer()
{
}