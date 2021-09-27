
#include "Collider.h"
#include "CollisionManager.h"

void CCollider::SetCollisionProfile(const std::string& strName)
{
	m_pProfile = CCollisionManager::GetInst()->FindProfile(strName);
}

void CCollider::AddCollisionList(CCollider* pCollider)
{
	m_CollisionList.push_back(pCollider);
}

bool CCollider::CheckCollisionList(CCollider* pCollider)
{
	std::list<CSharedPtr<CCollider>>::iterator	iter = m_CollisionList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == pCollider)
			return true;
	}

    return false;
}

void CCollider::DeleteCollisionList(CCollider* pCollider)
{
	std::list<CSharedPtr<CCollider>>::iterator	iter = m_CollisionList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == pCollider)
		{
			m_CollisionList.erase(iter);
			return;
		}
	}
}

void CCollider::ClearCollisionList()
{
	std::list<CSharedPtr<CCollider>>::iterator	iter = m_CollisionList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}

	m_CollisionList.clear();
}

void CCollider::CallCollisionBegin(CCollider* pDest, float fTime)
{
	if (m_pBeginFunc)
		m_pBeginFunc(this, pDest, fTime);
}

void CCollider::CallCollisionEnd(CCollider* pDest, float fTime)
{
	if (m_pEndFunc)
		m_pEndFunc(this, pDest, fTime);
}

bool CCollider::Init()
{
	m_pProfile = CCollisionManager::GetInst()->FindProfile("Default");

	return true;
}

void CCollider::Update(float fTime)
{
}

void CCollider::PostUpdate(float fTime)
{
}

void CCollider::Render(HDC hDC)
{
}

CCollider* CCollider::Clone()
{
	return nullptr;
}

CCollider::CCollider()	:
	m_pScene(nullptr),
	m_pOwner(nullptr),
	m_pProfile(nullptr),
	m_eType(ECollider_Type::Box),
	m_bEnable(true)
{
}

CCollider::CCollider(const CCollider& collider) :
	CRef(collider),
	m_pScene(nullptr),
	m_pOwner(nullptr),
	m_pProfile(nullptr),
	m_eType(ECollider_Type::Box),
	m_bEnable(true)
{
	m_eType = collider.m_eType;
	m_tOffset = collider.m_tOffset;
	m_pProfile = collider.m_pProfile;
}

CCollider::~CCollider()
{
	std::list<CSharedPtr<CCollider>>::iterator	iter = m_CollisionList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
}
