#pragma once

#include "MonsterBase.h"

class CPooter :
    public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CPooter();
	CPooter(const CPooter& obj);
	virtual ~CPooter();

private:
	float	m_fPatternTimer;
	float	m_fTearSpeedTimer;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CPooter* Clone();

private:
	void AddPooterAnimation();
	void DetectPlayer(float fTime);
	void PooterPattern(float fTime);
	void Fire();
	void FireAnimation();
	void DefaultAnimation();

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

