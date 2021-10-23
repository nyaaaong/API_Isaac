
#include "MotherDoor.h"
#include "Mother.h"
#include "Tear.h"
#include "MonsterSpawner.h"
#include "../Scene/RoomBase.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CMotherDoor::CMotherDoor() :
	m_pMother(nullptr),
	m_eDoorDir(DD_MAX),
	m_eDoorType(EMotherDoor_Type::Max),
	m_fM4PDist(1000.f),
	m_fM4PMaxDist(200.f),
	m_bAttackEnd(false),
	m_fAttackEndDelay(0.f),
	m_fStartFuncDelay(0.f)
{
}

CMotherDoor::CMotherDoor(const CMotherDoor& obj)	:
	CObj(obj)
{
	m_pMother = obj.m_pMother;
	m_eDoorDir = obj.m_eDoorDir;
	m_eDoorType = obj.m_eDoorType;
	m_fM4PDist = 1000.f;
	m_fM4PMaxDist = 200.f;
	m_bAttackEnd = false;
	m_fAttackEndDelay = 0.f;
	m_fStartFuncDelay = 0.f;
}

CMotherDoor::~CMotherDoor()
{
}

void CMotherDoor::Start()
{
	CObj::Start();
	
	m_pColliderBox = AddCollider<CColliderBox>("Monster");
	m_pColliderBox->SetCollisionProfile("Monster");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionCollidingFunc<CMotherDoor>(this, &CMotherDoor::CollisionColliding);

	AddAnimationNotify<CMotherDoor>("MotherHandTop", 2, this, &CMotherDoor::ResizeColliderBox);
	AddAnimationNotify<CMotherDoor>("MotherHandBottom", 2, this, &CMotherDoor::ResizeColliderBox);
	AddAnimationNotify<CMotherDoor>("MotherHandLeft", 2, this, &CMotherDoor::ResizeColliderBox);
	AddAnimationNotify<CMotherDoor>("MotherHandRight", 2, this, &CMotherDoor::ResizeColliderBox);
}

bool CMotherDoor::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::MonsterDoor);

	AddDoorAnimation();

	return true;
}

void CMotherDoor::Update(float fTime)
{
	CObj::Update(fTime);

	DetectPlayer(fTime);
	DoorTypeUpdater();
	StartFunc(fTime);

	if (m_bAttackEnd)
	{
		m_fAttackEndDelay += fTime;

		if (m_fAttackEndDelay >= 2.f)
			Disable();
	}
}

void CMotherDoor::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);

	if (!m_pMother->IsActive())
		Destroy();
}

CMotherDoor* CMotherDoor::Clone()
{
	return new CMotherDoor(*this);
}

void CMotherDoor::SetDoorType(EMotherDoor_Type eDoorType)
{
	m_eDoorType = eDoorType;
}

void CMotherDoor::AddDoorAnimation()
{
	AddAnimation("MotherSkinTop", false);
	AddAnimation("MotherSkinBottom", false);
	AddAnimation("MotherSkinLeft", false);
	AddAnimation("MotherSkinRight", false);

	AddAnimation("MotherEyeTop", false);
	AddAnimation("MotherEyeBottom", false);
	AddAnimation("MotherEyeLeft", false);
	AddAnimation("MotherEyeRight", false);

	AddAnimation("MotherHandTop", false, 0.1f);
	AddAnimation("MotherHandBottom", false, 0.1f);
	AddAnimation("MotherHandLeft", false, 0.1f);
	AddAnimation("MotherHandRight", false, 0.1f);
}

void CMotherDoor::DetectPlayer(float fTime)
{
	CObj* pPlayerBody = m_pScene->GetPlayerBody();

	if (pPlayerBody)
	{
		Vector2	tPlayerPos = pPlayerBody->GetPos() - pPlayerBody->GetSize() * pPlayerBody->GetPivot() + pPlayerBody->GetOffset();
		Vector2	tMonsterPos = m_tPos - m_tSize * m_tPivot * m_tOffset;

		m_fM4PDist = (tMonsterPos - tPlayerPos).Length();
	}

	if (m_fM4PDist <= m_fM4PMaxDist)
		SetDoorType(EMotherDoor_Type::Hand);
}

void CMotherDoor::DoorTypeUpdater()
{
	switch (m_eDoorType)
	{
	case EMotherDoor_Type::Hand:
		if (m_eDoorDir == DD_TOP)
		{
			ChangeAnimation("MotherHandTop");
			m_pColliderBox->SetExtent(Vector2(127.f, 110.f));
		}

		else if (m_eDoorDir == DD_LEFT)
		{
			ChangeAnimation("MotherHandLeft");
			m_pColliderBox->SetExtent(Vector2(110.f, 127.f));
		}

		else if (m_eDoorDir == DD_RIGHT)
		{
			ChangeAnimation("MotherHandRight");
			m_pColliderBox->SetExtent(Vector2(110.f, 127.f));
		}

		else if (m_eDoorDir == DD_BOTTOM)
		{
			ChangeAnimation("MotherHandBottom");
			m_pColliderBox->SetExtent(Vector2(127.f, 110.f));
		}
		break;
	case EMotherDoor_Type::Eye:
		if (m_eDoorDir == DD_TOP)
			ChangeAnimation("MotherEyeTop");

		else if (m_eDoorDir == DD_LEFT)
			ChangeAnimation("MotherEyeLeft");

		else if (m_eDoorDir == DD_RIGHT)
			ChangeAnimation("MotherEyeRight");

		else if (m_eDoorDir == DD_BOTTOM)
			ChangeAnimation("MotherEyeBottom");
		break;
	case EMotherDoor_Type::Skin:
		if (m_eDoorDir == DD_TOP)
			ChangeAnimation("MotherSkinTop");

		else if (m_eDoorDir == DD_LEFT)
			ChangeAnimation("MotherSkinLeft");

		else if (m_eDoorDir == DD_RIGHT)
			ChangeAnimation("MotherSkinRight");

		else if (m_eDoorDir == DD_BOTTOM)
			ChangeAnimation("MotherSkinBottom");
		break;
	}
}

