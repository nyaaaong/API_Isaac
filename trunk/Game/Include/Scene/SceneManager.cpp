
#include "SceneManager.h"
#include "Scene.h"
#include "SceneResource.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

CSceneManager* CSceneManager::m_pInst = nullptr;

void CSceneManager::MusicStart()
{
	m_pResource->SetVolume("BGM", 10);
	m_pResource->SetVolume("Effect", 30);

	m_pResource->LoadSound("BGM", true, "Stage1BGM", "Music/Stage1.ogg");
	m_pResource->SoundPlay("Stage1BGM");

	m_pResource->LoadSound("BGM", true, "BossBGM", "Music/Boss.ogg");
	m_pResource->LoadSound("BGM", false, "BossClearBGM", "Music/BossClear.ogg");
}

void CSceneManager::ChangeMusic(EMusic_Type eType)
{
	switch (eType)
	{
	case EMusic_Type::Boss:
		m_pResource->SoundStop("Stage1BGM");
		m_pResource->SoundPlay("BossBGM");
		break;
	case EMusic_Type::BossClear:
		m_pResource->SoundStop("BossBGM");
		m_pResource->SoundPlay("BossClearBGM");
		break;
	}
}

bool CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_DELETE(m_pScene);

		CInput::GetInst()->ClearCallback();

		m_pScene = m_pNextScene;
		m_pNextScene = nullptr;

		return true;
	}

	return false;
}

bool CSceneManager::Init()
{
	m_pScene = new CScene;

	m_pScene->Init();

	return true;
}

bool CSceneManager::Update(float fTime)
{
	if (!m_pScene->IsStart())
		m_pScene->Start();

	m_pScene->Update(fTime);

	return ChangeScene();
}

bool CSceneManager::PostUpdate(float fTime)
{
	m_pScene->PostUpdate(fTime);

	return ChangeScene();
}

bool CSceneManager::Collision(float fTime)
{
	m_pScene->Collision(fTime);

	return ChangeScene();
}

bool CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);

	return ChangeScene();
}

CSceneManager::CSceneManager()	:
	m_pScene(nullptr),
	m_pNextScene(nullptr),
	m_bInputAnimFrameData(false),
	m_bDebug(true)
{
	m_pResource = new CSceneResource;
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pResource);
	SAFE_DELETE(m_pNextScene);
	SAFE_DELETE(m_pScene);
}
