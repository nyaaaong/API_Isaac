#pragma once

#include "Collider.h"

class CColliderBox :
	public CCollider
{
	friend class CObj;

protected:
	float	m_fWidth;
	float	m_fHeight;
	RectInfo	m_tInfo;

public:
	void SetExtent(float fWidth, float fHeight)
	{
		m_fWidth = fWidth;
		m_fHeight = fHeight;
	}

	void SetExtent(const Vector2& tExtent)
	{
		m_fWidth = tExtent.x;
		m_fHeight = tExtent.y;
	}

public:
	Vector2 GetExtent()	const
	{
		return Vector2(m_fWidth, m_fHeight);
	}

	virtual float GetBottom()	const
	{
		return m_tInfo.fB;
	}

	const RectInfo& GetInfo()	const
	{
		return m_tInfo;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(HDC hDC);
	virtual CColliderBox* Clone();
	virtual bool Collision(CCollider* pDest);

protected:
	CColliderBox();
	CColliderBox(const CColliderBox& collider);
	virtual ~CColliderBox();
};

