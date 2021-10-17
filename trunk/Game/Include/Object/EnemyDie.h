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

private:
	EEnemy_Type	m_eType;

public:
	void SetEnemyType(EEnemy_Type eType)
	{
		m_eType = eType;
	}

public:
	void AnimationFinish();
};

