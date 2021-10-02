
#pragma once

#include "GameInfo.h"

class CGameManager
{
private:
	static bool m_bLoop;
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	HDC			m_hBackDC;
	HBITMAP		m_hBackBmp;
	HBITMAP		m_hPrevBackBmp;
	Resolution	m_tRS;
	class CTimer* m_pTimer;
	float		m_fTimeScale;
	HBRUSH		m_hGreenBrush;
	HBRUSH		m_hRedBrush;
	HPEN		m_hGreenPen;
	HPEN		m_hRedPen;
	bool		m_bIsActiveGame;
	bool		m_bTitleUpdate;
	char		m_cTextFPS[64];

public:
	bool IsTitleUpdate()	const
	{
		return m_bTitleUpdate;
	}

	bool IsActiveGame()	const
	{
		return m_bIsActiveGame;
	}

	const Resolution& GetResolution()	const
	{
		return m_tRS;
	}

	HPEN GetGreenPen()	const
	{
		return m_hGreenPen;
	}

	HPEN GetRedPen()	const
	{
		return m_hRedPen;
	}

	HBRUSH GetGreenBrush()	const
	{
		return m_hGreenBrush;
	}

	HBRUSH GetRedBrush()	const
	{
		return m_hRedBrush;
	}

public:
	void SetTitleUpdate(bool bIsUpdate)
	{
		m_bTitleUpdate = bIsUpdate;
	}

	void SetActiveGame(bool bIsActiveGame)
	{
		m_bIsActiveGame = bIsActiveGame;
	}

	HDC GetWindowDC()	const
	{
		return m_hDC;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

public:
	void SetTimeScale(float fTimeScale)
	{
		m_fTimeScale = fTimeScale;
	}

public:
	float GetDeltaTime()	const;
	float GetFPS()	const;

public:
	bool Init(HINSTANCE hInst);
	int Run();
	void Exit();

private:
	void Logic();
	bool Update(float fTime);
	bool PostUpdate(float fTime);
	bool Collision(float fTime);
	void Render(float fTime);

private:
	ATOM Register();
	BOOL Create();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

private:
	static CGameManager* m_pInst;

public:
	static CGameManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CGameManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	CGameManager();
	~CGameManager();
};

