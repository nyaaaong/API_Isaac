
#include "Collision.h"
#include "ColliderBox.h"
#include "ColliderSphere.h"

bool CCollision::CollisionBoxToBox(CColliderBox* pSrc, CColliderBox* pDest)
{
	if (CollisionBoxToBox(pSrc->GetInfo(), pDest->GetInfo()))
		return true;

	return false;
}

bool CCollision::CollisionBoxToBox(const RectInfo& pSrc, const RectInfo& pDest)
{
	if (pSrc.fL > pDest.fR)
		return false;

	if (pDest.fL > pSrc.fR)
		return false;

	if (pSrc.fT > pDest.fB)
		return false;

	if (pDest.fT > pSrc.fB)
		return false;

	return true;
}

bool CCollision::CollisionSphereToSphere(CColliderSphere* pSrc, CColliderSphere* pDest)
{
	if (CollisionSphereToSphere(pSrc->GetInfo(), pDest->GetInfo()))
		return true;

	return false;
}

bool CCollision::CollisionSphereToSphere(const SphereInfo& pSrc, const SphereInfo& pDest)
{
	float fDist = Distance(pSrc.tCenter, pDest.tCenter);

	return fDist <= pSrc.fRadius + pDest.fRadius;
}

bool CCollision::CollisionBoxToSphere(CColliderBox* pSrc, CColliderSphere* pDest)
{
	if (CollisionBoxToSphere(pSrc->GetInfo(), pDest->GetInfo()))
		return true;

	return false;
}

bool CCollision::CollisionBoxToSphere(const RectInfo& pSrc, const SphereInfo& pDest)
{
	if ((pSrc.fL <= pDest.tCenter.x && pSrc.fR >= pDest.tCenter.x) || (pSrc.fT <= pDest.tCenter.y && pSrc.fB >= pDest.tCenter.y))
	{
		RectInfo	tRect = pSrc;

		tRect.fL -= pDest.fRadius;
		tRect.fT -= pDest.fRadius;
		tRect.fR += pDest.fRadius;
		tRect.fB += pDest.fRadius;

		if (tRect.fL > pDest.tCenter.x)
			return false;

		if (tRect.fR < pDest.tCenter.x)
			return false;

		if (tRect.fT > pDest.tCenter.y)
			return false;

		if (tRect.fB < pDest.tCenter.y)
			return false;

		return true;
	}

	Vector2	tPos[4] = {};

	tPos[0] = Vector2(pSrc.fL, pSrc.fT);
	tPos[1] = Vector2(pSrc.fR, pSrc.fT);
	tPos[2] = Vector2(pSrc.fL, pSrc.fB);
	tPos[3] = Vector2(pSrc.fR, pSrc.fB);

	for (int i = 0; i < 4; ++i)
	{
		float	fDist = Distance(tPos[i], pDest.tCenter);

		if (fDist <= pDest.fRadius)
			return true;
	}

	return false;
}
