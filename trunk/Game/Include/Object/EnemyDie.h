#pragma once

#include "Obj.h"

class CEnemyDie :
    public CObj
{
	friend class CScene;

protected:
	CEnemyDie();
	CEnemyDie(const CEnemyDie& obj);
	virtual ~CEnemyDie();

public:
	virtual bool Init();
	virtual void Start();
	virtual CEnemyDie* Clone();

public:
	void AnimationFinish();
};

