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
	virtual bool Init();
	virtual void Start();
	virtual CPlayerTearEffect* Clone();

protected:
	CPlayerTearEffect();
	CPlayerTearEffect(const CPlayerTearEffect& obj);
	virtual ~CPlayerTearEffect();
};

