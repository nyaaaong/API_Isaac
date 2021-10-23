#pragma once

#include "Item.h"

class CHeart :
    public CItem
{
	friend class CScene;

protected:
	EHeart_Type	m_eType;

public:
	void SetHeartType(EHeart_Type eType)
	{
		m_eType = eType;
	}

protected:
	CHeart();
	CHeart(const CHeart& obj);
	virtual ~CHeart();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CHeart* Clone();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

