#pragma once
#include "MonsterBase.h"
class CFly :
    public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CFly();
	CFly(const CFly& obj);
	virtual ~CFly();

private:
	float	m_fPatternTimer;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CFly* Clone();

private:
	void AddFlyAnimation();
	void FlyPattern(float fTime);

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
};

