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
	int		m_iCurRoom;
	EObject	m_eCurObject;
	EEditor_State	m_eState;
	std::vector<CSharedPtr<CUIImage>>	m_vecMouse;
	CSharedPtr<CUIImage>	m_pCurMouse;
	float	m_fTimer;
	float	m_fMaxTimer;
	bool	m_bCoolDown; // 파일 로드와 동시에 오브젝트를 생성하는 것을 방지한다.
	char	m_cTitleText[256];
	char	m_cStateText[32];
	char	m_cFPSText[64];

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Render(HDC hDC);

private:
	void CreateMouseCursor();

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

	void CreateObject(float fTime);
	void DeleteObject(float fTime);

private:
	void LoadAnimationSequence();
	void LoadSound();

private:
	void GameMenu(float fTime);

private:
	void MouseWindowCheck();
	void MouseObjectView();
	void MouseSetBox();
	void EditorTextOut();

private:
	virtual void SaveFullPath(const char* cFullPath);
	virtual void LoadFullPath(const char* cFullPath);
};

