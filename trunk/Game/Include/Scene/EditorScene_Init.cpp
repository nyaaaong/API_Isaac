
#include "EditorScene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Resource/ResourceManager.h"

void CEditorScene::CreateMouseCursor()
{
	for (int i = OBJ_ROCK; i < OBJ_MAX; ++i)
	{
		// �ؽ��ĸ�
		char	cTextureName[32] = "Object";

		// ��ȣ�� ���ڷ�
		char cNum[16] = {};
		sprintf_s(cNum, "%d", i);

		// �ؽ��ĸ� + ����
		strcat_s(cTextureName, cNum);

		CTexture* pTexture = CResourceManager::GetInst()->FindTexture(cTextureName);
		pTexture->SetColorKey(255, 0, 255);

		m_vecMouse[i - 1] = new CUIImage;
		m_vecMouse[i - 1]->SetSize(75.f, 75.f);
		m_vecMouse[i - 1]->SetTexture(pTexture);
	}
}

void CEditorScene::Start()
{
	CScene::Start();

	// Ÿ��Ʋ�ٿ� �� ������ �ֱ����� ���ӸŴ������� ������ ���� �ʴ´�.
	CGameManager::GetInst()->SetTitleUpdate(false);

	CInput::GetInst()->SetShowCursor(false);

	CInput::GetInst()->SetCallback<CEditorScene>("EditorGameMenu", KS_DOWN, this, &CEditorScene::GameMenu);

	CInput::GetInst()->SetCallback<CEditorScene>("EditorNextObject", KS_DOWN, this, &CEditorScene::NextObject);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorPrevObject", KS_DOWN, this, &CEditorScene::PrevObject);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorSelectObject1", KS_DOWN, this, &CEditorScene::SelectObject1);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorSelectObject2", KS_DOWN, this, &CEditorScene::SelectObject1);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorSelectObject3", KS_DOWN, this, &CEditorScene::SelectObject1);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorSelectObject4", KS_DOWN, this, &CEditorScene::SelectObject1);

	CInput::GetInst()->SetCallback<CEditorScene>("EditorSaveRoom", KS_DOWN, this, &CEditorScene::SaveRoom);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorLoadRoom", KS_DOWN, this, &CEditorScene::LoadRoom);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorClearRoom", KS_DOWN, this, &CEditorScene::ClearRoom);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorNextRoom", KS_DOWN, this, &CEditorScene::NextRoom);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorPrevRoom", KS_DOWN, this, &CEditorScene::PrevRoom);

	CInput::GetInst()->SetCallback<CEditorScene>("EditorLeftClick", KS_PUSH, this, &CEditorScene::CreateObject);
	CInput::GetInst()->SetCallback<CEditorScene>("EditorRightClick", KS_PUSH, this, &CEditorScene::DeleteObject);
}