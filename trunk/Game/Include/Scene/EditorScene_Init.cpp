
#include "EditorScene.h"
#include "../Input.h"
#include "../Resource/ResourceManager.h"

void CEditorScene::CreateMouseCursor()
{
	for (int i = OBJ_ROCK; i < OBJ_MAX; ++i)
	{
		// 텍스쳐명
		char	cTextureName[32] = "Object";

		// 번호를 문자로
		char cNum[16] = {};
		sprintf_s(cNum, "%d", i);

		// 텍스쳐명 + 숫자
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
}