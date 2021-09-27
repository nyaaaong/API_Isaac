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

private:
	CMainMenu();
	virtual ~CMainMenu();
};

