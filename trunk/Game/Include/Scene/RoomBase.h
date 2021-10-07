#pragma once

#include "Stage.h"

class CRoomBase :
	public CStage
{
	friend class CSceneManager;

protected:
	std::vector<std::vector<class CDoor*>>	m_vecDoor;
	bool	m_bClearRoom;
	int		m_iRoomNum;
	std::vector<int>	m_vecRoomNum;

public:
	bool IsClearRoom()	const
	{
		return m_bClearRoom;
	}

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	void SetDoor(EDoorDir eDoorDir, bool bIsBossDoor);
	const Vector2& GetDoorPos(EDoorDir eDoorDir, bool bIsBossDoor);

protected:
	virtual void CreateMonster();
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoomBase();
	virtual ~CRoomBase();
};

