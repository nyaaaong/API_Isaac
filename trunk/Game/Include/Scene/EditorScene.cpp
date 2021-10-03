
#include "EditorScene.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

CEditorScene::CEditorScene()	:
	m_iCurRoom(1),
	m_eCurObject(OBJ_ROCK),
	m_eState(EEditor_State::Idle),
	m_fTimer(0.f),
	m_fMaxTimer(5.f),
	m_bCoolDown(false),
	m_cTitleText{},
	m_cStateText{},
	m_cFPSText{}
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

	for (int i = m_iCurRoom; i <= m_iMaxRoomCount; ++i)
	{
		CreateRoomMap<CRoomMap>("Room", i);
	}

	SetMap("Room", 1);

	CreateMouseCursor();

	LoadSound();
	LoadAnimationSequence();

	return true;
}

bool CEditorScene::Update(float fTime)
{
	CScene::Update(fTime);

	if (m_eState == EEditor_State::Saved ||
		m_eState == EEditor_State::Loaded)
	{
		m_bCoolDown = true;
		m_fTimer += fTime;

		if (m_fTimer >= m_fMaxTimer)
		{
			m_bCoolDown = false;
			m_fTimer = 0.f;
			m_eState = EEditor_State::Idle;
		}
	}

	MouseWindowCheck();
	MouseObjectView();
	MouseSetBox();
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
