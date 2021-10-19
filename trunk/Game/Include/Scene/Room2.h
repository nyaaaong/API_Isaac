#pragma once

#include "RoomBase.h"

class CRoom2 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom2();
	virtual ~CRoom2();
};

