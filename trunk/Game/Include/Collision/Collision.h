#pragma once

#include "../GameInfo.h"

class CCollision
{
public:
	static bool CollisionBoxToBox(class CColliderBox* pSrc, class CColliderBox* pDest);
	static bool CollisionBoxToBox(const RectInfo& pSrc, const RectInfo& pDest);

	static bool CollisionSphereToSphere(class CColliderSphere* pSrc, class CColliderSphere* pDest);
	static bool CollisionSphereToSphere(const SphereInfo& pSrc, const SphereInfo& pDest);

	static bool CollisionBoxToSphere(class CColliderBox* pSrc, class CColliderSphere* pDest);
	static bool CollisionBoxToSphere(const RectInfo& pSrc, const SphereInfo& pDest);
};

