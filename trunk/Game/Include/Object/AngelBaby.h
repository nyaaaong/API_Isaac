#pragma once
#include "MonsterBase.h"
class CAngelBaby :
    public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CAngelBaby();
	CAngelBaby(const CAngelBaby& obj);
	virtual ~CAngelBaby();

private:
	float	m_fPatternTimer;
	float	m_fTearSpeedTimer;
	float	m_fFireAnimDelay;
	float	m_fFireAnimDelayMax;
	bool	m_bIsFire;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CAngelBaby* Clone();

private:
	void DetectPlayer(float fTime);
	void AngelBabyPattern(float fTime);
	void Fire();
	void FireEnd(float fTime);

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

