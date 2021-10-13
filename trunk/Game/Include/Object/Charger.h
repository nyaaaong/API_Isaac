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
	bool	m_bChangeDir;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CCharger* Clone();

private:
	void AddChargerAnimation();
	void DetectPlayer();
	void ChagerPattern();

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

