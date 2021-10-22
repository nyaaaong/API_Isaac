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
	bool	m_bFirstPattern; // ó���� ������ �ߵ��ϴ� ����
	class CMotherLeg* m_pLeg;
	class CMotherDoor* m_pDoor[DD_MAX];
	CCharacter* m_pPlayer;
	float	m_fPlayerPrevHP;
	std::vector<std::function<void()>>	m_vecPatternFunc;
	bool	m_bProgress;	// ������ �������̶�� true

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CMother* Clone();

public:
	void SetPart(class CMotherLeg* pLeg, class CMotherDoor** pDoor);

private:
	void MotherPlayerHPUpdater();
	void MotherPattern(float fTime);

private:
	void SpawnLeg();
};