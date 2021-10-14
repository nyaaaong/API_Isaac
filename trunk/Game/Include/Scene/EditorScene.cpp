
#include "EditorScene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Map/RoomMap.h"
#include "../Map/MapManager.h"

CEditorScene::CEditorScene()	:
	m_iCurRoom(1),
	m_eCurType(MT_ROCK),
	m_eState(EEditor_State::Idle),
	m_fTimer(0.f),
	m_fMaxTimer(3.f),
	m_bCoolDown(false),
	m_cTitleText{},
	m_cStateText{},
	m_cMousePosText{}
{
	m_vecMouse.resize(MT_SPAWN - 1);

	CMapManager::GetInst()->SetEditorScene(true);
	SetEditor(true);
}

CEditorScene::~CEditorScene()
{
	CMapManager::GetInst()->RoomMapClear();

}

bool CEditorScene::Init()
{
	if (!CScene::Init())
		return false;

	for (int i = m_iCurRoom; i <= m_iMaxRoomCount; ++i)
	{
		CMapManager::GetInst()->CreateRoomMap(this, "Room", i);
	}

	CMapManager::GetInst()->SetMap(this, 1);

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

	if (m_eCurType != MT_SPAWN)
	{
		MouseWindowCheck();
		MouseObjectView();
		MouseSetBox();
	}

	else if (m_eCurType == MT_SPAWN)
	{
		if (!CInput::GetInst()->IsShowCursor())
			CInput::GetInst()->SetShowCursor(true);

		m_pCurMouse = nullptr;
	}

	EditorTextOut();

	if (m_pCurMouse)
		m_pCurMouse->Update(fTime);

	return true;
}

bool CEditorScene::PostUpdate(float fTime)
{
	CScene::PostUpdate(fTime);

	if (CInput::GetInst()->GetKeyUp("EditorLeftClick"))
	{
		m_tMouseEndPos = CInput::GetInst()->GetMousePos();

		if (m_tMouseEndPos.x > GetFieldRB().x)
			m_tMouseEndPos.x = GetFieldRB().x;

		if (m_tMouseEndPos.y > GetFieldRB().y)
			m_tMouseEndPos.y = GetFieldRB().y;

		RECT tRC = { static_cast<long>(m_tMouseStartPos.x), static_cast<long>(m_tMouseStartPos.y), static_cast<long>(m_tMouseEndPos.x), static_cast<long>(m_tMouseEndPos.y) };

		if (m_tMouseStartPos.x < m_tMouseEndPos.x && m_tMouseStartPos.y < m_tMouseEndPos.y && m_tMouseStartPos != m_tMouseEndPos)
		{
			FrameRect(CGameManager::GetInst()->GetWindowDC(), &tRC, CGameManager::GetInst()->GetGreenBrush());

			GetCurrentMap()->Create(m_eCurType, m_tMouseStartPos, m_tMouseEndPos - m_tMouseStartPos);
		}
	}

	return true;
}

bool CEditorScene::Render(HDC hDC)
{
	CScene::Render(hDC);

	if (m_pCurMouse)
		m_pCurMouse->Render(CInput::GetInst()->GetMousePos(), hDC);

	return true;
}
