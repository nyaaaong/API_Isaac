#pragma once

#include "MonsterBase.h"

class CCharger :
    public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CCharger();
	CCharger(const CCharger& obj);
	virtual ~CCharger();

private:
	float	m_fSpikeDelay;
	float	m_fPatternTimer;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CCharger* Clone();

private:
	void RandomDir();
	void AddChargerAnimation();
	void DetectPlayer(float fTime);
	void ChagerPattern(float fTime);

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

