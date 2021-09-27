
#include "ColliderSphere.h"
#include "ColliderBox.h"
#include "../Object/Obj.h"
#include "../GameManager.h"
#include "Collision.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

bool CColliderSphere::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderSphere::Update(float fTime)
{
	CCollider::Update(fTime);
}

void CColliderSphere::PostUpdate(float fTime)
{
	CCollider::PostUpdate(fTime);

	m_tInfo.tCenter = m_pOwner->GetPos() + m_tOffset;
}

void CColliderSphere::Render(HDC hDC)
{
	CCollider::Render(hDC);

#ifdef _DEBUG
	HPEN	hPen = CGameManager::GetInst()->GetGreenPen();

	if (!m_CollisionList.empty())
		hPen = CGameManager::GetInst()->GetRedPen();

	CCamera* pCamera = m_pScene->GetCamera();

	SphereInfo	tRenderInfo = m_tInfo;

	tRenderInfo.tCenter -= pCamera->GetPos();

	HGDIOBJ	hPrev = SelectObject(hDC, hPen);

	MoveToEx(hDC, static_cast<int>(tRenderInfo.tCenter.x + tRenderInfo.fRadius), static_cast<int>(tRenderInfo.tCenter.y), nullptr);

	for (int i = 0; i < 12; ++i)
	{
		float	fRadian = DegreeToRadian((i + 1) * (360.f / 12.f));

		float	x = tRenderInfo.tCenter.x + cosf(fRadian) * tRenderInfo.fRadius;
		float	y = tRenderInfo.tCenter.y + sinf(fRadian) * tRenderInfo.fRadius;

		LineTo(hDC, static_cast<int>(x), static_cast<int>(y));
	}

	SelectObject(hDC, hPrev);
#endif // _DEBUG

}

CColliderSphere* CColliderSphere::Clone()
{
	return new CColliderSphere(*this);
}

bool CColliderSphere::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case ECollider_Type::Box:
		return CCollision::CollisionBoxToSphere(dynamic_cast<CColliderBox*>(pDest), this);
	case ECollider_Type::Sphere:
		return CCollision::CollisionSphereToSphere(this, dynamic_cast<CColliderSphere*>(pDest));
	case ECollider_Type::Point:
		break;
	case ECollider_Type::Line:
		break;
	}

	return false;
}

CColliderSphere::CColliderSphere()
{
	m_tInfo.fRadius = 50.f;
	m_eType = ECollider_Type::Sphere;
}

CColliderSphere::CColliderSphere(const CColliderSphere& collider)	:
	CCollider(collider)
{
	m_tInfo = collider.m_tInfo;
}

CColliderSphere::~CColliderSphere()
{
}
