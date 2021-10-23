
#pragma once

#include "../GameInfo.h"
#include "Scene.h"
#include "../Object/Player.h"
#include "../Object/ObjManager.h"

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene;
	Vector2	m_tPrevScenePlayerPos; // ���� �濡�� ��� ������ ���� ��� �ߴ���
	class CSceneResource* m_pResource;
	bool	m_bInputAnimFrameData; // �ߺ��� �ִϸ��̼� �������� �ִ°��� �����ϱ� ���� ����
	bool	m_bDebug;

public:
	bool IsDebug()	const
	{
		return m_bDebug;
	}

	bool IsInputAnimFrameData()	const
	{
		return m_bInputAnimFrameData;
	}
	
	CScene* GetScene()	const
	{
		return m_pScene;
	}

	CScene* GetNextScene()	const
	{
		return m_pNextScene;
	}

public:
	void SetDebug()
	{
		m_bDebug = !m_bDebug;
	}

	void InputAnimFrameData()
	{
		m_bInputAnimFrameData = true;
	}

public:
	void MusicStart();
	void ChangeMusic(EMusic_Type eType);

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
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pScene->GetPlayer());

		if (pPlayer)
			CObjManager::GetInst()->PushPlayerInfo(pPlayer);

		m_pNextScene = new T;

		if (!m_pNextScene->Init())
		{
			SAFE_DELETE(m_pNextScene);
			return false;
		}

		return true;
	}
};

