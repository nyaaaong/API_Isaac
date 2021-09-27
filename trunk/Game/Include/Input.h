#pragma once

#include "GameInfo.h"

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
	HWND	m_hWnd;

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
	void UpdatEKeyState();
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

