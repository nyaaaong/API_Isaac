#pragma once

#include "Scene.h"
#include "../UI/UIImage.h"

class CEditorScene :
	public CScene
{
	friend class CSceneManager;

private:
	CEditorScene();
	virtual ~CEditorScene();

private:
	bool	m_bStart;
	int		m_iCurRoom;
	int		m_iMaxRoom;
	EObject	m_eCurObject;
	EEditor_State	m_eState;
	std::vector<CSharedPtr<CUIImage>>	m_vecMouse;
	CSharedPtr<CUIImage>	m_pCurMouse;

public:
	virtual bool Init();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Render(HDC hDC);

private:
	void NextRoom(float fTime);
	void PrevRoom(float fTime);
	void ClearRoom(float fTime);
	void SaveRoom(float fTime);
	void LoadRoom(float fTime);

private:
	void NextObject(float fTime);
	void PrevObject(float fTime);
	void SelectObject1(float fTime);
	void SelectObject2(float fTime);
	void SelectObject3(float fTime);
	void SelectObject4(float fTime);
	void SelectObject(EObject eSelect);

private:
	void LoadAnimationSequence();
	void LoadSound();

private:
	void GameMenu(float fTime);

private:
	void MouseWindowCheck();
	void MouseObjectView();
	void EditorTextOut();
};

