#pragma once

#include "MonsterBase.h"

class CRedFly :
    public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CRedFly();
	CRedFly(const CRedFly& obj);
	virtual ~CRedFly();

private:
	float	m_fPatternTimer;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CRedFly* Clone();

private:
	void AddRedFlyAnimation();
	void DetectPlayer(float fTime);
	void RedFlyPattern(float fTime);

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

