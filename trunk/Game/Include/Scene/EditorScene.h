#pragma once

#include "Scene.h"

class CEditorScene :
	public CScene
{
	friend class CSceneManager;

private:
	CEditorScene();
	virtual ~CEditorScene();

private:
	bool	m_bStart;
	class CEditorDlg* m_pDlg;

public:
	virtual bool Init();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);

private:
	void LoadAnimationSequence();
	void LoadSound();
	void GameMenu(float fTime);

public:
	void OnEditor(float fTime);
};

