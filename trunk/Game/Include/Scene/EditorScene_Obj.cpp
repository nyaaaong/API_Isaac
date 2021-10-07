
#include "EditorScene.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

void CEditorScene::NextObject(float fTime)
{
	if (m_bCoolDown)
		return;

	int iCurObj = m_eCurType + 1;

	if (iCurObj >= MT_MAX)
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

void CEditorScene::CreateObject(float fTime)
{
	if (m_bCoolDown)
		return;

	GetCurrentMap()->Create(m_eCurType, CInput::GetInst()->GetMousePos());
}

void CEditorScene::DeleteObject(float fTime)
{
	if (m_bCoolDown)
		return;

	GetCurrentMap()->Delete(CInput::GetInst()->GetMousePos());
}