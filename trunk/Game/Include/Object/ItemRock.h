#pragma once

#include "Obj.h"

class CItemRock :
    public CObj
{
	friend class CScene;

protected:
	class CItemGlasses* m_pItemGlasses;
	bool	m_bHasItem;

public:
	void SetItem(class CItemGlasses* pItem)
	{
		m_pItemGlasses = pItem;
	}

protected:
	CItemRock();
	CItemRock(const CItemRock& obj);
	virtual ~CItemRock();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

