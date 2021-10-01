
#include "EditorScene.h"
#include "../Input.h"
#include "../Map/Map.h"

void CEditorScene::NextObject(float fTime)
{
	if (m_bCoolDown)
		return;

	int iCurObj = m_eCurObject + 1;

	if (iCurObj >= OBJ_MAX)
		--iCurObj;

	m_eCurObject = static_cast<EObject>(iCurObj);
}

void CEditorScene::PrevObject(float fTime)
{
	if (m_bCoolDown)
		return;

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
	if (m_bCoolDown)
		return;

	GetCurrentMap()->Create(m_eCurObject, CInput::GetInst()->GetMousePos());
}

void CEditorScene::DeleteObject(float fTime)
{
	if (m_bCoolDown)
		return;

	GetCurrentMap()->Delete(CInput::GetInst()->GetMousePos());
}