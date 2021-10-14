#pragma once

#include "Obj.h"

class CBlock :
    public CObj
{
	friend class CScene;

private:
	EMapObject_Type	m_eType;
	float	m_fPrevLife;
	float	m_fLife;
	float	m_fLifeMax;
	class CRoomObj* m_pRoomObj;

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual float SetDamage(float fDamage);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);

protected:
	CBlock();
	CBlock(const CBlock& obj);
	virtual ~CBlock();

public:
	EMapObject_Type GetType()	const
	{
		return m_eType;
	}

public:
	void SetRoomObj(class CRoomObj* pObj)
	{
		m_pRoomObj = pObj;
	}
};

