
#include "EditorScene.h"
#include "EditorDlg.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "../Input.h"

CEditorScene::CEditorScene()	:
	m_bStart(false),
	m_pDlg(nullptr)
{
}

CEditorScene::~CEditorScene()
{
	SAFE_DELETE(m_pDlg);
}

bool CEditorScene::Init()
{
	LoadSound();
	LoadAnimationSequence();

	m_pDlg = new CEditorDlg;

	m_pDlg->SetScene(this);
	m_pDlg->Init(IDD_DIALOG_EDITOR);

	return true;
}

bool CEditorScene::Update(float fTime)
{
	if (!m_bStart)
	{
		m_bStart = true;
		CInput::GetInst()->SetCallback<CEditorScene>("Editor", KS_DOWN, this, &CEditorScene::OnEditor);
		CInput::GetInst()->SetCallback<CEditorScene>("GameMenu", KS_DOWN, this, &CEditorScene::GameMenu);
	}

	return true;
}

bool CEditorScene::PostUpdate(float fTime)
{
	return true;
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

void CEditorScene::OnEditor(float fTime)
{
}
