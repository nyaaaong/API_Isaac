
#include "Player.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "PlayerBody.h"

bool CPlayer::Init()
{
	if (!CCharacter::Init())
		return false;

	SetZOrder(EZOrder::Player);
	SetPivot(0.5f, 0.5f);

	AddPlayerAnimation();

	//m_pColliderBox = AddCollider<CColliderBox>("PlayerHead");
	//m_pColliderBox->SetExtent(100.f, 130.f);
	//m_pColliderBox->SetCollisionProfile("PlayerHead");

	m_pColliderSphere = AddCollider<CColliderSphere>("PlayerHead");
	m_pColliderSphere->SetRadius(40.f);
	m_pColliderSphere->SetCollisionProfile("PlayerHead");

	return true;
}

void CPlayer::Start()
{
	CCharacter::Start();

	AddCallback();

	m_pColliderSphere->SetCollisionBeginFunc<CPlayer>(this, &CPlayer::CollisionBegin);
	//m_pColliderBox->SetCollisionBeginFunc<CPlayer>(this, &CPlayer::CollisionBegin);
}

void CPlayer::Update(float fTime)
{
	CCharacter::Update(fTime);

	NoDamageTime(fTime);

	//m_pPlayerBody->SetPos(m_tPos);

	UpdateMoveUpDown();
}

void CPlayer::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	if (m_bIsMove && m_tVelocity.Length() == 0.f) // 움직인다는데 실제로 이동하지 않은 경우
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
	m_bHit = true;

	fDamage = CCharacter::SetDamage(fDamage);

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
	m_bBombEnable(false),
	m_bMoveUp(false),
	m_bMoveDown(false),
	m_fSkill1Time(0.f),
	m_pPlayerBody(nullptr),
	m_fNoDmgTimer(0.f),
	m_fNoDmgTimerMax(1.5f),
	m_bHit(false),
	m_fBlinkTimer(0.f),
	m_fBlinkSpeed(0.2f)
{
	m_eInfo.fAttack = 3.f;
	m_eInfo.fHP = PLAYER_HP_MAX;
	m_eInfo.fHPMax = PLAYER_HP_MAX;
	m_eInfo.iBomb = 3;
	m_eInfo.iBombMax = 99;
	m_eInfo.fTearTimer = 0.5f;
	m_eInfo.fShotSpeed = 400.f;
	m_eInfo.fTearDistance = 500.f;
	m_eInfo.fMoveSpeed = 300.f;
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
	m_eInfo = obj.m_eInfo;
	m_bBombEnable = false;
	m_fNoDmgTimer = obj.m_fNoDmgTimer;
	m_fNoDmgTimerMax = obj.m_fNoDmgTimerMax;
	m_bHit = obj.m_bHit;
	m_fBlinkTimer = obj.m_fBlinkTimer;
	m_fBlinkSpeed = obj.m_fBlinkSpeed;
}

CPlayer::~CPlayer()
{
}