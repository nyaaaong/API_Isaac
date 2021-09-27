
#pragma once

#include "../GameInfo.h"
#include "Scene.h"

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene;

public:
	CScene* GetScene()	const
	{
		return m_pScene;
	}

private:
	bool ChangeScene();

public:
	bool Init();
	bool Update(float fTime);
	bool PostUpdate(float fTime);
	bool Collision(float fTime);
	bool Render(HDC hDC);

private:
	static CSceneManager* m_pInst;

public:
	static CSceneManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CSceneManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	CSceneManager();
	~CSceneManager();

public:
	template <typename T>
	bool CreateScene()
	{
		m_pNextScene = new T;

		if (!m_pNextScene->Init())
		{
			SAFE_DELETE(m_pNextScene);
			return false;
		}

		return true;
	}
};

