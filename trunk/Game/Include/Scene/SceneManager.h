
#pragma once

#include "../GameInfo.h"
#include "Scene.h"
#include "../Object/Character.h"
#include "../Object/ObjManager.h"

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene;
	Vector2	m_tPrevScenePlayerPos; // ���� �濡�� ��� ������ ���� ��� �ߴ���
	class CSceneResource* m_pResource;
	bool	m_bInputAnimFrameData; // �ߺ��� �ִϸ��̼� �������� �ִ°��� �����ϱ� ���� ����

public:
	bool IsInputAnimFrameData()	const
	{
		return m_bInputAnimFrameData;
	}
	
	CScene* GetScene()	const
	{
		return m_pScene;
	}

public:
	void InputAnimFrameData()
	{
		m_bInputAnimFrameData = true;
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
		CCharacter* pPlayer = dynamic_cast<CCharacter*>(m_pScene->GetPlayer());

		if (pPlayer)
			CObjManager::GetInst()->PushPlayerInfo(pPlayer->GetInfo());

		m_pNextScene = new T;

		if (!m_pNextScene->Init())
		{
			SAFE_DELETE(m_pNextScene);
			return false;
		}

		return true;
	}
};

