#pragma once

#include "Scene.h"
#include "SceneManager.h"

class CStage :
    public CScene
{
	friend class CSceneManager;

protected:
	class CPlayerHUD* m_pPlayerHUD;
	int		m_iStage;
	int		m_bFirstRoom;

public:
	void FirstRoom()
	{
		m_bFirstRoom = true;
	}

	void SetStage(int iStage)
	{
		m_iStage = iStage;
	}

public:
	int GetStage()	const
	{
		return m_iStage;
	}

private:
	void LoadAnimationSequence();
	void LoadSound();
	void CreatePrototypes();

private:
	void PlayerAnimation();
	void EnemyAnimation();
	void BossAnimation();
	void TearAnimation();

private:
	void PlayerSound();
	void EnemySound();
	void BossSound();
	void EffectSound();

protected:
	void CreatePlayer(const Vector2& tStartPos);

protected:
	// 방을 이동하는 함수. 이동할 방의 클래스명을 타입네임으로 적어주고, tPos에는 플레이어가 이동할 문의 방향을 적어준다.
	template <typename T>
	void MoveRoom(const Vector2& tPos)
	{
		CSceneManager::GetInst()->SetPrevScenePlayerPos(tPos);
		CSceneManager::GetInst()->CreateScene<T>();
	}

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	CStage();
	virtual ~CStage();
};

