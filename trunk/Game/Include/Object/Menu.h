#pragma once

#include "Obj.h"

class CMenu :
    public CObj
{
	friend class CScene;

public:
	void GameStart(float fTime);
	void GameEditor(float fTime);
	void GameExit(float fTime);

public:
	virtual void Start();
	virtual bool Init();

protected:
	CMenu();
	CMenu(const CMenu& obj);
	virtual ~CMenu();

};

