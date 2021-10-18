
#include "Block.h"
#include "MonsterBase.h"
#include "../Map/RoomObj.h"
#include "../Map/MapManager.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

void CBlock::Start()
{
	CObj::Start();

	m_fLife = m_pRoomObj->m_fLife;

	m_pColliderBox->SetCollisionBeginFunc<CBlock>(this, &CBlock::CollisionBegin);
	m_pColliderBox->SetCollisionCollidingFunc<CBlock>(this, &CBlock::CollisionColliding);
}

bool CBlock::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);
	SetPos(m_tPos + m_tSize * m_tPivot);

	CMapManager::GetInst()->SetBlockSize(m_tSize);
	CMapManager::GetInst()->SetBlockPivot(m_tPivot);

	SetZOrder(EZOrder::RoomObject);

	m_pColliderBox = AddCollider<CColliderBox>("MapObject");
	m_pColliderBox->SetExtent(m_tSize);
	m_pColliderBox->SetCollisionProfile("Object");

	return true;
}

void CBlock::Update(float fTime)
{
	CObj::Update(fTime);

	if (m_fLife != m_fPrevLife)
	{
		m_fPrevLife = m_fLife;

		if (m_eType == MT_ROCK)
			m_fLife = 0.f;
		
		if (m_pRoomObj)
			m_pRoomObj->m_fLife = m_fLife;

		if (m_fLife <= 0.f)
			Destroy();
	}
}

CBlock::CBlock()	:
	m_eType(MT_NONE),
	m_fPrevLife(4.f),
	m_fLife(4.f),
	m_fLifeMax(4.f),
	m_pRoomObj(nullptr)
{
}

CBlock::CBlock(const CBlock& obj) :
	CObj(obj)
{
	m_eType = obj.m_eType;
	m_fPrevLife = obj.m_fPrevLife;
	m_fLife = obj.m_fLife;
	m_fLifeMax = obj.m_fLifeMax;
	m_pRoomObj = obj.m_pRoomObj;
}

CBlock::~CBlock()
{
}

void CBlock::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CBlock::CollisionColliding(CCollider* pSrc, CCollider* pDest, float fTime)
{
	std::string	strName = pDest->GetName();
	CObj* pDestObj = pDest->GetOwner();

	if (strName == "PlayerHead")
		return;

	float	tMove = 0.f;

	if (m_eType == MT_SPIKE)
	{
		if (strName == "PlayerBody")
			pDestObj->SetDamage(1.f);
	}

	else if (m_eType == MT_ROCK || m_eType == MT_IRON || m_eType == MT_POOP)
	{
		if (pDestObj->GetName() == "Charger")
			dynamic_cast<CMonsterBase*>(pDestObj)->BlockCollision();

		PushCollider(pSrc, pDest);
	}
}

float CBlock::SetDamage(float fDamage)
{
	fDamage = CObj::SetDamage(fDamage);

	m_fLife -= fDamage;

	if (m_fLife < 0.f)
		m_fLife = 0.f;

	return fDamage;
}
