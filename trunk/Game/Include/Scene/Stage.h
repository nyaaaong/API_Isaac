#pragma once
#include "Scene.h"
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
	void LoadBGM();
	void CreateObjects();
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

public:
	virtual bool Init();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	CStage();
	virtual ~CStage();
};
