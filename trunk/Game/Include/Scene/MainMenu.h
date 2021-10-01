#pragma once

#include "Stage.h"

class CMainMenu :
    public CScene
{
	friend class CSceneManager;

private:
	bool	m_bStart;

private:
	void LoadAnimationSequence();

public:
	virtual bool Init();
	virtual bool Update(float fTime);

private:
	CMainMenu();
	virtual ~CMainMenu();
};

