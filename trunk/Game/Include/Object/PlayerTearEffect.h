#pragma once
#include "Obj.h"
class CPlayerTearEffect :
    public CObj
{
	friend class CScene;
	friend class CTear;

public:
	void AnimationFinish();

public:
	virtual void Move(const Vector2& tDir, bool bUseActivity);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseActivity);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CPlayerTearEffect* Clone();

protected:
	CPlayerTearEffect();
	CPlayerTearEffect(const CPlayerTearEffect& obj);
	virtual ~CPlayerTearEffect();
};

