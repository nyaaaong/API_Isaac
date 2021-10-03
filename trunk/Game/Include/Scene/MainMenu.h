#pragma once

#include "Stage.h"

class CMainMenu :
    public CScene
{
	friend class CSceneManager;

private:
	void LoadAnimationSequence();

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);

private:
	CMainMenu();
	virtual ~CMainMenu();
};

