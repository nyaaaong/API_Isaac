
#include "EditorScene.h"
#include "MainMenu.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "../Input.h"

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
	m_pCurMouse = m_vecMouse[m_eCurObject - 1];
}

void CEditorScene::EditorTextOut()
{
	TCHAR	cText[32] = {};

	wsprintf(cText, TEXT("Room : %d / %d"), m_iCurRoom, m_iMaxRoom);

	TextOut(CGameManager::GetInst()->GetWindowDC(), 0, 0, cText, lstrlen(cText));

	memset(cText, 0, sizeof(TCHAR) * 32);

	lstrcpy(cText, TEXT("상태 : "));

	switch (m_eState)
	{
	case EEditor_State::Idle:
		lstrcat(cText, TEXT("대기 중"));
		break;
	case EEditor_State::Saved:
		lstrcat(cText, TEXT("저장 완료"));
		break;
	case EEditor_State::Loaded:
		lstrcat(cText, TEXT("불러오기 완료"));
		break;
	}

	TextOut(CGameManager::GetInst()->GetWindowDC(), 0, 20, cText, lstrlen(cText));
}

void CEditorScene::Save(const char* cFullPath)
{
	CScene::Save(cFullPath);

	m_eState = EEditor_State::Saved;
}

void CEditorScene::Load(const char* cFullPath)
{
	CScene::Load(cFullPath);

	m_eState = EEditor_State::Loaded;

	SetMap("Room", 1);
	m_iCurRoom = 1;
}
