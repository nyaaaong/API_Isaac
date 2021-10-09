
#include "SceneManager.h"
#include "Scene.h"
#include "../Input.h"
#include "../Map/RoomMap.h"

CSceneManager* CSceneManager::m_pInst = nullptr;

bool CSceneManager::IsPlayRoom(int iRoomNum)
{
	size_t iSize = m_vecPlayRoom.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecPlayRoom[i]->GetRoomNumber() == iRoomNum)
			return true;
	}

	return false;
}

bool CSceneManager::PushPlayRoom(CRoomMap* pRoom)
{
	size_t iSize = m_vecPlayRoom.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecPlayRoom[i] == pRoom)
			return false;
	}

	m_vecPlayRoom.push_back(pRoom);

	return true;
}

bool CSceneManager::PushPlaySpecialRoom(CRoomMap* pSpecialRoom)
{
	size_t iSize = m_vecPlaySpecialRoom.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecPlaySpecialRoom[i] == pSpecialRoom)
			return false;
	}

	m_vecPlaySpecialRoom.push_back(pSpecialRoom);

	return true;
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
	m_pNextScene(nullptr)
{
	m_vecPlayRoom.reserve(3);
	m_vecPlaySpecialRoom.reserve(3);
}

CSceneManager::~CSceneManager()
{
	{
		size_t iSize = m_vecPlaySpecialRoom.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			SAFE_DELETE(m_vecPlaySpecialRoom[i]);
		}

		m_vecPlaySpecialRoom.clear();
	}

	{
		size_t iSize = m_vecPlayRoom.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			SAFE_DELETE(m_vecPlayRoom[i]);
		}

		m_vecPlayRoom.clear();
	}

	SAFE_DELETE(m_pNextScene);
	SAFE_DELETE(m_pScene);
}
