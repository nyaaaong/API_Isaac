#pragma once

#include "Obj.h"

class CBomb :
    public CObj
{
	friend class CScene;

protected:
	CBomb();
	CBomb(const CBomb& obj);
	virtual ~CBomb();

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float fTime);
	virtual void Collision(float fTime);
	virtual CBomb* Clone();

private:
	Vector2	m_tDir;
	float	m_fDistance;
	float	m_fTimer;
	float	m_fTimerMax;

private:
	void BombDestroy();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

