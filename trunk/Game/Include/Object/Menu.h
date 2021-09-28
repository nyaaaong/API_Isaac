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
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CMenu* Clone();

protected:
	CMenu();
	CMenu(const CMenu& obj);
	virtual ~CMenu();

};

