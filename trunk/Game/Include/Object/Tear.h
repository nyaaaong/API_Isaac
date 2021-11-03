#pragma once

#include "Obj.h"

class CTear :
    public CObj
{
	friend class CScene;

protected:
	Vector2		m_tDir;
	float		m_fDistance;
	ETearType	m_eTearType;
	float		m_fDamage;
	float		m_fTurnSpeed;
	class CCharacter* m_pOwner;
	bool		m_bHit;
	ESpecial_Tear		m_eSpecialTear; // 보스 전용
	bool		m_bChildTear;	// 스페셜 눈물에 의해 생성된 또다른 눈물

public:
	void SetChildTear(bool bChildTear)
	{
		m_bChildTear = bChildTear;
	}

	void SetSpecialTear(ESpecial_Tear eSpecialPattern)
	{
		m_eSpecialTear = eSpecialPattern;
	}

	void SetOwner(class CCharacter* pOwner)
	{
		m_pOwner = pOwner;
	}

	void SetTearType(ETearType eTearType)
	{
		m_eTearType = eTearType;
	}

	void SetDir(float x, float y)
	{
		m_tDir.x = x;
		m_tDir.y = y;
	}

	void SetDir(const Vector2& tDir)
	{
		m_tDir = tDir;
		m_tDir.Normalize();
	}

	void SetDir(float fAngle)
	{
		m_tDir.x = cosf(DegreeToRadian(fAngle));
		m_tDir.y = sinf(DegreeToRadian(fAngle));
	}

	void SetDistance(float fDistance)
	{
		m_fDistance = fDistance;
	}

public:
	const Vector2& GetDir()	const
	{
		return m_tDir;
	}

public:
	void TearDestroy();

private:
	void TearMechanism(float fTime);
	void MoveTear(float fTime);
	void PostProgressTear();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual CTear* Clone();

protected:
	CTear();
	CTear(const CTear& obj);
	virtual ~CTear();
};

