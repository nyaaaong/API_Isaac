#pragma once

#include "Obj.h"

class CItemRock :
    public CObj
{
	friend class CScene;

protected:
	CItemRock();
	CItemRock(const CItemRock& obj);
	virtual ~CItemRock();

public:
	virtual bool Init();
	virtual void Start();
	virtual void Collision(float fTime);

public:
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

