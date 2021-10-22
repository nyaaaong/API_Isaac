
#include "MotherDoor.h"
#include "Mother.h"
#include "../Scene/RoomBase.h"

CMotherDoor::CMotherDoor() :
	m_pMother(nullptr),
	m_eDoorDir(DD_MAX),
	m_eDoorType(EMotherDoor_Type::Hand),
	m_fM4PDist(1000.f),
	m_fDetectDistance(200.f)
{
}

CMotherDoor::CMotherDoor(const CMotherDoor& obj)	:
	CObj(obj)
{
	m_pMother = obj.m_pMother;
	m_eDoorDir = obj.m_eDoorDir;
	m_eDoorType = obj.m_eDoorType;
	m_fM4PDist = 1000.f;
	m_fDetectDistance = obj.m_fDetectDistance;
}

CMotherDoor::~CMotherDoor()
{
}

void CMotherDoor::Start()
{
	CObj::Start();

	m_tPos = dynamic_cast<CRoomBase*>(m_pScene)->GetDoorPos(m_eDoorDir, DT_BOSS);
}

bool CMotherDoor::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetZOrder(EZOrder::Monster);

	AddDoorAnimation();

	return true;
}

void CMotherDoor::Update(float fTime)
{
	CObj::Update(fTime);

	DoorTypeUpdater();

	CObj* pPlayerBody = m_pScene->GetPlayerBody();

	if (pPlayerBody)
	{
		Vector2	tPlayerPos = pPlayerBody->GetPos() - pPlayerBody->GetSize() * pPlayerBody->GetPivot() + pPlayerBody->GetOffset();
		Vector2	tMonsterPos = m_tPos - m_tSize * m_tPivot * m_tOffset;

		m_fM4PDist = (tMonsterPos - tPlayerPos).Length();
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
	AddAnimation("MotherHandTop", false, 0.5f);
	AddAnimation("MotherHandBottom", false, 0.5f);
	AddAnimation("MotherHandLeft", false, 0.5f);
	AddAnimation("MotherHandRight", false, 0.5f);

	AddAnimation("MotherSkinTop", false);
	AddAnimation("MotherSkinBottom", false);
	AddAnimation("MotherSkinLeft", false);
	AddAnimation("MotherSkinRight", false);

	AddAnimation("MotherEyeTop", false);
	AddAnimation("MotherEyeBottom", false);
	AddAnimation("MotherEyeLeft", false);
	AddAnimation("MotherEyeRight", false);
}

void CMotherDoor::DetectPlayer(float fTime)
{
}

void CMotherDoor::DoorTypeUpdater()
{
	switch (m_eDoorType)
	{
	case EMotherDoor_Type::Hand:
		m_fDetectDistance = 100.f;
		if (m_eDoorDir == DD_TOP)
			ChangeAnimation("MotherHandTop");

		else if (m_eDoorDir == DD_LEFT)
			ChangeAnimation("MotherHandLeft");

		else if (m_eDoorDir == DD_RIGHT)
			ChangeAnimation("MotherHandRight");

		else if (m_eDoorDir == DD_BOTTOM)
			ChangeAnimation("MotherHandBottom");
		break;
	case EMotherDoor_Type::Eye:
		m_fDetectDistance = 300.f;
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
		m_fDetectDistance = 1000.f;
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

void CMotherDoor::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
}

void CMotherDoor::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CObj::CollisionColliding(pSrc, pDest, fTime);
}
