#pragma once

#include "Item.h"

class CItemGlasses :
    public CItem
{
	friend class CScene;

protected:
	CItemGlasses();
	CItemGlasses(const CItemGlasses& obj);
	virtual ~CItemGlasses();

public:
	virtual bool Init();
	virtual void Start();
};

