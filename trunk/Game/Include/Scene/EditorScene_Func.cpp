
#include "EditorScene.h"
#include "MainMenu.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "../Input.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

void CEditorScene::LoadAnimationSequence()
{
}

void CEditorScene::LoadSound()
{
}

void CEditorScene::GameMenu(float fTime)
{
	if (m_bCoolDown)
		return;

	CGameManager::GetInst()->SetTitleUpdate(true);
	CSceneManager::GetInst()->CreateScene<CMainMenu>();
}

void CEditorScene::MouseWindowCheck()
{
	HWND	hWnd = CGameManager::GetInst()->GetWindowHandle();
	CInput* pInst = CInput::GetInst();

	RECT	rc;
	GetClientRect(hWnd, &rc);

	POINT	tMouse;
	GetCursorPos(&tMouse);
	ScreenToClient(hWnd, &tMouse);

	if (rc.left <= tMouse.x && tMouse.x <= rc.right &&
		rc.top <= tMouse.y && tMouse.y <= rc.bottom)
	{
		if (pInst->IsShowCursor())
			pInst->SetShowCursor(false);
	}

	else
	{
		if (!pInst->IsShowCursor())
			pInst->SetShowCursor(true);
	}
}

void CEditorScene::MouseObjectView()
{
	m_pCurMouse = m_vecMouse[m_eCurType - 1];
}

void CEditorScene::MouseSetBox()
{
	// ��ġ ������ �����̸� �ʷϻ� �ڽ���, �ƴϸ� ������ �ڽ��� ����ϰ� �Ѵ�.
	Vector2	tMousePos = CInput::GetInst()->GetMousePos();
	Vector2	tObjSize = Vector2(75.f, 75.f);

	bool bSetPossible = GetCurrentMap()->IsSetObj(tMousePos);

	HBRUSH	hBrush = 0;
	RECT tRC = { static_cast<long>(tMousePos.x), static_cast<long>(tMousePos.y), static_cast<long>(tMousePos.x + tObjSize.x), static_cast<long>(tMousePos.y + tObjSize.y) };

	if (!m_bCoolDown)
	{
		if (bSetPossible)
			hBrush = CGameManager::GetInst()->GetGreenBrush();

		else
			hBrush = CGameManager::GetInst()->GetRedBrush();
	}

	else
		hBrush = CGameManager::GetInst()->GetRedBrush();

	FrameRect(CGameManager::GetInst()->GetWindowDC(), &tRC, hBrush);
}

void CEditorScene::EditorTextOut()
{
	memset(m_cTitleText, 0, sizeof(char) * 256);
	memset(m_cStateText, 0, sizeof(char) * 32);
	memset(m_cMousePosText, 0, sizeof(char) * 64);

	switch (m_eState)
	{
	case EEditor_State::Idle:
		strcpy_s(m_cStateText, "��� �ߡ�");
		break;
	case EEditor_State::Saved:
		strcpy_s(m_cStateText, "���� �Ϸᡡ");
		break;
	case EEditor_State::Loaded:
		strcpy_s(m_cStateText, "�ҷ����� �Ϸᡡ");
		break;
	}

	sprintf_s(m_cTitleText, "The Binding of Isaac��[������ ���]���� : %d / %d������ : ", m_iCurRoom, m_iMaxRoomCount);
	strcat_s(m_cTitleText, m_cStateText);

	sprintf_s(m_cMousePosText, "�����콺 ��ġ - X : %.2f��Y : %.2f", CInput::GetInst()->GetMousePos().x, CInput::GetInst()->GetMousePos().y);
	strcat_s(m_cTitleText, m_cMousePosText);

	SetWindowTextA(CGameManager::GetInst()->GetWindowHandle(), m_cTitleText);
}

void CEditorScene::SaveFullPath(const char* cFullPath)
{
	CScene::SaveFullPath(cFullPath);

	m_eState = EEditor_State::Saved;
}

void CEditorScene::LoadFullPath(const char* cFullPath)
{
	CScene::LoadFullPath(cFullPath);

	m_eState = EEditor_State::Loaded;

	CMapManager::GetInst()->SetMap(this, 1);
	m_iCurRoom = 1;
}
