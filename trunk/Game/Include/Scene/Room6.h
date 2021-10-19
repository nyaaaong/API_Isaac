#pragma once

#include "RoomBase.h"

class CRoom6 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom6();
	virtual ~CRoom6();
};

