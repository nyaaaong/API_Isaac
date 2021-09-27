#pragma once

#include "Obj.h"

class CDoor :
    public CObj
{
	friend class CRoom;

protected:
	class CScene* m_pNextRoom;

public:
	class CScene* GetNextRoom()	const
	{
		return m_pNextRoom;
	}

public:
	virtual void Move(const Vector2& tDir, bool bUseActivity);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseActivity);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CDoor* Clone();

protected:
	CDoor();
	CDoor(const CDoor& obj);
	virtual ~CDoor();
};
