#pragma once
#include "Obj.h"
class CItemAddEffect :
    public CObj
{
	friend class CScene;
	friend class CPlayer;

protected:
	CItemAddEffect();
	CItemAddEffect(const CItemAddEffect& obj);
	virtual ~CItemAddEffect();

public:
	virtual bool Init();
	virtual CItemAddEffect* Clone();
};
