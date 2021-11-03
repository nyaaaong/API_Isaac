#pragma once

#include "Stage.h"

class CRoomBase :
	public CStage
{
	friend class CSceneManager;

protected:
	std::vector<std::vector<class CDoor*>>	m_vecDoor;
	int		m_iMonsterCount;
	bool	m_bIsBossRoom;

public:
	int GetMonsterCount()	const
	{
		return m_iMonsterCount;
	}

public:
	void AddMonsterCount(int iCount)
	{
		m_iMonsterCount += iCount;
	}

public:
	void SubMonsterCount();

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

