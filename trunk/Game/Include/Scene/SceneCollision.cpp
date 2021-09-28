
#include "SceneCollision.h"
#include "Scene.h"
#include "Camera.h"
#include "../Input.h"
#include "../Collision/Collider.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWidget.h"

void CSceneCollision::AddCollider(CCollider* pCollider)
{
	m_vecCollider.push_back(pCollider);
}

void CSceneCollision::AddUIWindow(CUIWindow* pWindow)
{
	m_vecUIWindow.push_back(pWindow);
}

void CSceneCollision::CollisionMouse(float fTime)
{
}

void CSceneCollision::Collision(float fTime)
{
	size_t iSize = m_vecCollider.size();

	if (iSize > 1)
	{
		for (size_t i = 0; i < iSize - 1; ++i)
		{
			CCollider* pSrc = m_vecCollider[i];

			for (size_t j = i + 1; j < iSize; ++j)
			{
				CCollider* pDest = m_vecCollider[j];

				if (pSrc->GetOwner() == pDest->GetOwner()) // 같은 오브젝트의 충돌체인 경우
					continue;

				CollisionProfile* pSrcProfile = pSrc->GetProfile();
				CollisionProfile* pDestProfile = pDest->GetProfile();

				ECollision_State	eSrcState = pSrcProfile->vecState[pDestProfile->eChannel];
				ECollision_State	eDestState = pDestProfile->vecState[pSrcProfile->eChannel];

				if (eSrcState == ECollision_State::Ignore && eDestState == ECollision_State::Ignore)
					continue;

				if (pSrc->Collision(pDest))
				{
					if (!pSrc->CheckCollisionList(pDest)) // 충돌이 되지 않고 있었을 때
					{
						pSrc->AddCollisionList(pDest);
						pDest->AddCollisionList(pSrc);

						pSrc->CallCollisionBegin(pDest, fTime);
						pDest->CallCollisionBegin(pSrc, fTime);
					}
				}

				else if (pSrc->CheckCollisionList(pDest)) // 충돌이 되고 있었을 때
				{
					pSrc->DeleteCollisionList(pDest);
					pDest->DeleteCollisionList(pSrc);

					pSrc->CallCollisionEnd(pDest, fTime);
					pDest->CallCollisionEnd(pSrc, fTime);
				}
			}
		}
	}

	m_vecCollider.clear(); // 충돌 처리 후 제거
	m_vecUIWindow.clear();
}

int CSceneCollision::SortY(const void* pSrc, const void* pDest)
{
	CCollider* pSrcObj = *(CCollider**)pSrc;
	CCollider* pDestObj = *(CCollider**)pDest;

	float	fSrcY = pSrcObj->GetBottom();
	float	fDestY = pDestObj->GetBottom();

	if (fSrcY > fDestY)
		return -1;

	else if (fSrcY < fDestY)
		return 1;

    return 0;
}

CSceneCollision::CSceneCollision()	:
	m_pScene(nullptr),
	m_pSelectWidget(nullptr),
	m_pMouseCollision(nullptr)
{
	m_vecCollider.reserve(500);
	m_vecUIWindow.reserve(10);
}

CSceneCollision::~CSceneCollision()
{
}
