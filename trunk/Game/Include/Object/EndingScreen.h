#pragma once

#include "Obj.h"

class CEndingScreen :
    public CObj
{
	friend class CScene;

protected:
	CEndingScreen();
	CEndingScreen(const CEndingScreen& obj);
	virtual ~CEndingScreen();

public:
	virtual void Start();
	virtual bool Init();
};

