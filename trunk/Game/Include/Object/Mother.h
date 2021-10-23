#pragma once

#include "MonsterBase.h"

class CMother :
	public CMonsterBase
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CMother();
	CMother(const CMother& obj);
	virtual ~CMother();

private:
	float	m_fPatternTimer;
	float	m_fPatternTimerMax;
	float	m_fPatternDelay;
	float	m_fPlayerPrevHP;
	bool	m_bFirstPattern; // 처음엔 무조건 발동하는 패턴
	bool	m_bProgress;	// 패턴이 진행중이라면 true
	class CMotherLeg* m_pLeg;
	class CMotherDoor* m_pDoor[DD_MAX];
	CCharacter* m_pPlayer;
	std::vector<std::function<void()>>	m_vecPatternFunc;
	float	m_fFirstDelay;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CMother* Clone();

public:
	void SetPart(class CMotherLeg* pLeg, class CMotherDoor** pDoor);
	void SetProgress(bool bIsProgress)
	{
		m_bProgress = bIsProgress;
	}

private:
	void MotherPlayerHPUpdater();
	void MotherPattern(float fTime);
	void EnableRandomDoor(EMotherDoor_Type eType);
	void AddPatternTimer(float fValue);

private:
	void SpawnLeg();
	void SpawnEye();
	void SpawnSkin();
	void Call1();
	void Call2();
};