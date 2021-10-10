
#pragma once

#include "../GameInfo.h"
#include "Scene.h"

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene;
	Vector2	m_tPrevScenePlayerPos; // 이전 방에서 어느 방향의 문을 사용 했는지
	class CSceneResource* m_pResource;

public:
	CScene* GetScene()	const
	{
		return m_pScene;
	}

public:
	void MusicStart();

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
	const Vector2& GetPrevScenePlayerPos()	const
	{
		return m_tPrevScenePlayerPos;
	}

public:
	void SetPrevScenePlayerPos(const Vector2& tPos)
	{
		m_tPrevScenePlayerPos = tPos;
	}

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

