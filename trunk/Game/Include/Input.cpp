#include "Input.h"

CInput* CInput::m_pInst = nullptr;

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	// ----------- MainMenu ----------- 

	CreateKey("MenuGameStart1", VK_RETURN);
	CreateKey("MenuGameStart2", VK_SPACE);
	CreateKey("MenuGameEditor", 'E');
	SetCtrlKey("MenuGameEditor", true);
	CreateKey("MenuGameExit", VK_ESCAPE);

	// ----------- Editor ----------- 

	CreateKey("EditorGameMenu", VK_BACK);
	SetCtrlKey("EditorGameMenu", true);

	CreateKey("EditorNextObject", 'E');
	CreateKey("EditorPrevObject", 'Q');
	CreateKey("EditorSelectObject1", '1'); 
	CreateKey("EditorSelectObject2", '2'); 
	CreateKey("EditorSelectObject3", '3'); 
	CreateKey("EditorSelectObject4", '4');
	CreateKey("EditorSelectObject5", '5');

	CreateKey("EditorSaveRoom", 'S');
	SetCtrlKey("EditorSaveRoom", true);
	CreateKey("EditorLoadRoom", 'L');
	SetCtrlKey("EditorLoadRoom", true);
	CreateKey("EditorClearRoom", 'N');
	SetCtrlKey("EditorClearRoom", true);
	CreateKey("EditorNextRoom", 'D');
	CreateKey("EditorPrevRoom", 'A');

	CreateKey("EditorLeftClick", VK_LBUTTON);
	CreateKey("EditorRightClick", VK_RBUTTON);

	// ----------- Player ----------- 

	CreateKey("PlayerMoveUp", 'W');
	CreateKey("PlayerMoveDown", 'S');
	CreateKey("PlayerMoveLeft", 'A');
	CreateKey("PlayerMoveRight", 'D');

	CreateKey("PlayerFireUp", VK_UP);
	CreateKey("PlayerFireDown", VK_DOWN);
	CreateKey("PlayerFireLeft", VK_LEFT);
	CreateKey("PlayerFireRight", VK_RIGHT);

	CreateKey("PlayerBomb", 'E');

	CreateKey("PlayerNextRoom", 'O');

	return true;
}

void CInput::Update(float fTime)
{
	UpdateKeyState();
	UpdateMouse(fTime);
	UpdateKeyInfo(fTime);
}

bool CInput::GetKeyDown(const std::string& strName)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (!pInfo)
		return false;

	return m_vecKeyState[pInfo->tState.iKey].bState[KS_DOWN];
}

bool CInput::GetKeyPush(const std::string& strName)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (!pInfo)
		return false;

	return m_vecKeyState[pInfo->tState.iKey].bState[KS_PUSH];
}

bool CInput::GetKeyUp(const std::string& strName)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (!pInfo)
		return false;

	return m_vecKeyState[pInfo->tState.iKey].bState[KS_UP];
}

void CInput::ClearCallback()
{
	std::unordered_map<std::string, KeyInfo*>::iterator	iter = m_mapInfo.begin();
	std::unordered_map<std::string, KeyInfo*>::iterator	iterEnd = m_mapInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < KS_MAX; ++i)
		{
			iter->second->Callback[i] = nullptr;
		}
	}
}

bool CInput::CreateKey(const std::string& strName, int iKey)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (pInfo)
		return false;

	pInfo = new KeyInfo;

	pInfo->strName = strName;
	pInfo->tState.iKey = iKey;

	m_mapInfo.insert(std::make_pair(strName, pInfo));

	bool bAdd = false;

	size_t iSize = m_vecAddKey.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecAddKey[i] == iKey)
		{
			bAdd = true;
			break;
		}
	}

	if (!bAdd)
		m_vecAddKey.push_back(iKey);

	return true;
}

bool CInput::SetCtrlKey(const std::string& strName, bool bState)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (!pInfo)
		return false;

	pInfo->bCtrl = bState;

	return true;
}

bool CInput::SetAltKey(const std::string& strName, bool bState)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (!pInfo)
		return false;

	pInfo->bAlt = bState;

	return true;
}

bool CInput::SetShiftKey(const std::string& strName, bool bState)
{
	KeyInfo* pInfo = FindKeyInfo(strName);

	if (!pInfo)
		return false;

	pInfo->bShift = bState;

	return true;
}