void CMotherDoor::StartFunc(float fTime)
{
	if (m_bAttackEnd)
		return;

	m_fStartFuncDelay += fTime;

	switch (m_eDoorType)
	{
	case EMotherDoor_Type::Eye:
	{
		if (m_fStartFuncDelay >= 0.5f)
		{
			m_fStartFuncDelay = 0.f;

			GetM2PDir();

			CSharedPtr<CTear>	pTear = m_pScene->CreateObject<CTear>("MonsterTear", "MonsterTear", m_tBulletStartPos, Vector2(80.f, 80.f));
			pTear->SetDir(m_tM2PDir);
			pTear->SetOwner(m_pMother);
			m_pScene->GetSceneResource()->SoundPlay("Tear");
		}

		else
			return;
	}
		break;
	case EMotherDoor_Type::Skin:
		CMonsterSpawner::GetInst()->CreateMonster(m_tBulletStartPos);

		if (!m_pScene->GetSceneResource()->IsPlaying("MotherSummon"))
			m_pScene->GetSceneResource()->SoundPlay("MotherSummon");

		break;
	}

	m_bAttackEnd = true;
}

void CMotherDoor::ResizeColliderBox()
{
	if (m_eDoorType != EMotherDoor_Type::Hand)
		return;

	switch (m_eDoorDir)
	{
	case DD_LEFT:
		m_tPos.x += 40.f;
		break;
	case DD_RIGHT:
		m_tPos.x -= 40.f;
		m_pColliderBox->SetExtent(Vector2(255.f, 236.f));
		break;
	case DD_TOP:
		m_tPos.y += 40.f;
		break;
	case DD_BOTTOM:
		m_tPos.y -= 40.f;
		m_pColliderBox->SetExtent(Vector2(236.f, 255.f));
		break;
	}

	m_pScene->GetSceneResource()->SoundPlay("MotherHandAttack");
}

void CMotherDoor::GetM2PDir()
{
	CObj* pPlayer = m_pScene->GetPlayer();

	float	fAngle = 0.f;

	if (pPlayer)
		fAngle = GetAngle(m_tPos, pPlayer->GetPos());

	if (isnan<float>(fAngle))
		return;

	float	fDegree = DegreeToRadian(fAngle);

	if (!fDegree)
		return;

	m_tM2PDir.x = cosf(fDegree);
	m_tM2PDir.y = sinf(fDegree);
}

void CMotherDoor::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	std::string	strName = pDest->GetName();
	CObj* pPlayer = pDest->GetOwner();

	if (strName == "PlayerHead" || strName == "PlayerBody")
		pPlayer->SetDamage(m_pMother->GetAttack());
}

float CMotherDoor::SetDamage(float fDamage)
{
	fDamage = CObj::SetDamage(fDamage);

	m_pMother->SetDamage(fDamage);

	return fDamage;
}

void CMotherDoor::EnableTask()
{
	Vector2	tFieldLT = m_pScene->GetFieldLT();
	Vector2	tFieldRB = m_pScene->GetFieldRB();

	m_tPos = dynamic_cast<CRoomBase*>(m_pScene)->GetDoorPos(m_eDoorDir, DT_BOSS);

	m_tBulletStartPos = m_tPos;

	switch (m_eDoorDir)
	{
	case DD_LEFT:
		m_tPos.x -= 20.f;
		m_tBulletStartPos.x = tFieldLT.x + 20.f;
		switch (m_eDoorType)
		{
		case EMotherDoor_Type::Eye:
			SetSize(132.f, 126.f);
			break;
		case EMotherDoor_Type::Skin:
			SetSize(121.f, 142.f);
			break;
		}
		break;
	case DD_RIGHT:
		m_tPos.x += 20.f;
		m_tBulletStartPos.x = tFieldRB.x - 20.f;
		switch (m_eDoorType)
		{
		case EMotherDoor_Type::Eye:
			SetSize(132.f, 126.f);
			break;
		case EMotherDoor_Type::Skin:
			SetSize(121.f, 142.f);
			break;
		}
		break;
	case DD_TOP:
		m_tPos.y -= 20.f;
		m_tBulletStartPos.y = tFieldLT.y + 30.f;
		switch (m_eDoorType)
		{
		case EMotherDoor_Type::Eye:
			SetSize(126.f, 132.f);
			break;
		case EMotherDoor_Type::Skin:
			SetSize(142.f, 121.f);
			break;
		}
		break;
	case DD_BOTTOM:
		m_tPos.y += 20.f;
		m_tBulletStartPos.y = tFieldRB.y - 30.f;
		switch (m_eDoorType)
		{
		case EMotherDoor_Type::Eye:
			SetSize(126.f, 132.f);
			break;
		case EMotherDoor_Type::Skin:
			SetSize(142.f, 121.f);
			break;
		}
		break;
	}

	CMonsterSpawner::GetInst()->CreateSmoke(m_tPos);

	m_pMother->SetProgress(true);
}

void CMotherDoor::DisableTask()
{
	m_fM4PDist = 1000.f;
	m_bAttackEnd = false;
	m_fAttackEndDelay = 0.f;
	m_eDoorType = EMotherDoor_Type::Max;

	m_pMother->SetProgress(false);
}
