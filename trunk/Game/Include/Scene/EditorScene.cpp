
#include "EditorScene.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "../GameManager.h"
#include "../Input.h"
#include "../Resource/ResourceManager.h"
#include "../Map/Map.h"

CEditorScene::CEditorScene()	:
	m_bStart(false),
	m_iCurRoom(1),
	m_iMaxRoom(20),
	m_eCurObject(OBJ_ROCK),
	m_eState(EEditor_State::Idle)
{
	m_vecMouse.resize(OBJ_MAX - 1);
}

CEditorScene::~CEditorScene()
{
}

bool CEditorScene::Init()
{
	if (!CScene::Init())
		return false;

	for (int i = m_iCurRoom; i <= m_iMaxRoom; ++i)
	{
		CreateMap<CMap>("Room", i);
	}

	SetMap("Room", 1);

	for (int i = OBJ_ROCK; i < OBJ_MAX; ++i)
	{
		// 텍스쳐명
		char	cTextureName[32] = "Object";

		// 번호를 문자로
		char cNum[16] = {};
		sprintf_s(cNum, "%d", i );

		// 텍스쳐명 + 숫자
		strcat_s(cTextureName, cNum);

		CTexture* pTexture = CResourceManager::GetInst()->FindTexture(cTextureName);
		pTexture->SetColorKey(255, 0, 255);

		m_vecMouse[i - 1] = new CUIImage;
		m_vecMouse[i - 1]->SetSize(75.f, 75.f);
		m_vecMouse[i - 1]->SetTexture(pTexture);
	}

	LoadSound();
	LoadAnimationSequence();

	return true;
}

bool CEditorScene::Update(float fTime)
{
	CScene::Update(fTime);

	if (!m_bStart)
	{
		m_bStart = true;

		CInput::GetInst()->SetCallback<CEditorScene>("GameMenu", KS_DOWN, this, &CEditorScene::GameMenu);

		CInput::GetInst()->SetCallback<CEditorScene>("NextObject", KS_DOWN, this, &CEditorScene::NextObject);
		CInput::GetInst()->SetCallback<CEditorScene>("PrevObject", KS_DOWN, this, &CEditorScene::PrevObject);
		CInput::GetInst()->SetCallback<CEditorScene>("SelectObject1", KS_DOWN, this, &CEditorScene::SelectObject1);
		CInput::GetInst()->SetCallback<CEditorScene>("SelectObject2", KS_DOWN, this, &CEditorScene::SelectObject1);
		CInput::GetInst()->SetCallback<CEditorScene>("SelectObject3", KS_DOWN, this, &CEditorScene::SelectObject1);
		CInput::GetInst()->SetCallback<CEditorScene>("SelectObject4", KS_DOWN, this, &CEditorScene::SelectObject1);

		CInput::GetInst()->SetCallback<CEditorScene>("SaveRoom", KS_DOWN, this, &CEditorScene::SaveRoom);
		CInput::GetInst()->SetCallback<CEditorScene>("LoadRoom", KS_DOWN, this, &CEditorScene::LoadRoom);
		CInput::GetInst()->SetCallback<CEditorScene>("ClearRoom", KS_DOWN, this, &CEditorScene::ClearRoom);
		CInput::GetInst()->SetCallback<CEditorScene>("NextRoom", KS_DOWN, this, &CEditorScene::NextRoom);
		CInput::GetInst()->SetCallback<CEditorScene>("PrevRoom", KS_DOWN, this, &CEditorScene::PrevRoom);

		CInput::GetInst()->SetCallback<CEditorScene>("LeftClick", KS_PUSH, this, &CEditorScene::CreateObject);
		CInput::GetInst()->SetCallback<CEditorScene>("RightClick", KS_PUSH, this, &CEditorScene::DeleteObject);
	}

	MouseWindowCheck();

	MouseObjectView();

	EditorTextOut();

	if (m_pCurMouse)
		m_pCurMouse->Update(fTime);

	return true;
}

bool CEditorScene::PostUpdate(float fTime)
{
	CScene::PostUpdate(fTime);

	return true;
}

bool CEditorScene::Render(HDC hDC)
{
	CScene::Render(hDC);

	if (m_pCurMouse)
		m_pCurMouse->Render(CInput::GetInst()->GetMousePos(), hDC);

	return true;
}

void CEditorScene::NextRoom(float fTime)
{
	++m_iCurRoom;

	if (m_iCurRoom > m_iMaxRoom)
		m_iCurRoom = m_iMaxRoom;

	SetMap("Room", m_iCurRoom);
}

void CEditorScene::PrevRoom(float fTime)
{
	--m_iCurRoom;

	if (m_iCurRoom < 1)
		m_iCurRoom = 1;

	SetMap("Room", m_iCurRoom);
}

void CEditorScene::ClearRoom(float fTime)
{
	GetCurrentMap()->Clear();
}

void CEditorScene::SaveRoom(float fTime)
{
}

void CEditorScene::LoadRoom(float fTime)
{
}

void CEditorScene::NextObject(float fTime)
{
	int iCurObj = m_eCurObject + 1;

	if (iCurObj >= OBJ_MAX)
		--iCurObj;

	m_eCurObject = static_cast<EObject>(iCurObj);
}

void CEditorScene::PrevObject(float fTime)
{
	int iCurObj = m_eCurObject - 1;

	if (iCurObj <= OBJ_NONE)
		++iCurObj;

	m_eCurObject = static_cast<EObject>(iCurObj);
}

void CEditorScene::SelectObject1(float fTime)
{
	m_eCurObject = OBJ_ROCK;
}

void CEditorScene::SelectObject2(float fTime)
{
	m_eCurObject = OBJ_IRON;
}

void CEditorScene::SelectObject3(float fTime)
{
	m_eCurObject = OBJ_SPIKE;
}

void CEditorScene::SelectObject4(float fTime)
{
	m_eCurObject = OBJ_POOP;
}

void CEditorScene::CreateObject(float fTime)
{
	GetCurrentMap()->Create(m_eCurObject, CInput::GetInst()->GetMousePos());
}

void CEditorScene::DeleteObject(float fTime)
{
	GetCurrentMap()->Delete(CInput::GetInst()->GetMousePos());
}

void CEditorScene::LoadAnimationSequence()
{
}

void CEditorScene::LoadSound()
{
}

void CEditorScene::GameMenu(float fTime)
{
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
