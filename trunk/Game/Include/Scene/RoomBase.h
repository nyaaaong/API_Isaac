#pragma once

#include "Stage.h"

class CRoomBase :
	public CStage
{
	friend class CSceneManager;

protected:
	int		m_iLeftDoor;
	int		m_iTopDoor;
	int		m_iRightDoor;
	int		m_iBottomDoor;

protected:
	std::vector<class CDoor*>	m_vecDoor;

protected:
	void CreateDoor();
	void CreateMonster();

public:
	void AddDoorCount(EDoorDir eDoorDir)
	{
		switch (eDoorDir)
		{
		case EDoorDir::Left:
			++m_iLeftDoor;
			break;
		case EDoorDir::Top:
			++m_iTopDoor;
			break;
		case EDoorDir::Right:
			++m_iRightDoor;
			break;
		case EDoorDir::Bottom:
			++m_iBottomDoor;
			break;
		}
	}

	void SetDoorCount(EDoorDir eDoorDir)
	{
		switch (eDoorDir)
		{
		case EDoorDir::Left:
			--m_iLeftDoor;
			break;
		case EDoorDir::Top:
			--m_iTopDoor;
			break;
		case EDoorDir::Right:
			--m_iRightDoor;
			break;
		case EDoorDir::Bottom:
			--m_iBottomDoor;
			break;
		}
	}

public:
	int GetLeftDoorCount()	const
	{
		return m_iLeftDoor;
	}

	int GetTopDoorCount()	const
	{
		return m_iTopDoor;
	}

	int GetRightDoorCount()	const
	{
		return m_iRightDoor;
	}

	int GetBottomDoorCount()	const
	{
		return m_iBottomDoor;
	}

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	CRoomBase();
	virtual ~CRoomBase();
};

