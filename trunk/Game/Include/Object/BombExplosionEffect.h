#pragma once

#include "Obj.h"

class CBombExplosionEffect :
    public CObj
{
	friend class CScene;
	friend class CBomb;

protected:
	CBombExplosionEffect();
	CBombExplosionEffect(const CBombExplosionEffect& obj);
	virtual ~CBombExplosionEffect();

public:
	virtual bool Init();
	virtual void Start();
	virtual CBombExplosionEffect* Clone();

public:
	void AnimationFinish();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

