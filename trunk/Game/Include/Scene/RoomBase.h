#pragma once

#include "Stage.h"

class CRoomBase :
	public CStage
{
	friend class CSceneManager;

protected:
	std::vector<std::vector<class CDoor*>>	m_vecDoor;
	int		m_iMonsterCount;

public:
	int GetMonsterCount()	const
	{
		return m_iMonsterCount;
	}

public:
	void SubMonsterCount(int iCount)
	{
		m_iMonsterCount -= iCount;

		if (m_iMonsterCount < 0)
			m_iMonsterCount = 0;
	}

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	void SetDoor(EDoorDir eDoorDir, EDoorType eDoorType);
	const Vector2& GetDoorPos(EDoorDir eDoorDir, EDoorType eDoorType);

private:
	void CreateDoor();

public:
	virtual void CreateMonster();
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoomBase();
	virtual ~CRoomBase();
};

