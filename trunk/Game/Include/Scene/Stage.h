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

public:
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
	void BombAnimation();

private:
	void PlayerSound();
	void EnemySound();
	void BossSound();
	void EffectSound();

protected:
	void CreatePlayer(const Vector2& tStartPos);

public:
	// ���� �̵��ϴ� �Լ�. �̵��� ���� Ŭ�������� Ÿ�Գ������� �����ְ�, tPos���� �÷��̾ �̵��� ���� ������ �����ش�.
	template <typename T>
	void MoveRoom(const Vector2& tPos)
	{
		CSceneManager::GetInst()->SetPrevScenePlayerPos(tPos);
		CSceneManager::GetInst()->CreateScene<T>();
	}

public:
	virtual bool Init();
	virtual void Start();

protected:
	CStage();
	virtual ~CStage();
};

