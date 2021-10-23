#pragma once

#include "Obj.h"

class CEnemySmokeNormal :
    public CObj
{
	friend class CScene;

protected:
	CEnemySmokeNormal();
	CEnemySmokeNormal(const CEnemySmokeNormal& obj);
	virtual ~CEnemySmokeNormal();

public:
	virtual bool Init();
	virtual void Start();
	virtual CEnemySmokeNormal* Clone();

public:
	void AnimationFinish();
};

