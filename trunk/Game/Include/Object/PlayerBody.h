#pragma once

#include "Obj.h"

class CPlayerBody :
    public CObj
{
	friend class CScene;

private:
	class CPlayer* m_pPlayer;
	Vector2	m_tMoveDir;

public:
	const Vector2& GetMoveDir()	const
	{
		return m_tMoveDir;
	}

public:
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual float SetDamage(float fDamage);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CPlayerBody* Clone();

public:
	virtual void AddPos(float x, float y);
	virtual void AddPos(const Vector2& tPos);

protected:
	CPlayerBody();
	CPlayerBody(const CPlayerBody& obj);
	virtual ~CPlayerBody();
};

