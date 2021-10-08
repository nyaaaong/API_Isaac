#pragma once

#include "Obj.h"

class CCharacter :
    public CObj
{
	friend class CScene;

protected:
	CharacterInfo	m_eInfo;
	Vector2			m_tBulletStartDir;
	float			m_fTearTimer;

public:
	bool IsDead()	const
	{
		return m_eInfo.fHP <= 0.f;
	}

public:
	float GetAttack()	const
	{
		return m_eInfo.fAttack;
	}

	float GetHP()	const
	{
		return m_eInfo.fHP;
	}

	float GetHPMax()	const
	{
		return m_eInfo.fHPMax;
	}

	int GetBomb()	const
	{
		return m_eInfo.iBomb;
	}

	int GetBombMax()	const
	{
		return m_eInfo.iBombMax;
	}

	float GetTearTimer()	const
	{
		return m_eInfo.fTearTimer;
	}

	float GetShotSpeed()	const
	{
		return m_eInfo.fShotSpeed;
	}

	float GetTearDistance()	const
	{
		return m_eInfo.fTearDistance;
	}

	float GetMoveSpeed()	const
	{
		return m_eInfo.fMoveSpeed;
	}

	const Vector2& GetBulletStartDir()	const
	{
		return m_tBulletStartDir;
	}

public:
	void SetBulletStartDir(const Vector2& tDir)
	{
		m_tBulletStartDir = tDir;
	}

	void SetBulletStartDir(float x, float y)
	{
		m_tBulletStartDir = Vector2(x, y);
	}

protected:
	virtual void SetFireStart();

public:
	virtual float SetDamage(float fDamage);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void Move(const Vector2& tDir, bool bUseField);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CCharacter* Clone();

protected:
	CCharacter();
	CCharacter(const CCharacter& obj);
	virtual ~CCharacter();
};

