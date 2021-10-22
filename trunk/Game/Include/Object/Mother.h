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
	bool	m_bFirstPattern; // 처음엔 무조건 발동하는 패턴
	class CMotherLeg* m_pLeg;
	class CMotherDoor* m_pDoor[DD_MAX];

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CMother* Clone();

public:
	void SetPart(class CMotherLeg* pLeg, class CMotherDoor** pDoor);

private:
	void MotherPattern(float fTime);
};