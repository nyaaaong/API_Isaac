#pragma once

#include "Collider.h"

class CColliderSphere :
	public CCollider
{
	friend class CObj;

protected:
	SphereInfo	m_tInfo;

public:
	void SetRadius(float fRadius)
	{
		m_tInfo.fRadius = fRadius;
	}

public:
	float GetRadius()	const
	{
		return m_tInfo.fRadius;
	}

	virtual float GetBottom()	const
	{
		return m_tInfo.tCenter.y + m_tInfo.fRadius;
	}

	const SphereInfo& GetInfo()	const
	{
		return m_tInfo;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(HDC hDC);
	virtual CColliderSphere* Clone();
	virtual bool Collision(CCollider* pDest);

protected:
	CColliderSphere();
	CColliderSphere(const CColliderSphere& collider);
	virtual ~CColliderSphere();
};

