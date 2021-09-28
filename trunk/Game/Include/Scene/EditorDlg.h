#pragma once

#include "../GameInfo.h"

class CEditorDlg
{
public:
	CEditorDlg();
	~CEditorDlg();

private:
	HWND	m_hDlg;
	int		m_iID;
	bool	m_bOpen;
	class CScene* m_pScene;

public:
	bool IsOpen()	const
	{
		return m_bOpen;
	}

	RECT GetRect()	const
	{
		RECT	rc;
		GetWindowRect(m_hDlg, &rc);
		return rc;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

public:
	bool Init(int iID);
	void Show();
	void Create();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};

