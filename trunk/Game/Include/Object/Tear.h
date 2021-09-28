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

public:
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

private:
	void TearDestroy();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CTear* Clone();

protected:
	CTear();
	CTear(const CTear& obj);
	virtual ~CTear();
};

