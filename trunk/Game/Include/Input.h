#pragma once

#include "GameInfo.h"
#include "UI/UIImage.h"

struct KeyState
{
	int		iKey;
	bool	bState[KS_MAX];

	KeyState()	:
		iKey(0),
		bState{}
	{}
};

struct KeyInfo
{
	std::string	strName;
	KeyState	tState;
	std::function<void(float)>	Callback[KS_MAX];
	bool	bCtrl;
	bool	bAlt;
	bool	bShift;

	KeyInfo() :
		bCtrl(false),
		bAlt(false),
		bShift(false)
	{}
};

class CInput
{
private:
	std::unordered_map<std::string, KeyInfo*>	m_mapInfo;
	std::vector<KeyState>	m_vecKeyState;
	std::vector<int>		m_vecAddKey;
	bool	m_bCtrl;
	bool	m_bAlt;
	bool	m_bShift;
	Vector2	m_tMousePos;
	Vector2	m_tMouseMove;
	HWND	m_hWnd;
	bool	m_bMouseDown;
	bool	m_bMousePush;
	bool	m_bMouseUp;
	bool	m_bShowCursor;

public:
	bool IsShowCursor()	const
	{
		return m_bShowCursor;
	}

	bool GetMouseDown()	const
	{
		return m_bMouseDown;
	}

	bool GetMousePush()	const
	{
		return m_bMousePush;
	}

	bool GetMouseUp()	const
	{
		return m_bMouseUp;
	}

	const Vector2& GetMousePos()	const
	{
		return m_tMousePos;
	}

	const Vector2& GetMouseMove()	const
	{
		return m_tMouseMove;
	}

public:
	void SetShowCursor(bool bCursor)
	{
		if (bCursor)
		{
			if (!m_bShowCursor)
			{
				m_bShowCursor = true;
				ShowCursor(TRUE);
			}
		}

		else
		{
			if (m_bShowCursor)
			{
				m_bShowCursor = false;
				ShowCursor(FALSE);
			}
		}
	}

public:
	void ClearCallback();

public:
	bool CreateKey(const std::string& strName, int iKey);
	bool SetCtrlKey(const std::string& strName, bool bState);
	bool SetAltKey(const std::string& strName, bool bState);
	bool SetShiftKey(const std::string& strName, bool bState);

private:
	KeyInfo* FindKeyInfo(const std::string& strName);

public:
	bool Init(HWND hWnd);
	void Update(float fTime);

private:
	void UpdateMouse(float fTime);
	void UpdateKeyState();
	void UpdateKeyInfo(float fTime);

private:
	static CInput* m_pInst;

public:
	static CInput* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CInput;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	CInput();
	~CInput();

public:
	template <typename T>
	void SetCallback(const std::string& strName, EKeyState eState, T* pObj, void(T::* pFunc)(float))
	{
		KeyInfo* pInfo = FindKeyInfo(strName);

		if (pInfo)
			pInfo->Callback[eState] = std::bind(pFunc, pObj, std::placeholders::_1);
	}
};

