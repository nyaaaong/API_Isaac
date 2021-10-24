#pragma once

#include "Scene.h"

class CEnding :
	public CScene
{
	friend class CSceneManager;

protected:
	class CEndingScreen* m_pScreen;

protected:
	CEnding();
	virtual ~CEnding();

public:
	virtual bool Init();
};

