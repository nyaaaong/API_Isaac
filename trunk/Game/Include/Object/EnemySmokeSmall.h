#pragma once

#include "Obj.h"

class CEnemySmokeSmall :
    public CObj
{
	friend class CScene;

protected:
	CEnemySmokeSmall();
	CEnemySmokeSmall(const CEnemySmokeSmall& obj);
	virtual ~CEnemySmokeSmall();

public:
	virtual bool Init();
	virtual void Start();
	virtual CEnemySmokeSmall* Clone();

public:
	void AnimationFinish();
};