KeyInfo* CInput::FindKeyInfo(const std::string& strName)
{
	std::unordered_map<std::string, KeyInfo*>::iterator	iter = m_mapInfo.find(strName);

	if (iter == m_mapInfo.end())
		return nullptr;

	return iter->second;
}

void CInput::UpdateMouse(float fTime)
{
	POINT	tMouse;

	GetCursorPos(&tMouse);
	ScreenToClient(m_hWnd, &tMouse);

	Vector2	tPos;
	tPos.x = static_cast<float>(tMouse.x);
	tPos.y = static_cast<float>(tMouse.y);

	m_tMouseMove = tPos - m_tMousePos;
	m_tMousePos = tPos;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_bMouseDown && !m_bMousePush)
		{
			m_bMouseDown = true;
			m_bMousePush = true;
		}

		else
			m_bMouseDown = false;
	}

	else if (m_bMousePush)
	{
		m_bMouseDown = false;
		m_bMousePush = false;
		m_bMouseUp = true;
	}

	else if (m_bMouseUp)
		m_bMouseUp = false;
}

void CInput::UpdateKeyState()
{
	size_t iSize = m_vecAddKey.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		int iKey = m_vecAddKey[i];

		if (GetAsyncKeyState(iKey) & 0x8000)
		{
			if (!m_vecKeyState[iKey].bState[KS_DOWN] &&
				!m_vecKeyState[iKey].bState[KS_PUSH])
			{
				m_vecKeyState[iKey].bState[KS_DOWN] = true;
				m_vecKeyState[iKey].bState[KS_PUSH] = true;
			}

			else
				m_vecKeyState[iKey].bState[KS_DOWN] = false;
		}

		else if (m_vecKeyState[iKey].bState[KS_PUSH])
		{
			m_vecKeyState[iKey].bState[KS_PUSH] = false;
			m_vecKeyState[iKey].bState[KS_DOWN] = false;
			m_vecKeyState[iKey].bState[KS_UP] = true;
		}

		else if (m_vecKeyState[iKey].bState[KS_UP])
			m_vecKeyState[iKey].bState[KS_UP] = false;
	}

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_bCtrl = true;

	else
		m_bCtrl = false;

	if (GetAsyncKeyState(VK_MENU) & 0x8000)
		m_bAlt = true;

	else
		m_bAlt = false;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_bShift = true;

	else
		m_bShift = false;
}

void CInput::UpdateKeyInfo(float fTime)
{
	std::unordered_map<std::string, KeyInfo*>::iterator	iter = m_mapInfo.begin();
	std::unordered_map<std::string, KeyInfo*>::iterator	iterEnd = m_mapInfo.end();

	int iKey = 0;

	for (; iter != iterEnd; ++iter)
	{
		iKey = iter->second->tState.iKey;

		if (m_vecKeyState[iKey].bState[KS_DOWN] &&
			iter->second->bCtrl == m_bCtrl &&
			iter->second->bAlt == m_bAlt &&
			iter->second->bShift == m_bShift)
		{
			if (iter->second->Callback[KS_DOWN])
				iter->second->Callback[KS_DOWN](fTime);
		}

		if (m_vecKeyState[iKey].bState[KS_PUSH] &&
			iter->second->bCtrl == m_bCtrl &&
			iter->second->bAlt == m_bAlt &&
			iter->second->bShift == m_bShift)
		{
			if (iter->second->Callback[KS_PUSH])
				iter->second->Callback[KS_PUSH](fTime);
		}

		if (m_vecKeyState[iKey].bState[KS_UP] &&
			iter->second->bCtrl == m_bCtrl &&
			iter->second->bAlt == m_bAlt &&
			iter->second->bShift == m_bShift)
		{
			if (iter->second->Callback[KS_UP])
				iter->second->Callback[KS_UP](fTime);
		}
	}
}

CInput::CInput()	:
	m_bCtrl(false),
	m_bAlt(false),
	m_bShift(false),
	m_hWnd(0),
	m_bMouseDown(false),
	m_bMousePush(false),
	m_bMouseUp(false),
	m_bShowCursor(true)
{
	m_vecKeyState.resize(KEY_COUNT_MAX);

	for (int i = 0; i < KEY_COUNT_MAX; ++i)
	{
		m_vecKeyState[i].iKey = i;
	}
}

CInput::~CInput()
{
	std::unordered_map<std::string, KeyInfo*>::iterator	iter = m_mapInfo.begin();
	std::unordered_map<std::string, KeyInfo*>::iterator	iterEnd = m_mapInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}
