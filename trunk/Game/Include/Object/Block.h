#pragma once

#include "Obj.h"

class CBlock :
    public CObj
{
	friend class CScene;

private:
	EMapObject_Type	m_eType;
	float	m_fHP;
	float	m_fHPMax;

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);

protected:
	CBlock();
	CBlock(const CBlock& obj);
	virtual ~CBlock();

public:
	EMapObject_Type GetType()	const
	{
		return m_eType;
	}		
};

