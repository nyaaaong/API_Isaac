#pragma once

#include "Stage.h"

class CRoomBase :
	public CStage
{
	friend class CSceneManager;

protected:
	std::vector<std::vector<class CDoor*>>	m_vecDoor;
	int		m_iMonsterCount;
	int		m_iBossMonsterCount;

public:
	int GetBossMonsterCount()	const
	{
		return m_iBossMonsterCount;
	}

	int GetMonsterCount()	const
	{
		return m_iMonsterCount;
	}

public:
	void SubMonsterCount();
	void SubBossMonsterCount();

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);

public:
	const Vector2& GetDoorPos(EDoorDir eDoorDir, EDoorType eDoorType);

protected:
	void SetDoor(EDoorDir eDoorDir, EDoorType eDoorType);

private:
	void CreateDoor();

public:
	void CreateMonster();
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoomBase();
	virtual ~CRoomBase();
};

