#pragma once

#include "Obj.h"

class CMotherLeg :
    public CObj
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CMotherLeg();
	CMotherLeg(const CMotherLeg& obj);
	virtual ~CMotherLeg();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CMotherLeg* Clone();
	virtual void EnableTask();
	virtual float SetDamage(float fDamage);

private:
	class CMother* m_pMother;
	Vector2	m_tPlayerPos;
	bool	m_bAttack;
	bool	m_bAttackEnd;
	float	m_fAttackDelay;
	float	m_fIdleTime;
	bool	m_bAttackPossible;

public:
	void SetMother(class CMother* pMother)
	{
		m_pMother = pMother;
	}

private:
	void DetectPlayer(float fTime);

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

