
#include "ColliderBox.h"
#include "../Object/Obj.h"
#include "../GameManager.h"
#include "Collision.h"
#include "ColliderSphere.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"

bool CColliderBox::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderBox::Update(float fTime)
{
	CCollider::Update(fTime);
}

void CColliderBox::PostUpdate(float fTime)
{
	CCollider::PostUpdate(fTime);

	Vector2 tPos = m_pOwner->GetPos();

	m_tInfo.fL = tPos.x - m_fWidth / 2.f + m_tOffset.x;
	m_tInfo.fT = tPos.y - m_fHeight / 2.f + m_tOffset.y;
	m_tInfo.fR = tPos.x + m_fWidth / 2.f + m_tOffset.x;
	m_tInfo.fB = tPos.y + m_fHeight / 2.f + m_tOffset.y;
}

void CColliderBox::Render(HDC hDC)
{
	CCollider::Render(hDC);

	if (!CSceneManager::GetInst()->IsDebug())
		return;

	HBRUSH	hBrush = CGameManager::GetInst()->GetGreenBrush();

	if (!m_CollisionList.empty())
		hBrush = CGameManager::GetInst()->GetRedBrush();

	CCamera* pCamera = m_pScene->GetCamera();

	RectInfo	tRectInfo = m_tInfo;

	tRectInfo.fL -= pCamera->GetPos().x;
	tRectInfo.fR -= pCamera->GetPos().x;
	tRectInfo.fT -= pCamera->GetPos().y;
	tRectInfo.fB -= pCamera->GetPos().y;

	RECT tRC = { static_cast<long>(tRectInfo.fL), static_cast<long>(tRectInfo.fT), static_cast<long>(tRectInfo.fR), static_cast<long>(tRectInfo.fB) };

	FrameRect(hDC, &tRC, hBrush);

}

CColliderBox* CColliderBox::Clone()
{
	return new CColliderBox(*this);
}

bool CColliderBox::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case ECollider_Type::Box:
		return CCollision::CollisionBoxToBox(this, dynamic_cast<CColliderBox*>(pDest));
	case ECollider_Type::Sphere:
		return CCollision::CollisionBoxToSphere(this, dynamic_cast<CColliderSphere*>(pDest));
	case ECollider_Type::Point:
		break;
	case ECollider_Type::Line:
		break;
	}

	return false;
}

CColliderBox::CColliderBox()	:
	m_fWidth(0.f),
	m_fHeight(0.f)
{
	m_eType = ECollider_Type::Box;
}

CColliderBox::CColliderBox(const CColliderBox& collider) :
	CCollider(collider),
	m_fWidth(collider.m_fWidth),
	m_fHeight(collider.m_fHeight)
{
	m_eType = collider.m_eType;
}

CColliderBox::~CColliderBox()
{
}
