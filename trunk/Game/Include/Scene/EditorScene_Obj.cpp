
#include "EditorScene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Map/RoomMap.h"

void CEditorScene::NextObject(float fTime)
{
	if (m_bCoolDown)
		return;

	int iCurObj = m_eCurType + 1;

	if (iCurObj > MT_SPAWN)
		--iCurObj;

	m_eCurType = static_cast<EMapObject_Type>(iCurObj);
}

void CEditorScene::PrevObject(float fTime)
{
	if (m_bCoolDown)
		return;

	int iCurObj = m_eCurType - 1;

	if (iCurObj <= MT_NONE)
		++iCurObj;

	m_eCurType = static_cast<EMapObject_Type>(iCurObj);
}

void CEditorScene::SelectObject1(float fTime)
{
	m_eCurType = MT_ROCK;
}

void CEditorScene::SelectObject2(float fTime)
{
	m_eCurType = MT_IRON;
}

void CEditorScene::SelectObject3(float fTime)
{
	m_eCurType = MT_SPIKE;
}

void CEditorScene::SelectObject4(float fTime)
{
	m_eCurType = MT_POOP;
}

void CEditorScene::SelectObject5(float fTime)
{
	m_eCurType = MT_SPAWN;
}

void CEditorScene::CreateObject(float fTime)
{
	if (m_bCoolDown)
		return;

	if (m_eCurType != MT_SPAWN)
		GetCurrentMap()->Create(this, m_eCurType, CInput::GetInst()->GetMousePos());

	else if (m_eCurType == MT_SPAWN)
	{
		RECT tRC = {};

		if (CInput::GetInst()->GetKeyDown("EditorLeftClick"))
		{
			m_tMouseStartPos = CInput::GetInst()->GetMousePos();

			if (m_tMouseStartPos.x < GetFieldLT().x)
				m_tMouseStartPos.x = GetFieldLT().x;

			if (m_tMouseStartPos.y < GetFieldLT().y)
				m_tMouseStartPos.y = GetFieldLT().y;
		}

		if (CInput::GetInst()->GetKeyPush("EditorLeftClick"))
		{
			m_tMouseEndPos = CInput::GetInst()->GetMousePos();

			if (m_tMouseEndPos.x > GetFieldRB().x)
				m_tMouseEndPos.x = GetFieldRB().x;

			if (m_tMouseEndPos.y > GetFieldRB().y)
				m_tMouseEndPos.y = GetFieldRB().y;

			tRC = { static_cast<long>(m_tMouseStartPos.x), static_cast<long>(m_tMouseStartPos.y), static_cast<long>(m_tMouseEndPos.x), static_cast<long>(m_tMouseEndPos.y) };

			if (m_tMouseStartPos != m_tMouseEndPos)
				FrameRect(CGameManager::GetInst()->GetWindowDC(), &tRC, CGameManager::GetInst()->GetGreenBrush());
		}
	}
}

void CEditorScene::DeleteObject(float fTime)
{
	if (m_bCoolDown)
		return;

	if (m_eCurType != MT_SPAWN)
		GetCurrentMap()->Delete(this, CInput::GetInst()->GetMousePos());

	else if (m_eCurType == MT_SPAWN)
		GetCurrentMap()->DeleteSpawn(this, CInput::GetInst()->GetMousePos());
}