#pragma once

#include "Obj.h"

class CEnemySmoke :
    public CObj
{
	friend class CScene;

protected:
	CEnemySmoke();
	CEnemySmoke(const CEnemySmoke& obj);
	virtual ~CEnemySmoke();

public:
	virtual bool Init();
	virtual void Start();
	virtual CEnemySmoke* Clone();

public:
	void AnimationFinish();
};

