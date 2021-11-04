
#include "Player.h"
#include "PlayerBody.h"
#include "ObjManager.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

bool CPlayer::Init()
{
	if (!CCharacter::Init())
		return false;

	SetZOrder(EZOrder::Player);
	SetPivot(0.5f, 0.5f);

	AddPlayerAnimation();

	CObjManager::GetInst()->PullPlayerInfo(this);

	return true;
}

void CPlayer::Start()
{
	CCharacter::Start();

	AddNotify();
	AddCallback();

	m_pPlayerBody = dynamic_cast<CPlayerBody*>(m_pScene->GetPlayerBody());
	m_pPlayerBody->Start();
	m_pPlayerBody->SetPos(m_tPos);
	m_pPlayerBody->EnableDamage(m_bEnableDamage);

	m_pColliderBox = AddCollider<CColliderBox>("PlayerHead");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionProfile("PlayerHead");
}

void CPlayer::Update(float fTime)
{
	CCharacter::Update(fTime);

	NoDamageTime(fTime);

	UpdateMoveUpDown();

	IsaacAddItemUpdater(fTime);
}

void CPlayer::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	if (!m_bIsFire &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveUp") &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveDown") &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveLeft") &&
		!CInput::GetInst()->GetKeyPush("PlayerMoveRight")&&
		!CInput::GetInst()->GetKeyPush("PlayerItemMoveUp") &&
		!CInput::GetInst()->GetKeyPush("PlayerItemMoveDown") &&
		!CInput::GetInst()->GetKeyPush("PlayerItemMoveLeft") &&
		!CInput::GetInst()->GetKeyPush("PlayerItemMoveRight"))
		DefaultAnimation();

	if (!m_bDie && m_tInfo.fHP <= 0.f)
		IsaacDeath(fTime);
}

void CPlayer::Collision(float fTime)
{
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
	m_fNoDmgTimerMax(3.f),
	m_bHit(false),
	m_fBlinkTimer(0.f),
	m_fBlinkSpeed(0.2f),
	m_bDie(false),
	m_fAnimDelay(0.f),
	m_bIsItem(false),
	m_ItemAddEffect(nullptr),
	m_bIsItemAnim(false),
	m_bCheatNoDamage(false)
{
	m_tInfo.fAttack = 3.f;
	m_tInfo.fHP = PLAYER_HP_MAX;
	m_tInfo.fHPMax = PLAYER_HP_MAX;
	m_tInfo.fTearSpeed = 0.5f;
	m_tInfo.fShotSpeed = 400.f;
	m_tInfo.fTearDistance = 300.f;
	m_tInfo.fMoveSpeed = 300.f;
}

CPlayer::CPlayer(const CPlayer& obj) :
	CCharacter(obj),
	m_bIsFire(false),
	m_bIsMove(false),
	m_bMoveDown(false),
	m_bMoveUp(false),
	m_pPlayerBody(obj.m_pPlayerBody),
	m_bDie(false),
	m_ItemAddEffect(nullptr),
	m_bIsItemAnim(false),
	m_bCheatNoDamage(false)
{
	m_fSkill1Time = obj.m_fSkill1Time;
	m_tInfo = obj.m_tInfo;
	m_bUseBomb = false;
	m_fNoDmgTimer = obj.m_fNoDmgTimer;
	m_fNoDmgTimerMax = obj.m_fNoDmgTimerMax;
	m_bHit = obj.m_bHit;
	m_fBlinkTimer = obj.m_fBlinkTimer;
	m_fBlinkSpeed = obj.m_fBlinkSpeed;
	m_fAnimDelay = 0.f;
	m_bIsItem = obj.m_bIsItem;
}

CPlayer::~CPlayer()
{
}