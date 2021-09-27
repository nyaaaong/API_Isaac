#pragma once

#include "Obj.h"

class CPlayerBody :
    public CObj
{
	friend class CScene;

private:
	class CPlayer* m_pPlayer;

public:
	void SetPlayer(class CPlayer* pPlayer)
	{
		m_pPlayer = pPlayer;
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
	virtual CPlayerBody* Clone();

protected:
	CPlayerBody();
	CPlayerBody(const CPlayerBody& obj);
	virtual ~CPlayerBody();
};

