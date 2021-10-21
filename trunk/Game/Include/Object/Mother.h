#pragma once

#include "MonsterBase.h"

class CMother :
    public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CMother();
	CMother(const CMother& obj);
	virtual ~CMother();

private:
	float	m_fPatternTimer;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CMother* Clone();

private:
	void AddMotherAnimation();
	void DetectPlayer(float fTime);
	void MotherPattern(float fTime);

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};